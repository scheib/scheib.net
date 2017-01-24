// SceneLight.h: interface for the SceneLight class.
//
//////////////////////////////////////////////////////////////////////
//
// Parent Class for all Lights for a scene
//

#ifndef SCENELIGHT_H
#define SCENELIGHT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Vec3f.h"

class SceneLight  
{
public:
	SceneLight();
  virtual ~SceneLight();
  
  // Returns vector from point to light UN-NORMALIZED
  virtual Vec3f getDirection(const Vec3f point) { return Vec3f(); }
  
  // Returns color and intensity of light from this light
  // which reaches point
  virtual Vec3f calculate_intensity(const Vec3f point) { return Vec3f(); }

  bool cast_shadows;
};

#endif 
