// SceneEnvironment.h: interface for the SceneEnvironment class.
//
//////////////////////////////////////////////////////////////////////
//
// Parent Class for all Environments for a Scene
//

#ifndef SCENEENVIRONMENT_H
#define SCENEENVIRONMENT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Vec3f.h"

class SceneEnvironment  
{
public:
  SceneEnvironment(const Vec3f ambient_color = Vec3f(),
    const Vec3f background_color = Vec3f())
  { 
    the_ambient_color     = ambient_color    ;
    the_background_color  = background_color ;
  }
  virtual ~SceneEnvironment() { }
  
  // returns the ambient light level
  virtual Vec3f get_ambient_light() { return the_ambient_color; }
  
  // returns color at an infinite distance, the wall of the universe.
  virtual Vec3f get_universe_wall(const Vec3f dir) { return the_background_color; }

  void set_ambient_color(const Vec3f ambient_color)
  { the_ambient_color = ambient_color; }

  void set_background_color(const Vec3f background_color)
  { the_background_color = background_color; }
                            
protected:
  Vec3f the_ambient_color;
  Vec3f the_background_color;
  
};

#endif
