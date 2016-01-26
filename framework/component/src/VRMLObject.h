/*
 * $RCSfile: VRMLObject.h,v $ 
 *
 * Copyright (C) 1996, Beat Liechti <liechti@isbe.ch>
 *                     Ingenieurschule Bern, Switzerland
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
 *  $Id: VRMLObject.h,v 1.2 1996/08/01 12:01:33 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _VRMLObject_H
#define _VRMLObject_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Stack.h"
#include "booga/base/Color.h"
#include "booga/base/Vector3D.h"
#include "booga/base/TransMatrix3D.h"

#include "VRML.h"
#include "VRMLState.h"

//___________________________________________________________________ VRMLObject

class VRMLObject {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    VRMLObject();
    // VRMLObject(const VRMLObject&);          // Use default version.
    
  public:
    virtual ~VRMLObject();
    
  private:
    VRMLObject& operator=(const VRMLObject&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    virtual void apply(Stack<VRMLState*> &stack) = 0;
    virtual VRMLObject* copy() = 0;
};

//___________________________________________________________________ VRMLList

class VRMLList : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    VRMLList();
  public:
    VRMLList(const VRMLList& aList); 
  public:
    ~VRMLList();
  private:
    VRMLList& operator=(const VRMLList&);      // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    void add(VRMLObject& vrmlObject);
    void reset();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 public:
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject* copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private: 
    struct sData {
      List<VRMLObject*> ourList;
      long ourRefCount;
    } *myData;
};

//___________________________________________________________________ VRMLMatrixTransform

class VRMLMatrixTransform : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLMatrixTransform();                   // default constructor  
  public:
    //VRMLMatrixTransform(const VRMLMatrixTransform&);  // default copy constructor
  public:
    //~VRMLMatrixTransform();                  // default destructor
  private:
    VRMLMatrixTransform& operator=(const VRMLMatrixTransform&);      // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLMatrixTransform
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    void setMatrix(const TransMatrix3D& matrix);
    void reset();
  private:
    void apply(VRMLState &state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:       
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    TransMatrix3D myMatrix;
};

//___________________________________________________________________ VRMLRotation

class VRMLRotation : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLRotation();                          // default constructor  
  public:
    //VRMLRotation(const VRMLRotation&);       // default copy constructor
  public:
    //~VRMLRotation();                         // default destructor
  private:
    VRMLRotation& operator=(const VRMLRotation&);  // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLRotation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    void setRotation(const TransMatrix3D& rotation);
    void reset();
  private:  
    void apply(VRMLState &state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 private:
   TransMatrix3D myRotation;
};

//___________________________________________________________________ VRMLTransform

class VRMLTransform : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLTransform();                         // default constructor  
  public:
    //VRMLTransform(const VRMLTransformt&);    // default copy constructor
  public:
    //~VRMLTransform();                        // default destructor
  private:
    VRMLTransform& operator=(const VRMLTransform&);  // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLTransform
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setTranslation(const Vector3D& translation);
    void setRotation(const TransMatrix3D& rotation);
    void setScaleFactor(const Vector3D& scaleFactor);
    void setScaleOrientation(const TransMatrix3D& scaleOrientation);
    void setCenter(Vector3D& center);
    void reset(); 
 private:
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    Vector3D myTranslation;
    TransMatrix3D myRotation;    
    Vector3D myScaleFactor;
    TransMatrix3D myScaleOrientation;
    TransMatrix3D myScaleOrientationInvert;
    Vector3D myCenter;    
};

//___________________________________________________________________ VRMLTranslation

class VRMLTranslation : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLTranslation();                          // default constructor  
  public:
    //VRMLTranslation(const VRMLTranslation&);    // default copy constructor
  public:
    //~VRMLTranslation();                         // default destructor
  private:
    VRMLTranslation& operator=(const VRMLTranslation&);  // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLTranslation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setTranslation(const Vector3D& translation);
    void reset();
  private:
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  private:
    Vector3D myTranslation;
};

//___________________________________________________________________ VRMLScale

class VRMLScale : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLScale();                          // default constructor  
  public:
    //VRMLScale(const VRMLScale&);          // default copy constructor
  public:
    //~VRMLScale();                         // default destructor
  private:
    VRMLScale& operator=(const VRMLScale&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLScale
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setScaleFactor(const Vector3D& scaleFactor);
    void reset();
  private:
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    Vector3D myScaleFactor;
};

//___________________________________________________________________ VRMLOrthographicCamera

class VRMLOrthographicCamera : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLOrthographicCamera();                              // default constructor  
  public:
    //VRMLOrthographicCamera(const VRMLOrthographicCamera&); // default copy constructor
  public:
    //~VRMLOrthographicCamera();                             // default destructor
  private:
    VRMLOrthographicCamera& operator=(const VRMLOrthographicCamera&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLScale
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setPosition(const Vector3D& position);
    void setOrientation(const TransMatrix3D& orientation);
    void setFocalDistance(double focalDistance);
    void setHeight(double height);
    void reset(); 
  private:
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    Vector3D myPosition;
    TransMatrix3D myOrientation;
    double myFocalDistance;
    double myHeight;    
};

//___________________________________________________________________ VRMLPerspectiveCamera

class VRMLPerspectiveCamera : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLPerspectiveCamera();                             // default constructor  
  public:
    //VRMLPerspectiveCamera(const VRMLPerspectiveCamera&); // default copy constructor
  public:
    //~VRMLPerspectiveCamera();                            // default destructor
  private:
    VRMLPerspectiveCamera& operator=(const VRMLPerspectiveCamera&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLPerspectiveCamera
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setPosition(const Vector3D& position);
    void setOrientation(const TransMatrix3D& orientation);
    void setFocalDistance(double focalDistance);
    void setHeightAngle(double heightAngle);
    void reset();
  private:    
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    Vector3D myPosition;
    TransMatrix3D myOrientation;
    double myFocalDistance;
    double myHeightAngle;
};

//___________________________________________________________________ VRMLDirectionalLight

class VRMLDirectionalLight : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLDirectionalLight();                             // default constructor  
  public:
    //VRMLDirectionalLight(const VRMLDirectionalLight&);  // default copy constructor
  public:
    //~VRMLDirectionalLight();                            // default destructor
  private:
    VRMLDirectionalLight& operator=(const VRMLDirectionalLight&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLDirectionalLight
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setOn(bool on);
    void setIntensity(double intensity);
    void setColor(const Color& color);
    void setDirection(const Vector3D& direction);
    bool getOn();
    void reset();
  private:
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    bool myOn;
    double myIntensity;
    Color myColor;
    Vector3D myLocation;
};

//___________________________________________________________________ VRMLPointLight

class VRMLPointLight : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLPointLight();                       // default constructor  
  public:
    //VRMLPointLight(const VRMLPointLight&);  // default copy constructor
  public:
    //~VRMLPointLight();                      // default destructor
  private:
    VRMLPointLight& operator=(const VRMLPointLight&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLPointLight
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setOn(bool on);
    void setIntensity(double intensity);
    void setColor(const Color& color);
    void setLocation(const Vector3D& location);
    bool getOn();
    void reset(); 
  private:
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    bool myOn;
    double myIntensity;
    Color myColor;
    Vector3D myLocation;
};

//___________________________________________________________________ VRMLSpotLight

class VRMLSpotLight : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLSpotLight();                              // default constructor  
  public:
    //VRMLSpotLight(const VRMLSpotLight&);          // default copy constructor
  public: 
    //~VRMLSpotLight();                             // default destructor
  private:
    VRMLSpotLight& operator=(const VRMLSpotLight&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLSpotLight
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setOn(bool on);
    void setIntensity(double intensity);
    void setColor(const Color& color);
    void setLocation(const Vector3D& location);
    void setDirection(const Vector3D& direction);
    bool getOn();
    void reset(); 
  private:
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    bool myOn;
    double myIntensity;
    Color myColor;
    Vector3D myLocation;
    Vector3D myDirection;
};

//___________________________________________________________________ VRMLCone

class VRMLCone : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLCone();                             // default constructor  
  public:
    //VRMLCone(const VRMLCone&);              // default copy constructor
  public:
    //~VRMLCone();                            // default destructor
  private:
    VRMLCone& operator=(const VRMLCone&);     // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLCone
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setParts(unsigned long parts);
    void setBottomRadius(double bottomRadius);
    void setHeight(double height);
    void reset();
  private:
    void addMaterial(VRMLState& state, Object3D* object3D, int matIndex);
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    unsigned long myParts;
    double myBottomRadius;
    double myHeight;
};

//___________________________________________________________________ VRMLCube

class VRMLCube : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLCube();                             // default constructor  
  public:
    //VRMLCube(const VRMLCube&);              // default copy constructor
  public:
    //~VRMLCube();                            // default destructor
  private:
    VRMLCube& operator=(const VRMLCube&);     // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLCone
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setWidth(double width);
    void setHeight(double height);
    void setDepth(double depth);
    void reset();
  private:
    void addMaterial(VRMLState& state, Object3D *object3D, int matIndex);
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    double myWidth;
    double myHeight;
    double myDepth;
};

//___________________________________________________________________ VRMLCylinder

class VRMLCylinder : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLCylinder();                             // default constructor  
  public:
    //VRMLCylinder(const VRMLCylinder&);          // default copy constructor
  public:
    //~VRMLCylinder();                            // default destructor
  private:
    VRMLCylinder& operator=(const VRMLCylinder&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLCylinder
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setParts(unsigned long parts);
    void setRadius(double radius);
    void setHeight(double height);
    void reset();
  private:
    void addMaterial(VRMLState& state, Object3D* object3D, int matIndex);
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    unsigned long myParts;
    double myRadius;
    double myHeight;
};

//___________________________________________________________________ VRMLIndexedFaceSet

class VRMLIndexedFaceSet : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLIndexedFaceSet();                          // default constructor  
  public:
    //VRMLIndexedFaceSet(const VRMLIndexedFaceSet&); // default copy constructor
  public:
    //~VRMLIndexedFaceSet();                         // default destructor
  private:
    VRMLIndexedFaceSet& operator=(const VRMLIndexedFaceSet&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLIndexedFaceSet
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setCoordIndex(const List<long>& coordIndex);
    void setMaterialIndex(const List<long>& materialIndex);
    void setNormalIndex(const List<long>& normalIndex);
    void reset();
  private:
    void addMaterial(VRMLState& state, Object3D *object3D, int matIndex);
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    List<long> myCoordIndex;
    List<long> myMaterialIndex;
    List<long> myNormalIndex;
};

//___________________________________________________________________ VRMLSphere

class VRMLSphere : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLSphere();                          // default constructor  
  public:
    //VRMLSphere(const VRMLSphere&);         // default copy constructor
  public:
    //~VRMLSphere();                         // default destructor
  private:
    VRMLSphere& operator=(const VRMLSphere&);    // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLSphere
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setRadius(double radius);
    void reset();
  private:
    void addMaterial(VRMLState& state, Object3D* object3D, int matIndex);
    void apply(VRMLState& state);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    double myRadius;
};

//___________________________________________________________________ VRMLCoordinate3

class VRMLCoordinate3 : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLCoordinate3();                          // default constructor  
  public:
    //VRMLCoordinate3(const VRMLCoordinate3&);    // default copy constructor
  public:
    //~VRMLCoordinate3();                         // default destructor
  private:
    VRMLCoordinate3& operator=(const VRMLCoordinate3&);    // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLCoordinate3
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setPoint(List<Vector3D>& point);
    void reset();
  private:
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    List<Vector3D> myPoint;  
};

//___________________________________________________________________ VRMLMaterial

class VRMLMaterial : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLMaterial();                          // default constructor  
  public:
    //VRMLMaterial(const VRMLMaterial&);       // default copy constructor
  public:
    //~VRMLMaterial();                         // default destructor
  private:
    VRMLMaterial& operator=(const VRMLMaterial&);  // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLMaterial
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setAmbientColor(List<Color>& ambientColor);
    void setDiffuseColor(List<Color>& diffuseColor);
    void setSpecularColor(List<Color>& specularColor);
    void reset();
  private:
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    List<Color> myAmbientColor;
    List<Color> myDiffuseColor;
    List<Color> mySpecularColor;
};

//___________________________________________________________________ VRMLMaterialBinding

class VRMLMaterialBinding : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLMaterialBinding();                           // default constructor  
  public:
    //VRMLMaterialBinding(const VRMLMaterialBinding&); // default copy constructor
  public:
    //~VRMLMaterialBinding();                          // default destructor
  private:
    VRMLMaterialBinding& operator=(const VRMLMaterialBinding&);  // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLMaterialBinding
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setValue(VRML_binding_t value);
    void reset();
  private:
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    VRML_binding_t myValue;
};

//___________________________________________________________________ VRMLNormal

class VRMLNormal : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLNormal();                          // default constructor  
  public:
    //VRMLNormal(const VRMLNormal&);         // default copy constructor
  public:
    //~VRMLNormal();                         // default destructor
  private:
    VRMLNormal& operator=(const VRMLNormal&);    // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLNormal
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setVector(List<Vector3D> vector);
    void reset();
  private:
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    List<Vector3D> myVector;
};

//___________________________________________________________________ VRMLNormalBinding

class VRMLNormalBinding : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLNormalBinding();                          // default constructor  
  public:
    //VRMLNormalBinding(const VRMLNormalBinding&);  // default copy constructor
  public:
    //~VRMLNormalBinding();                         // default destructor
  private:
    VRMLNormalBinding& operator=(const VRMLNormalBinding&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLNormal
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void setValue(VRML_binding_t value);
    void reset();
  private:
    void apply(VRMLState& state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private:
    VRML_binding_t myValue;
};

//___________________________________________________________________ VRMLSeparatorStart

class VRMLSeparatorStart : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLSeparatorStart();                          // default constructor  
  public:
    //VRMLSeparatorStart(const VRMLSeparatorStart&); // default copy constructor
  public:
    //~VRMLSeparatorStart();                         // default destructor
  private:
    VRMLSeparatorStart& operator=(const VRMLSeparatorStart&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();
};

//___________________________________________________________________ VRMLSeparatorStop

class VRMLSeparatorStop : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLSeparatorStop();                          // default constructor  
  public:
    //VRMLSeparatorStop(const VRMLSeparatorStop&);  // default copy constructor
  public:
    //~VRMLSeparatorStop();                         // default destructor
  private:
    VRMLSeparatorStop& operator=(const VRMLSeparatorStop&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();
};

//___________________________________________________________________ VRMLLODStart

class VRMLLODStart : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLLODStart();                          // default constructor  
  public:
    //VRMLLODStart(const VRMLSeparatorStart&); // default copy constructor
  public:
    //~VRMLLODStart();                         // default destructor
  private:
    VRMLLODStart& operator=(const VRMLLODStart&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();
};

//___________________________________________________________________ VRMLLODStop

class VRMLLODStop : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLLODStop();                            // default constructor  
  public:
    //VRMLLODStop(const VRMLSeparatorStart&);   // default copy constructor
  public:
    //~VRMLLODStop();                           // default destructor
  private:
    VRMLLODStop& operator=(const VRMLLODStop&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();
};

//___________________________________________________________________ VRMLSwitchStart

class VRMLSwitchStart : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLSwitchStart();                          // default constructor  
  public:
    //VRMLSwitchStart(const VRMLSwitchStart&);    // default copy constructor
  public:
    //~VRMLSwitchStart();                         // default destructor
  private:
    VRMLSwitchStart& operator=(const VRMLSwitchStart&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLSwitchStart
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  public:
    void reset();
    void setWhichChild(long whichChild);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  private: 
    long myWhichChild;
};

//___________________________________________________________________ VRMLSwitchStop

class VRMLSwitchStop : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLSwitchStop();                          // default constructor  
  public:
    //VRMLSwitchStop(const VRMLSwitchStop&);     // default copy constructor
  public:
    //~VRMLSwitchStop();                         // default destructor
  private:
    VRMLSwitchStop& operator=(const VRMLSwitchStop&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();
};

//___________________________________________________________________ VRMLTransformSeparatorStart

class VRMLTransformSeparatorStart : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLTransformSeparatorStart();                          // default constructor  
  public:
    //VRMLTransformSeparatorStart(const VRMLTransformSeparatorStart&); // default copy constructor
  public:
    //~VRMLTransformSeparatorStart();                         // default destructor
  private:
    VRMLTransformSeparatorStart& operator=(const VRMLTransformSeparatorStart&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();
};

//___________________________________________________________________ VRMLTransformSeparatorStop

class VRMLTransformSeparatorStop : public VRMLObject
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  public:
    //VRMLTransformSeparatorStop();                          // default constructor  
  public:
    //VRMLTransformSeparatorStop(const VRMLTransformSeparatorStart&); // default copy constructor
  public:
    //~VRMLTransformSeparatorStop();                         // default destructor
  private:
    VRMLTransformSeparatorStop& operator=(const VRMLTransformSeparatorStop&); // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class VRMLObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
  public:    
    virtual void apply(Stack<VRMLState*> &stack);
    virtual VRMLObject *copy();
};

#endif // _VRMLObject_H

