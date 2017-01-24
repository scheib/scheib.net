// ObjSphere.h: interface for the ObjSphere class.
//
//////////////////////////////////////////////////////////////////////
//
// sphere object

#ifndef OBJSPHERE_H
#define OBJSPHERE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "SceneObject.h"
#include "Vec3f.h"

class ObjSphere : public SceneObject  
{
public:
	ObjSphere(const Vec3f pos = Vec3f(0,0,0),
              const float radius = 1.0f);
	virtual ~ObjSphere();

    // Updates internal data for the specified time (including bounding).
    virtual void update_geometry(const float time) { };

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
    virtual Vec3f ObjSphere::calculate_normal();

protected:
    Vec3f intersected_point;
};

#endif 
