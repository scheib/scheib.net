// MatTexturedQuad.cpp: implementation of the MatTexturedQuad class.
//
//////////////////////////////////////////////////////////////////////

#include "MatTexturedQuad.h"

Vec3f MatTexturedQuad::get_color()
{ 
  Vec3f temp;
  temp = texture.get_color_01(intersected_x, intersected_y);
  //temp = Vec3f(intersected_x, intersected_y, 0.5); //!
  return temp; 
}
