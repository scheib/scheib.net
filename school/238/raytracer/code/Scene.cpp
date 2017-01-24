    // Scene.cpp: implementation of the Scene class.
    //
    //////////////////////////////////////////////////////////////////////
    
    #include "Scene.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include <time.h>
    
//    #include <stdlib.h>
    
    //////////////////////////////////////////////////////////////////////
    // Construction/Destruction
    //////////////////////////////////////////////////////////////////////
    
    Scene::Scene(const int light_count, const int obj_count, const int max_depth)
    {
        the_max_light_count = (light_count > 0) ? light_count : 0;
        the_light_list = new SceneLight*[the_max_light_count];    
        the_light_count = 0;
        
        the_max_obj_count = (obj_count > 0) ? obj_count : 0;
        the_obj_list = new SceneObject*[the_max_obj_count];
        the_obj_count = 0;
    
        the_distance_list = new DList[the_max_obj_count];
    
        if(!the_light_list || !the_distance_list || !the_obj_list)
        {
            cout << "\nOUT OF MEMORY: can not create scene.\n" << endl;
            the_max_light_count = 0;
            the_max_obj_count   = 0;
        }
    
        the_max_recursion_depth = max_depth;
    
        the_environment = NULL;
        the_observer    = NULL;
    }
    
    Scene::~Scene()
    {
        delete [] the_light_list;
        delete [] the_obj_list;
        delete [] the_distance_list;
    }
    
    
    //////////////////////////////////////////////////////////////////////
    // add_light
    //////////////////////////////////////////////////////////////////////
    
    void Scene::add_light(SceneLight *light)
    {
        if (the_light_count < the_max_light_count)
        {
            the_light_list[the_light_count] = light;
            the_light_count++;
        }
        else
        {
            cout << "\nOUT OF MEMORY: can not add light to scene. Scene memory not programmed flexible.\n" << endl;
        }
    }
    
    
    
    //////////////////////////////////////////////////////////////////////
    // add_object
    //////////////////////////////////////////////////////////////////////
    
    void Scene::add_object(SceneObject *obj)
    {
        if (the_obj_count < the_max_obj_count)
        {
            the_obj_list[the_obj_count] = obj;
            obj->set_scene(this);
            the_distance_list[the_obj_count].object_number = the_obj_count;
            the_obj_count++;
        }
        else
        {
            cout << "\nOUT OF MEMORY: can not add object to scene. Scene memory not programmed flexible.\n" << endl;
        }
    }
    
    
    
    //////////////////////////////////////////////////////////////////////
    // set_environment
    //////////////////////////////////////////////////////////////////////
    
    void Scene::set_environment(SceneEnvironment *env)
    {
        the_environment = env;
    }
    
    //////////////////////////////////////////////////////////////////////
    // set_observer
    //////////////////////////////////////////////////////////////////////
    
    void Scene::set_observer(Observer *observer)
    {
        the_observer = observer;
    }
    
    
    //////////////////////////////////////////////////////////////////////
    // draw
    //////////////////////////////////////////////////////////////////////
    
    void Scene::draw(Buffer &buffer, const float time, const float frame_width)
    {
        if (!the_environment)
        {
            cout << "\nERROR: No environment specified for scene, can not draw\n" << endl;
            return;
        }
        if (!the_observer)
        {
            cout << "\nERROR: No observer specified for scene, can not draw\n" << endl;
            return;
        }
    
        int buffer_width = buffer.get_width();
        int buffer_height = buffer.get_height();
    
    
    
        cout << endl;
        // MAIN WORK LOOP to find color for each position in buffer
        for(int y = 0; y < buffer_height; y++)
        {
            // progress meter
            cout << "\r" << 100*y/buffer_height << "%\t";
            cout.flush();
    
            for(int x = 0; x < buffer_width; x++)
            {
                //! Debug hook
                //if ( (x==50 ) && (y==50))
                //x = x + 1 - 1;

                // PRE PIXEL DISTRIBUTIONS
                float pixel_time = time + rand()/(float)RAND_MAX*frame_width - 0.5f*frame_width;            
                int i;
    
                the_observer->update_for_time(pixel_time); // MUST BE BEFORE OBJECT UPDATE
    
                for(i=0; i<the_max_obj_count; i++)
                    the_obj_list[i]->update_geometry(pixel_time);
    
                for(i=0; i<the_material_count; i++)
                    the_material_list[i]->update_for_time(pixel_time);
                
    
                // TRACE PIXEL RAY
                Vec3f jittered_coi = the_observer->make_jittered_coi(
                    x, buffer_width, y, buffer_height);            
                Vec3f lense_eye = the_observer->make_lense_eye();
                Vec3f direction = jittered_coi - lense_eye;
                
                buffer.put_color(x, y, trace_ray(lense_eye, direction.norm_value(), 1));
    
            }
        }
    
        cout << "\r100%\t";
        cout << endl;
    }
    

    

    void Scene::adaptive_draw(Buffer &buffer, const float time, const float frame_width, const int samples)
    {
        if (!the_environment)
        {
            cout << "\nERROR: No environment specified for scene, can not draw\n" << endl;
            return;
        }
        if (!the_observer)
        {
            cout << "\nERROR: No observer specified for scene, can not draw\n" << endl;
            return;
        }
    
        int buffer_width = buffer.get_width();
        int buffer_height = buffer.get_height();
    
        int start_samples = buffer.adaptive_total_samples;
    
        cout << endl;
        // MAIN WORK LOOP to find color for each position in buffer
        while(buffer.adaptive_total_samples < samples )
        {
            {
              FILE *fStopFileExists = fopen("stop", "r");
              if (fStopFileExists) 
              {
                fclose(fStopFileExists);        
                break;
              }        
            }

          // find next pixel to render
            cout << ".";
            cout.flush();
          float max = -1.0f;
          {
            int i;
            for(i = 0; i < buffer_height*buffer_width; i++)
              if (max < buffer.the_adaptive_stuff[i].z)
                max = buffer.the_adaptive_stuff[i].z;
          }
          
          for(int y = 0; y < buffer_height; y++)
          {
            for(int x = 0; x < buffer_width; x++)
            {
              if (buffer.the_adaptive_stuff[y*buffer_width+x].z >= max * 0.7) //!
              {
                //! Debug hook
                //if ( (x==50 ) && (y==50))
                //x = x + 1 - 1;
                
                // PRE PIXEL DISTRIBUTIONS
                float pixel_time = time + rand()/(float)RAND_MAX*frame_width - 0.5f*frame_width;            
                int i;
                
                the_observer->update_for_time(pixel_time); // MUST BE BEFORE OBJECT UPDATE
                
                for(i=0; i<the_max_obj_count; i++)
                  the_obj_list[i]->update_geometry(pixel_time);
                
                for(i=0; i<the_material_count; i++)
                  the_material_list[i]->update_for_time(pixel_time);
                
                
                // TRACE PIXEL RAY
                Vec3f jittered_coi = the_observer->make_jittered_coi(
                  x, buffer_width, y, buffer_height);            
                Vec3f lense_eye = the_observer->make_lense_eye();
                Vec3f direction = jittered_coi - lense_eye;
                
                buffer.put_color(x, y, trace_ray(lense_eye, direction.norm_value(), 1));
                
              }
            }
          }
        }

        cout << "did " << buffer.adaptive_total_samples - start_samples << " samples "<< endl;
    }

        
    //////////////////////////////////////////////////////////////////////
    // trace_ray
    //////////////////////////////////////////////////////////////////////
    
    Vec3f Scene::trace_ray(const Vec3f eye, const Vec3f dir, const int depth)
    {
        if (depth > the_max_recursion_depth) // Limit on recursion
        {
            return the_environment->get_universe_wall(dir);
            // return Vec3f();
        }
    
    
    
        /* 
            First we find distance to bounding spheres in 'the_distance_list'
            the list is sorted
            actual intersection tests are performed starting with the nearest
        */
    
        int i;
        float temp_t;
    
        // BOUNDING BOX INTERSECTION
        for(i=0; i<the_max_obj_count; i++)
        {
            switch(the_obj_list[the_distance_list[i].object_number]->intersect_bounding_sphere(
                eye, dir, temp_t))
            {
            case SceneObject::NO_INTERSECTION:
                the_distance_list[i].isect_type = SceneObject::NO_INTERSECTION;
                break;
            case SceneObject::OUTSIDE_INTERSECTION:
                the_distance_list[i].t = temp_t;
                the_distance_list[i].isect_type = SceneObject::OUTSIDE_INTERSECTION;
                break;
            case SceneObject::INSIDE_INTERSECTION:
                the_distance_list[i].t = temp_t;
                the_distance_list[i].isect_type = SceneObject::INSIDE_INTERSECTION;
                break;
            }
        }
    
        // SORT LIST to try to intersect closest objects first
        //! sort not yet implemented!
        {
            /*
            bool not_sorted;
            DList t_item;
            do {
                not_sorted = false;
                for(i=1; i<the_max_obj_count; i++)
                {
                    if ((the_distance_list[i-1].isect_type == SceneObject::NO_INTERSECTION) &&
                        (the_distance_list[i  ].isect_type != SceneObject::NO_INTERSECTION))
                    {
                        if ((the_distance_list[i-1].isect_type != SceneObject::NO_INTERSECTION) &&
                        (the_distance_list[i  ].isect_type != SceneObject::NO_INTERSECTION))
                        {                        
                            // swap
                            t_item = the_distance_list[i-1];
                            the_distance_list[i-1] = the_distance_list[i];
                            the_distance_list[i] = t_item; 
    
                            not_sorted = true;
                        }
                        else if (the_distance_list[i-1].t >
                                 the_distance_list[i  ].t) 
                        {
                            // swap
                            t_item = the_distance_list[i-1];
                            the_distance_list[i-1] = the_distance_list[i];
                            the_distance_list[i] = t_item; 
    
                            not_sorted = true;
                        }
                }
            } while(not_sorted);
            */
        }
    
        // FIND CLOSEST REAL INTERSECTION
        //! sort hasn't been implemented yet!
        {
            DList closest;
            closest.t = 999999999.9f; //! need a better infinity
            closest.object_number = -1;
            closest.isect_type = SceneObject::NO_INTERSECTION;
    
            for(i=0; i<the_max_obj_count; i++)
            {
                if(the_distance_list[i].isect_type == SceneObject::NO_INTERSECTION)
                {
                    continue;
                }
    
                the_distance_list[i].isect_type = 
                    the_obj_list[the_distance_list[i].object_number]->intersect(
                        eye, dir, 
                        the_distance_list[i].isect_type, 
                        the_distance_list[i].t);
    
                if (the_distance_list[i].isect_type == SceneObject::NO_INTERSECTION)
                {
                    continue;
                }
    
                if (the_distance_list[i].t < closest.t)
                {
                    closest = the_distance_list[i];
                }
            }
    
            if (closest.isect_type != SceneObject::NO_INTERSECTION)
            {
                Vec3f intersection_point = eye+closest.t*dir;
    
                return shade_object(closest.object_number, 
                                    intersection_point,
                                    closest.isect_type, 
                                    eye-intersection_point, 
                                    depth);
    
            }
            else
            {
                //! TODO Add object connection to compute background.
                return the_environment->get_universe_wall(dir);
            }
        }
    }
    
    
    
    //////////////////////////////////////////////////////////////////////
    // shade_object
    //////////////////////////////////////////////////////////////////////
    
    Vec3f Scene::shade_object(const int obj_num, 
                              const Vec3f point,
                              const SceneObject::Intersect_Type isect_type,
                              const Vec3f to_eye, // NOT normalized
                              const int depth)
    {
        Vec3f normal = the_obj_list[obj_num]->calculate_normal(); // Is already normalized
    
        // If surface is backface to eye REVERSE NORMAL
        if (normal.dot(to_eye) < 0)
            normal *= -1; 
    
        const Vec3f to_eye_normalized = to_eye.norm_value();
    
        // Get objects material
        Material* mat;  
        Material blank_mat;
        mat = the_obj_list[obj_num]->get_material();
        if (!mat) mat = &blank_mat; // if no material use blank material
    
        // Get the reflected ray vector (used for specular calc & reflected component)
        Vec3f reflected = 2*normal*normal.dot(to_eye_normalized) - to_eye_normalized;
    
        // Distribute the reflection vector over a solid angle.
        // Accomplished via a box filter over a disk perpendicular to the normal.
        // modifies: Vec3f 'reflected'
        {
            Vec3f up(0, 0, 1);
            Vec3f right = normal.cross(up);
            if (right.length() <= 0.0001f)
            {
                // If the light was directly above or below we need another 'up'
                right = normal.cross(Vec3f(1, 0, 0)); 
            }
            up = right.cross(normal);
    
            right.normalize();
            up.normalize();
    
            float x;
            float y;
            while(1)
            {
                x = rand()/(float)RAND_MAX*2.0f-1.0f;
                y = rand()/(float)RAND_MAX*2.0f-1.0f;
                if (1.0f >= sqrt(x*x + y*y)) break; // if random point in square is on disk
            }
    
            float disc_scale = (float)tan(mat->get_reflection_angle());
            reflected += disc_scale * y * up     + 
                         disc_scale * x * right;
            reflected.normalize();
        }
    
        // ILLUMINATION FROM LIGHTS ----------
    
        // AMBIENT LIGHT 
        Vec3f retColor = mat->get_color();
        retColor *= the_environment->get_ambient_light(); // Ambient //!
        //retColor *= mat->get_Kdiffuse() * the_environment->get_ambient_light(); // Ambient //!

    
        int i, j;
        for (i=0; i<the_light_count; i++) // Loop through all lights
        {
            Vec3f point_to_light = the_light_list[i]->getDirection(point); // NOT normalized
            Vec3f point_to_light_normalized = point_to_light.norm_value();
            float point_to_light_length = point_to_light.length();
            float transmission = 1.0f;
    
            // Check for backface with respect to light
            float nor_dot_light = normal.dot(point_to_light);
            if(nor_dot_light <= 0)
                continue; // Skip this light, it is behind face.
    
            // Shadows - check for intersection between here and light
            if (the_light_list[i]->cast_shadows && the_obj_list[obj_num]->receive_shadows)
            {
              float temp_t;
              Vec3f shadow_point = point + point_to_light_normalized * 0.001f;   // added by RMG
                         
              for(j=0; j<the_max_obj_count; j++)
              {
                if (!the_obj_list[j]->cast_shadows) continue; // some objects don't cast shadows
                    
                // Intersect bounding 
                SceneObject::Intersect_Type I = the_obj_list[j]->intersect_bounding_sphere(
                    shadow_point, point_to_light_normalized, temp_t);
                if (I != SceneObject::NO_INTERSECTION)
                {
                  // If intersection was between us and light
                  if (temp_t <= point_to_light_length) 
                  {
                    // Do real object intersection
                    SceneObject::Intersect_Type I = the_obj_list[the_distance_list[j].object_number]->intersect(
                      shadow_point, point_to_light_normalized, 
                      SceneObject::OUTSIDE_INTERSECTION, 
                      temp_t);
                    if (I != SceneObject::NO_INTERSECTION)
                    {
                      // If intersection was between us and light
                      if (temp_t >= 0 && temp_t <= point_to_light_length) 
                      {
                        // Reduce light trasmision according to this intersection.
                        transmission *= the_obj_list[j]->get_material()->get_Krefraction();
                        if (transmission < 0.001f) break; // Breaks object loop, 
                      }
                    }
                  }
                }
              } // End of object loop
              
              if (transmission < 0.001f) continue; // Full shadow. Skip this light source.
            } // end shadows
            
            // Add contribution for this light...
    
            Vec3f light_intensity = the_light_list[i]->calculate_intensity(point) * transmission;
    
    
            // DIFFUSE LIGHT (from this lightsource)
            float nor_dot_light_normalized = normal.dot(point_to_light_normalized);
            retColor += mat->get_color()
                        * light_intensity
                        * (nor_dot_light_normalized * mat->get_Kdiffuse()); 
    
    
            // SPECULAR LIGHT (from this lightsource)
            float power_reflect_dot_light =
                (float)pow(reflected.dot(point_to_light_normalized), mat->get_Kspecular_power());
            retColor += light_intensity * 
                        ( power_reflect_dot_light
                         * mat->get_Kspecular()); 
    
        } // End light source loop
    
    
        // REFLECTION
        if (mat->get_Kreflectance() && isect_type == SceneObject::OUTSIDE_INTERSECTION)
        {
            retColor += mat->get_Kreflectance() *
                        trace_ray(point+0.001f*reflected, reflected, depth+1);
        }
    
        // REFRACTION
        if (mat->get_Krefraction())
        {
            // Material densities hardwired here:
            float n;
            if (isect_type == SceneObject::OUTSIDE_INTERSECTION)
                n = 1 / the_obj_list[obj_num]->get_material()->get_density();
            else // INSIDE INTERSECTION
                n = the_obj_list[obj_num]->get_material()->get_density() / 1;
    
            float sqr = 1-n*n*(1 - (float)pow(normal.dot(to_eye_normalized), 2));
            if (sqr > 0) 
            {
                Vec3f refraction = (n*normal.dot(to_eye_normalized) - 
                                    (float)sqrt(sqr)) *
                                    normal - n*to_eye_normalized;
                refraction.normalize();
    
                // Distribute the refraction vector over a solid angle.
                // Accomplished via a box filter over a disk perpendicular to the normal.
                // modifies: Vec3f 'refraction'
                {
                    Vec3f up(0, 0, 1);
                    Vec3f right = normal.cross(up);
                    if (right.length() <= 0.0001f)
                    {
                        // If the light was directly above or below we need another 'up'
                        right = normal.cross(Vec3f(1, 0, 0)); 
                    }
                    up = right.cross(normal);
    
                    right.normalize();
                    up.normalize();
    
                    float x;
                    float y;
                    while(1)
                    {
                        x = rand()/(float)RAND_MAX*2.0f-1.0f;
                        y = rand()/(float)RAND_MAX*2.0f-1.0f;
                        if (1.0f >= sqrt(x*x + y*y)) break; // if random point in square is on disk
                    }
    
                    float disc_scale = (float)tan(mat->get_refraction_angle());
                    refraction += disc_scale * y * up     + 
                                  disc_scale * x * right;
                    refraction.normalize();
                }
    
                retColor += mat->get_Krefraction() *
                            trace_ray(point+0.001f*refraction, refraction, depth+1);
            }
            else
            {   
                // HEY! doesn't this mean that we are inside shooting out and that
                // we can't, so we should reflect inside instead!?!?? TEST THIS
                if (isect_type == SceneObject::OUTSIDE_INTERSECTION)
                cout << "\nWarning: Refraction calculation had square root domain error." << endl;
            }
        }
    
    
    
    
        // CLAMP COLORS
        retColor.clamp();
    
        //!
        /*    Alternate clamping style
        if(retColor[0]>1) retColor /= retColor[0];
        if(retColor[1]>1) retColor /= retColor[1];
        if(retColor[2]>1) retColor /= retColor[2];
        */
    
        return retColor;
    
    }
