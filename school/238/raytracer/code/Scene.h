// Scene.h: interface for the Scene class.
//
//////////////////////////////////////////////////////////////////////
//
// Scene which contains all data and properties and which can draw
// the scene to a buffer
//

/* Notes:

Coordinate system used:

Right handed; Z is up.

   z
   |   (far away)
   | .y
   |/____ x

*/

#ifndef SCENE_H
#define SCENE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Buffer.h"
#include "SceneLight.h"
#include "SceneObject.h"
#include "SceneEnvironment.h"
#include "Observer.h"
#include "Vec3f.h"	// Added by ClassView

class Scene  
{
public:
	Scene(const int light_count, const int obj_count, const int max_depth);
	virtual ~Scene();

    void add_light(SceneLight *light);
    void add_object(SceneObject *obj);
	void set_environment(SceneEnvironment *env);
	void set_observer(Observer *observer);
	void set_material_list(Material **material_list, int num)
    {   the_material_list = material_list;
        the_material_count = num; }
    Observer* get_observer() { return the_observer; }
	void draw(Buffer &buffer, const float time, const float frame_width);
	void adaptive_draw(Buffer &buffer, const float time, const float frame_width, const int samples);

protected:
    // recursive function to determine color a ray will see.
    // dir must be normalized
    // depth is current recursion depth
	Vec3f trace_ray(const Vec3f eye, const Vec3f dir, const int depth);

    // recursive function to determine color at intersection point
    // depth is current recursion depth
    Vec3f shade_object(const int obj_num, 
                       const Vec3f point,
                       const SceneObject::Intersect_Type isect_type,
                       const Vec3f to_eye, // to_eye Not Normalized
                       const int depth);

protected:
	int the_light_count;
	int the_max_light_count;
	SceneLight ** the_light_list;

	int the_obj_count;
	int the_max_obj_count;
	SceneObject ** the_obj_list;

	int the_material_count;
	Material ** the_material_list;

    SceneEnvironment* the_environment;
    Observer * the_observer;
    int the_max_recursion_depth;
    struct DList { int   object_number; 
                   float t; 
                   SceneObject::Intersect_Type isect_type;
    } *the_distance_list;
};

#endif
