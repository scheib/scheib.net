// SceneObject.h: interface for the SceneObject class.
//
//////////////////////////////////////////////////////////////////////
//
// Parent Class for all Objects for a scene
//

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Vec3f.h"
#include "Material.h"

class Scene;

class SceneObject  
{
public:
    // TYPE DEFS
    //////////////

    // NO_INTERSECTION, OUTSIDE_INTERSECTION, INSIDE_INTERSECTION
    enum Intersect_Type {
        NO_INTERSECTION,
        OUTSIDE_INTERSECTION,
        INSIDE_INTERSECTION
    };


	SceneObject();
	virtual ~SceneObject();

    virtual void set_material(Material* material) // associates a material type with sphere
        { the_material = material; }
    Material* get_material() // returns object's material
        { return the_material; }

    void set_scene(Scene* scene) // Sets pointer back to the scene this object is contained in
        { the_scene = scene; }
    Scene* get_scene() // returns object's material
        { return the_scene; }

    // Updates internal data for the specified time (including bounding).
    virtual void update_geometry(const float time) { }
    

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
	virtual Vec3f calculate_normal();


    bool cast_shadows; // Does this object cast shadows
    bool receive_shadows; // Can shadows be cast on this object

protected:
	Vec3f the_bounding_sphere_center;
	float the_bounding_sphere_radius;
	float the_bounding_sphere_radius_squared;

    Material *the_material;
    Scene *the_scene;
};

#endif 
