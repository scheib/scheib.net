// MatTexturedQuad.h: interface for the MatTexturedQuad class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MATTEXTUREDQUAD_H
#define MATTEXTUREDQUAD_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Material.h"
#include "Buffer.h"

class MatTexturedQuad : public Material  
{
public:
  MatTexturedQuad() {}
  virtual ~MatTexturedQuad() {}

#pragma warning( disable : 4183 )
  set_texture_buffer(const char* texture_file_name)
  {
  	texture.ReadTGA(texture_file_name);
  }

  set_intersected_point(const float x, const float y)
  {
    intersected_x = x;
    intersected_y = y;
  }

  Vec3f get_color();

protected:
  Buffer texture;
  float intersected_x, intersected_y;
};

#endif 
