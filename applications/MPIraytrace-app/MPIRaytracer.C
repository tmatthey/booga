/*
 * $RCSfile: MPIRaytracer.C,v $
 *
 * Copyright (C) 1996, Bernhard Buhlmann <buhlmann@iam.unibe.ch>
 *                     University of Berne, Switzerland
 *
 * All rights reserved.
 *
 * This software may be freely copied, modified, and redistributed
 * provided that this copyright notice is preserved on all copies.
 *
 * You may not distribute this software, in whole or in part, as part of
 * any commercial product without the express consent of the authors.
 *
 * There is no warranty or other guarantee of fitness of this software
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: MPIRaytracer.C,v 1.5 1998/05/22 07:07:40 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifdef HAVE_MPI
//extern "C" {
#include <mpi.h>
//}
#endif

#include <time.h>

#ifdef HAVE_OPENGL
#include <GL/glut.h>
#endif

#include <sstream>  // ostrstream
#include "booga/base/Statistic.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Primitive3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/Ray3D.h"
#include "booga/object/Ray3DFactory.h"
#include "booga/object/Texture3D.h"
#include "booga/object/Texture3DContext.h"
#include "booga/object/Viewing3D.h"
#include "booga/component/JPEGWriter.h"
#include "MPIRaytracer.h"

//____________________________________________________________________ MPIRaytracer

implementRTTI(MPIRaytracer, PixmapRenderer);

static void ourDisplayFunc();
static void ourIdleFunc();
static void quit();
static void keyboardCallback(unsigned char key, int x, int y);
static void mouseCallback(int button, int state, int x, int y);

int idle_myLinesLeft;
int idle_resX;
int idle_myRowDataEntrySize;
int idle_number;
float idle_r;
float idle_g;
float idle_b;

MPIRaytracer::MPIRaytracer(int numtask, int taskid, bool show, int number, int pipe, int argc, char* argv[])
{
  myNumtask = numtask;
  myTaskid = taskid;
  myRowDataEntrySize = 7;
  myNumber = number;
  myShow = false;
  myLinesLeft = 0;
  myRowData = NULL;
  myPipe = pipe;
#ifdef HAVE_OPENGL
  myShow = show;
  if (show && taskid == 1)
      glutInit(&argc, &argv[0]);
#endif
}

bool MPIRaytracer::doExecute()
{
  if (myTaskid == 0) {
    // I'm the master, so allocate a Pixmap:   
    // Initialize pixmap
    myPixmap->clearDepth(MAXFLOAT);
    myPixmap->clearAlpha(0);
    Color bg = getCamera()->getBackground();
    myPixmap->clearColor(bg[0], bg[1], bg[2]);
  }

  if (myTaskid == 0){
    std::stringstream os;
    os << "Using " << (myShow ? myNumtask -2 : myNumtask -1);
    os << " process to raytrace";
    Report::hint(os);

    collect_pixels();
  }
  else if (myTaskid == 1 && myShow)
    display_pixels();
  else
    compute_pixels();
        
  // Postprocessing. 
  return true;
}

void MPIRaytracer::compute_pixels ()
{
#ifdef HAVE_MPI
  // Some variables for use in the loop.
  MPI_Status stat;
  Color bg = getCamera()->getBackground();
  Color defaultColor = bg;
  long position = 0;
  int x,y,i;
  double t = 0;
  double t1,t2;
  double t_max = -1;

  int resX = getCamera()->getViewing()->getResolutionX();
  Ray3D* ray = Ray3DFactory::createRay(Vector3D(0,0,0), Vector3D(1,0,0));
  const Path3D* path = NULL;

  myRowData = new float[myRowDataEntrySize*resX];

  i = 0;

  // Setup the texturing context.
  Texture3DContext context;
  context.setWorld(getWorld());
  context.setAmbientLightSources(getAmbientLightSources());
  context.setDirectedLightSources(getDirectedLightSources());

  // GO !!!
  MPI_Barrier(MPI_COMM_WORLD);

  //
  // Start ray tracing.
  //
  
  while(true) {

    // Wait for a line
    t1 = MPI_Wtime();
    MPI_Recv(&y,1,MPI_INT,0,2,MPI_COMM_WORLD, &stat);
    t2 = MPI_Wtime() - t1;
    if (i > 0) {
      t +=t2;
      if (t2 > t_max)
	t_max = t2;
    }
    i++;

    if (y < 0)
      break;

    // reset myRowData:
    for (int i=0; i<myRowDataEntrySize*resX; i++)
      myRowData[i] = -1;

    position = 0;
    for (x=0; x<resX; x++, position += myRowDataEntrySize) { 
      //
      // We send a new primary ray ...
      //
      ray->reset();
      getCamera()->getViewing()->computeRayThrough(x, y, *ray);

      if (getWorld()->getObjects()->intersect(*ray) &&
          ((path = ray->getPath()) != NULL)) {
        context.setIncidencePosition(ray->getOrigin());
        context.setOCS2WCS(path->getLastTransform());
        context.setPositionWCS(ray->getHitPoint());
        context.setNormalOCS(ray->getBestHitObject()->normal(context.getPositionOCS()));
        context.setColor(defaultColor);

        Texture3D::texturing(context, path);
  
        myRowData[position + 0] = x;
        myRowData[position + 1] = y;
        myRowData[position + 2] = context.getColor().getRed();
        myRowData[position + 3] = context.getColor().getGreen();
        myRowData[position + 4] = context.getColor().getBlue();
        myRowData[position + 5] = context.getColor().getBlue();
        myRowData[position + 6] = ray->getBestHitDistance();        
      } else {
        myRowData[position + 1] = y;
      }
        
    }
    MPI_Send (myRowData, myRowDataEntrySize * resX, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
    if (myShow)
      MPI_Send (myRowData, myRowDataEntrySize * resX, MPI_FLOAT, 1, 1, MPI_COMM_WORLD);

  }
  std::stringstream os;
  os << "Slave " << myTaskid -  (myShow ? 2 : 1) << " was " << t << " (" << t_max << ") seconds idle";
  Report::hint(os);

  delete ray;
  delete myRowData;
#endif
}

void MPIRaytracer::collect_pixels()
{
#ifdef HAVE_MPI
  MPI_Status stat;
  long position = 0;
  int numproc = myShow ? myNumtask -2 : myNumtask -1;
  int offset  = myShow ? 2 : 1;
  int* busy;
  int* statistic;
  int x,y,i,j;
  int resX = getCamera()->getViewing()->getResolutionX();
  int resY = getCamera()->getViewing()->getResolutionY();
  if (myRowData == NULL)
    myRowData = new float[myRowDataEntrySize*resX];

  busy = new int[numproc];
  statistic = new int[numproc];
  for (i=0;i< numproc;i++){
    busy[i] = 0; 
    statistic[i] = 0;
  }

  myLinesLeft = resY;
  y = 0;

  // GO !!!
  MPI_Barrier(MPI_COMM_WORLD);

  while(myLinesLeft > 0) {
    // Feed the idle slaves
    for(j = 0; j <= myPipe; j++){
      for(i = 0; i <numproc; i++){
	if (busy[i] == j && y < resY){
	  MPI_Send(&y,1,MPI_INT, i + offset, 2,MPI_COMM_WORLD);
	  statistic[i]++;
	  busy[i]++;
	  y++;
	}
      }
    }


    // Receive data from a slave
    MPI_Recv(myRowData, myRowDataEntrySize * resX, MPI_FLOAT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &stat);
    busy[stat.MPI_SOURCE - offset]--;

    for (x=0, position = 0; x<resX; x++, position += myRowDataEntrySize) {
      if (myRowData[position + 0] > -1) {
        myPixmap->setPosition(x, (int)myRowData[position + 1]);
        myPixmap->setColor(myRowData[position + 2], myRowData[position + 3], myRowData[position + 4]);
        myPixmap->setDepth(myRowData[position + 5]);
        myPixmap->setAlpha(myRowData[position + 6]);
        
      }    
    }
    myLinesLeft--;
    if (!(myLinesLeft % 10)) {
      std::stringstream os;
      os << "Finished line " << getCamera()->getViewing()->getResolutionY() - myLinesLeft;
      Report::debug(os);
    }
  }
  
  // Sending EOF
  y = -1;
  for(i = 0; i <numproc; i++)
    MPI_Send(&y,1,MPI_INT, i + offset, 2,MPI_COMM_WORLD);

  std::stringstream os;
  os << "Distribution: ";
  for(i = 0; i < numproc-1; i++)
    os << statistic[i] <<", ";
  os << statistic[numproc-1];
  Report::hint(os);

  delete statistic;
  delete busy;
  delete myRowData;

  postprocessing(); // afterGenerate(); // !!!!!!!!!!!!!!!!!!
  return;
#endif
}

void MPIRaytracer::display_pixels() 
{
#ifdef HAVE_OPENGL  
  int resX = getCamera()->getViewing()->getResolutionX();
  int resY = getCamera()->getViewing()->getResolutionY();

  idle_myLinesLeft = resY;
  idle_resX = resX;
  idle_myRowDataEntrySize = myRowDataEntrySize;
  idle_r = getCamera()->getBackground().getRed();
  idle_g = getCamera()->getBackground().getGreen();
  idle_b = getCamera()->getBackground().getBlue();
  idle_number = myNumber;

  myRowData = new float[myRowDataEntrySize*resX];

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
  
  glutInitWindowSize(getCamera()->getViewing()->getResolutionX(), 
                  getCamera()->getViewing()->getResolutionY());

  glutCreateWindow("MPIraytrace Viewer");
  Color bgColor = getCamera()->getBackground();
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);
  glDrawBuffer (GL_FRONT);
  glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0);

  glClear(GL_COLOR_BUFFER_BIT);

  //
  // Setup viewing parameters and light sources of the GL rendering engine.
  //
  GLdouble left    = 0;
  GLdouble right   = getCamera()->getViewing()->getResolutionX();
  GLdouble bottom  = 0;
  GLdouble top     = getCamera()->getViewing()->getResolutionY();
                   
//  glViewport(0, 0, (GLint)getCamera()->getViewing()->getResolutionX(), 
//                   (GLint)getCamera()->getViewing()->getResolutionY());

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(left, right, bottom, top, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 
  //
  // Setup rendering quality.
  //
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);
  glShadeModel(GL_FLAT);

  glutIdleFunc (ourIdleFunc);
  glutDisplayFunc (ourDisplayFunc);
  glutKeyboardFunc(keyboardCallback);
  glutMouseFunc(mouseCallback);
  glFlush();

  glutMainLoop();
#else

#endif
}

void ourIdleFunc()
{
#ifdef HAVE_MPI
#ifdef HAVE_OPENGL    
  static float *row = NULL;
  static float *myRowData = NULL;
  MPI_Status stat;
  static bool new_pic = true;
  // GO !!!
  if (new_pic){
    new_pic = false;
#ifdef sgi
    if (row == NULL)
    {
      nanosleep(&wait,tmp);
      timespec_t wait;
      wait.tv_sec = 0;
      wait.tv_nsec = 5e+8;
      timespec_t *tmp = NULL;
    }
#endif
    MPI_Barrier(MPI_COMM_WORLD);
  }

  if (idle_myLinesLeft > 0) {
    if (row == NULL)
      row = new float[3*idle_resX];
    if (myRowData == NULL)
      myRowData = new float[idle_myRowDataEntrySize*idle_resX];
    for (int i=0; i<3*idle_resX; i++)
      row[i] = 0.0;

    MPI_Recv(myRowData,idle_myRowDataEntrySize * idle_resX, MPI_FLOAT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &stat);

    for (long x=0, position = 0; x<idle_resX; x++, position += idle_myRowDataEntrySize) {
      if (myRowData[position + 0] > -1) {
	row[3*x+0] = myRowData[position + 2];
        row[3*x+1] = myRowData[position + 3];
        row[3*x+2] = myRowData[position + 4];
	if (row[3*x+0] > 1.0)
	  row[3*x+0] = 1.0;
	if (row[3*x+1] > 1.0)
	  row[3*x+1] = 1.0;
	if (row[3*x+1] > 1.0)
	  row[3*x+1] = 1.0;
      } else {
        row[3*x+0] = idle_r;
        row[3*x+1] = idle_g;
        row[3*x+2] = idle_b;
      }    
    }

    glLoadIdentity();
    glRasterPos2d(0, myRowData[1]);
    glDrawPixels (idle_resX, 1, GL_RGB, GL_FLOAT, row);
    glFlush();

    idle_myLinesLeft--;

  }
  else {
    MPI_Barrier(MPI_COMM_WORLD);
    new_pic = true;

    idle_number--;
    if (idle_number <= 0) {
      delete row;
      delete myRowData;
      glutIdleFunc (NULL);
    }
    else {
      idle_myLinesLeft = idle_resX;
    }
  }
#endif
#endif
}

void ourDisplayFunc()
{
  return;
}

void mouseCallback(int , int , int , int )
{
  if (idle_number <=0){
#ifdef HAVE_OPENGL    
    glutIdleFunc (NULL);
#endif
    quit();
  }
}

void keyboardCallback(unsigned char , int, int)
{
  if (idle_number <=0){
#ifdef HAVE_OPENGL    
    glutIdleFunc (NULL);
#endif
    quit();
  }
}
// quit function when using glut
void quit()
{
#ifdef HAVE_MPI
  MPI_Finalize();
#endif
  exit(0);
}
