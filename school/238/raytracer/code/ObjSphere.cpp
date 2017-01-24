// ObjSphere.cpp: implementation of the ObjSphere class.
//
//////////////////////////////////////////////////////////////////////

#include "ObjSphere.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ObjSphere::ObjSphere(const Vec3f pos,
              const float radius)
{
    the_bounding_sphere_center = pos;
    the_bounding_sphere_radius = radius;
    the_bounding_sphere_radius_squared = radius * radius;
}

ObjSphere::~ObjSphere()
{

}


SceneObject::Intersect_Type ObjSphere::intersect(const Vec3f ray_origin, 
                          const Vec3f ray_direction,
                          const Intersect_Type intersect_type,
                          float &t)
{
    intersected_point = ray_origin+t*ray_direction; // Save for normal calculation
    return intersect_type;
}

Vec3f ObjSphere::calculate_normal()
{
    /*
    Vec3f norm(pos);
    norm -= the_bounding_sphere_center;
    norm.normalize();
    */
    return (intersected_point - the_bounding_sphere_center).norm_value();
}
