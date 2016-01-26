/*
 * $RCSfile: PixmapRenderer.C,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: PixmapRenderer.C,v 1.11 1996/08/02 08:42:10 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Aggregate2D.h"
#include "booga/object/Pixmap2D.h"
#include "booga/object/World2D.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/component/PixmapRenderer.h"

//______________________________________________________________ PixmapRenderer

implementRTTI(PixmapRenderer, Renderer);

PixmapRenderer::PixmapRenderer()
{
  myPixmap = NULL;
}

bool PixmapRenderer::preprocessing()
{
  if (!Renderer::preprocessing())
    return false;
 
  myPixmap = createPixmap(getCamera()->getViewing()->getResolutionX(), 
                          getCamera()->getViewing()->getResolutionY());

  return true;                       
}

bool PixmapRenderer::postprocessing()
{
  getResult()->getObjects()->adoptObject(new Pixmap2D(myPixmap));
  getResult()->getObjects()->computeBounds();
  myPixmap = NULL;
  
  return Renderer::postprocessing();
}

void PixmapRenderer::cleanupAfterFailure()
{
  delete myPixmap;
  myPixmap = NULL;
}
