// SceneObject.cpp: implementation of the SceneObject class.
//
//////////////////////////////////////////////////////////////////////

#include "SceneObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SceneObject::SceneObject() :
    cast_shadows(false),
    receive_shadows(false),
	the_bounding_sphere_center(0, 0, 0),
	the_bounding_sphere_radius(0),
    the_bounding_sphere_radius_squared(0),
    the_material(NULL),
    the_scene(NULL)
{
}

SceneObject::~SceneObject()
{

}




SceneObject::Intersect_Type SceneObject::intersect_bounding_sphere(const Vec3f ray_origin, 
                                                      const Vec3f ray_direction, 
                                                      float &t)
{
    // Algrithm taken from "Essential Ray Tracing Algorithms" by Eric Haines

    // Step 1: find distance squared between ray origin and center
    // OC is the Ray Origin to Sphere Center vector

    Vec3f OC(the_bounding_sphere_center);
    OC -= ray_origin;
    float length_OC_sqrd = OC.x*OC.x + OC.y*OC.y + OC.z*OC.z;

    // Step 2: calculate ray distance which is closest to center
    // Tca is the Closest aproach to the sphere center along the ray, t parameter.

    float Tca = OC.dot(ray_direction);

    // Step 3: test if ray is outside and points away from sphere

    bool outside_of_sphere = length_OC_sqrd >= the_bounding_sphere_radius_squared;
    if ((Tca < 0) && outside_of_sphere)
    {
        return SceneObject::NO_INTERSECTION;
    }

    // Step 4: find square of half chord intersection distance
    // T2hc is the half chord distance squared

    float T2hc = the_bounding_sphere_radius_squared - length_OC_sqrd + Tca*Tca;

    // Step 5: test if square is negative

    if (T2hc < 0)
    {
        return SceneObject::NO_INTERSECTION;
    }

    // Step 6: calculate intersection distance

    if (outside_of_sphere)
    {
        t = Tca - (float)sqrt(T2hc);
        return SceneObject::OUTSIDE_INTERSECTION;
    }
    else
    {
        t = Tca + (float)sqrt(T2hc);
        return SceneObject::INSIDE_INTERSECTION;
    }

    // FOLOWING STEPS unused
    // Step 7: find intersection point
    // Step 8: calculate normal at point

}

SceneObject::Intersect_Type SceneObject::intersect(const Vec3f ray_origin, 
                                      const Vec3f ray_direction,
                                      const Intersect_Type intersect_type,
                                      float &t)
{
    return SceneObject::NO_INTERSECTION;
}

Vec3f SceneObject::calculate_normal()
{
    return Vec3f(0,0,0);
}

