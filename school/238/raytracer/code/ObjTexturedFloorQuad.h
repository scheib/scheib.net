// TexturedFloorQuad.h: interface for the TexturedFloorQuad class.
//
//////////////////////////////////////////////////////////////////////
//
// textured quad object on the floor

#ifndef TEXTUREDFLOORQUAD_H
#define TEXTUREDFLOORQUAD_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SceneObject.h"
#include "Buffer.h"
#include "Vec3f.h"
#include "MatTexturedQuad.h"

class ObjTexturedFloorQuad : public SceneObject  
{
public:
	ObjTexturedFloorQuad(const Vec3f _position, const float _xscale, const float _yscale, const char* texture_file_name);
  virtual ~ObjTexturedFloorQuad() { }

    // Updates internal data for the specified time (including bounding).
    virtual void update_geometry(const float time) { };

    // Determines if ray intersects bounding shpere of object
    // ray_direction must be normalized
    // t, the distance to the intersection, is returned
    virtual Intersect_Type intersect_bounding_sphere(const Vec3f ray_origin, 
                                                     const Vec3f ray_direction,
                                                     float &t);

    // Finds intersection of object, Call AFTER intersect_bounding_sphere()
    // ray_direction must be normalized
    // intersect_type is value returned from intersect_bounding_sphere().
    // t must be intersection of bounding box, will be modified after actual intersection.
	  virtual Intersect_Type intersect(const Vec3f ray_origin, 
                                     const Vec3f ray_direction,
                                     const Intersect_Type intersect_type,
                                     float &t);

    // Returns normal of intersection, Call AFTER intersect()
    // Returns NORMALIZED normal
    virtual Vec3f calculate_normal() { return Vec3f(0,0,1); }

    virtual void set_material(Material* material); // We have our own special material for a textured quad
        

protected:
  float top_left_x;
  float top_left_y;
  float bottom_right_x;
  float bottom_right_y;
  float quad_z;
  Vec3f intersected_point;
  MatTexturedQuad texture_material;
};

#endif 
