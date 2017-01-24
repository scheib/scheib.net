// ObjTexturedFloorQuad.cpp: implementation of the ObjTexturedFloorQuad class.
//
//////////////////////////////////////////////////////////////////////

#include "ObjTexturedFloorQuad.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ObjTexturedFloorQuad::ObjTexturedFloorQuad(const Vec3f _position, const float _xscale, const float _yscale, const char* texture_file_name)
{
  top_left_x = _position.x - _xscale;
  top_left_y = _position.y + _yscale;
  bottom_right_x = _position.x + _xscale;
  bottom_right_y = _position.y - _yscale;
  quad_z = _position.z;

  texture_material.set_texture_buffer(texture_file_name);
  SceneObject::set_material(&texture_material);

 	the_bounding_sphere_center = _position;
	the_bounding_sphere_radius_squared = _xscale * _xscale + _yscale * _yscale;
	the_bounding_sphere_radius = (float) pow(the_bounding_sphere_radius_squared, 0.5);
}

// We have our own special material for a textured quad
void ObjTexturedFloorQuad::set_material(Material* material)
{
  texture_material.set_color(           material->get_color()             );
  texture_material.set_Kdiffuse(        material->get_Kdiffuse()          );
  texture_material.set_Kspecular(       material->get_Kspecular()         );
  texture_material.set_Kspecular_power( material->get_Kspecular_power()   );
  texture_material.set_Kreflectance(    material->get_Kreflectance()      );
  texture_material.set_Krefraction(     material->get_Krefraction()       );
  texture_material.set_density(         material->get_density()           );
  texture_material.set_reflection_angle(material->get_reflection_angle()  );
  texture_material.set_refraction_angle(material->get_refraction_angle()  );
}

// Determines if ray intersects bounding shpere of object
// ray_direction must be normalized
// t, the distance to the intersection, is returned
SceneObject::Intersect_Type ObjTexturedFloorQuad::intersect_bounding_sphere(const Vec3f ray_origin, 
                                                               const Vec3f ray_direction,
                                                               float &t)
{
  if (ray_origin.z == quad_z) return SceneObject::OUTSIDE_INTERSECTION;
  
  if (ray_origin.z > quad_z)
  {
    if (ray_direction.z > 0) return SceneObject::NO_INTERSECTION;
  }
  else     
  {
    if (ray_direction.z < 0) return SceneObject::NO_INTERSECTION;
  }
  
  if (ray_direction.z == 0) return SceneObject::NO_INTERSECTION;
  
  float x, y;
  t = (quad_z - ray_origin.z) / ray_direction.z;
  x = ray_origin.x + ray_direction.x * t;
  y = ray_origin.y + ray_direction.y * t;

  if ( (x >= top_left_x) && (x <= bottom_right_x) 
    && (y <= top_left_y) && (y >= bottom_right_y) )
  {
    x = (x-top_left_x)/(bottom_right_x-top_left_x);
    y = (y-top_left_y)/(bottom_right_y-top_left_y);
    //! y = (y-bottom_right_y)/(top_left_y-bottom_right_y);  this is what should be, not the previous. but textures flipped?

    texture_material.set_intersected_point( x, y );
    return SceneObject::OUTSIDE_INTERSECTION;
  }
    
  return SceneObject::NO_INTERSECTION;  
}



// Finds intersection of object, Call AFTER intersect_bounding_sphere()
// ray_direction must be normalized
// intersect_type is value returned from intersect_bounding_sphere().
// t must be intersection of bounding box, will be modified after actual intersection.
SceneObject::Intersect_Type ObjTexturedFloorQuad::intersect(const Vec3f ray_origin, 
                                     const Vec3f ray_direction,
                                     const Intersect_Type intersect_type,
                                     float &t)
{
    return intersect_type;
}
