// Observer.cpp: implementation of the Observer class.
//
//////////////////////////////////////////////////////////////////////

#include "Observer.h"

#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Observer::Observer(const Vec3f position, 
                   const Vec3f coi, 
                   const float tilt_deg, 
                   const float angle_of_view_deg,
                   const float aspect_ratio,
                   const float lense_radius,
                   const float pixel_size)
{
    the_pos = position;
    the_coi = coi;
    the_tilt = tilt_deg / 180.0f * 3.14159f;
    the_half_angle_fov = (0<=angle_of_view_deg ) ?
        angle_of_view_deg / 2.0f / 180.0f * 3.14159f
        : angle_of_view_deg; // If negative then this is in distance units, not degrees
    the_aspect_ratio = aspect_ratio;
    the_lense_radius = lense_radius;
    the_pixel_size   = pixel_size;  

    the_keyframes = new params;
    the_keyframes->time = 0;
    the_keyframes->next = NULL;

    the_keyframes->pos            = the_pos;
    the_keyframes->coi            = the_coi;           
    the_keyframes->tilt           = the_tilt;          
    the_keyframes->half_angle_fov = the_half_angle_fov;
    the_keyframes->aspect_ratio   = the_aspect_ratio;  
    the_keyframes->lense_radius   = the_lense_radius;  
    the_keyframes->pixel_size     = the_pixel_size;    
}

Observer::~Observer()
{

}

/*
void Observer::generate_pix_array_vecs(Vec3f &eye,
                                       Vec3f &top_left, 
                                       Vec3f &right_dir, 
                                       Vec3f &down_dir)
{
    eye = the_pos;

    // Calculate 
    Vec3f direction = (the_coi - the_pos);
    Vec3f temp_up(0,0,1); // temporarily the z axis
    Vec3f temp_right = direction .cross(temp_up);
    temp_up = temp_right.cross(direction );

    // Head Tilt
    temp_up.normalize();
    temp_right.normalize();

    right_dir = temp_right * (float) cos(the_tilt) + temp_up * (float)sin(the_tilt);
    Vec3f up =  temp_right * (float)-sin(the_tilt) + temp_up * (float)cos(the_tilt);

    right_dir.normalize();
    down_dir = -up.norm_value();



    float half_width_scaler = (float)tan(the_half_angle_fov) * direction.length();
    float half_height_scaler = half_width_scaler * the_aspect_ratio;

    top_left = eye + direction  
               - half_width_scaler*right_dir
               - half_height_scaler*down_dir;
    
    right_dir *= 2*half_width_scaler;
    down_dir  *= 2*half_height_scaler;
}
*/

Vec3f Observer::make_lense_eye()
{
    // BOX FILTER:

    Vec3f up(0, 0, 1);
    Vec3f right = (the_coi-the_pos).cross(up);
    up = right.cross(the_coi-the_pos);

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

    return the_pos 
        + the_lense_radius * y * up
        + the_lense_radius * x * right;

    // TENT FILTER 
/*    Vec3f up(0, 0, 1);
    Vec3f right = (the_coi-eye).cross(up);
    up = right.cross(the_coi-eye);

    right.normalize();
    up.normalize();

    float rand_angle = rand()/(float)RAND_MAX*6.283f; // Angle from 0 to 360 degrees (in rad)
    float rand_mag = rand()/(float)RAND_MAX;

    return eye 
        + the_lense_radius * rand_mag * (float)sin(rand_angle) * up
        + the_lense_radius * rand_mag * (float)cos(rand_angle) * right;
*/

}


Vec3f Observer::make_jittered_coi(
        const int pix_x, 
        const int buffer_width,
        const int pix_y, 
        const int buffer_height)
{

    // Calculate 
    Vec3f direction = (the_coi - the_pos); // not normalized
    Vec3f temp_up(0,0,1); // temporarily the z axis
    Vec3f temp_right = direction .cross(temp_up);
    temp_up = temp_right.cross(direction );

    // Head Tilt
    temp_up.normalize();
    temp_right.normalize();

    Vec3f right_dir = temp_right * (float) cos(the_tilt) + temp_up * (float)sin(the_tilt);
    Vec3f up =  temp_right * (float)-sin(the_tilt) + temp_up * (float)cos(the_tilt);

    right_dir.normalize();
    Vec3f down_dir = -up.norm_value();

    float half_width_scaler;
    float half_height_scaler;
    if (0 <= the_half_angle_fov)
    {
        half_width_scaler = (float)tan(the_half_angle_fov) * direction.length();
        half_height_scaler = half_width_scaler * the_aspect_ratio;
    }
    else // the_half_angle_fov is negative, it specifies the width of the frame at the coi
    {
        half_width_scaler = -0.5f * the_half_angle_fov;
        half_height_scaler = half_width_scaler * the_aspect_ratio;
    }

    Vec3f top_left = the_coi  
               - half_width_scaler*right_dir
               - half_height_scaler*down_dir;
    
    right_dir *= 2*half_width_scaler;
    down_dir  *= 2*half_height_scaler;

    // Now find the point of the pixel, offset by the jitter

    float rand_mag1 = the_pixel_size * (rand()/(float)RAND_MAX - 0.5f);
    float rand_mag2 = the_pixel_size * (rand()/(float)RAND_MAX - 0.5f);

    return top_left
        + (pix_x + rand_mag1) / (float)buffer_width  * right_dir
        + (pix_y + rand_mag2) / (float)buffer_height * down_dir;
}


void Observer::add_keyframe(const float time,
                      const Vec3f position,
                      const Vec3f coi,
                      const float tilt_deg,
                      const float angle_of_view_deg,
                      const float aspect_ratio,
                      const float lense_radius,
                      const float pixel_size)
{
    params *new_keyframe;
    new_keyframe = new params;
    new_keyframe->time = time;
    new_keyframe->next = NULL;

    new_keyframe->pos            = position;
    new_keyframe->coi            = coi;           
    new_keyframe->tilt           = tilt_deg / 180.0f * 3.14159f;          
    new_keyframe->half_angle_fov = (0<=angle_of_view_deg ) ?
        angle_of_view_deg / 2.0f / 180.0f * 3.14159f
        : angle_of_view_deg; // If negative then this is in distance units, not degrees
    new_keyframe->aspect_ratio   = aspect_ratio;  
    new_keyframe->lense_radius   = lense_radius;  
    new_keyframe->pixel_size     = pixel_size;    

    // Add to existing list
    params *list_reader = the_keyframes;
    while( list_reader->next != NULL )
        list_reader = list_reader->next;

    list_reader->next = new_keyframe;
    if (list_reader->time >= new_keyframe->time)
    {
        cout << "ERROR: Keyframe specified with a time of " << time
            << "\nbut the last keyframe was at time " << list_reader->time
            << "\nKeyframes MUST be specified in order." << endl;
        exit(666);
    }
}


void Observer::update_for_time(const float time)
{
    if ( the_keyframes->next == NULL ) return; // If we have no keyframes to interp. quit
    
    if (the_keyframes->time >= time) 
    {
        // Use the first keyframe only, time was less than first keyframe.
        the_pos            =  the_keyframes->pos            ;
        the_coi            =  the_keyframes->coi            ;
        the_tilt           =  the_keyframes->tilt           ;
        the_half_angle_fov =  the_keyframes->half_angle_fov ;
        the_aspect_ratio   =  the_keyframes->aspect_ratio   ;
        the_lense_radius   =  the_keyframes->lense_radius   ;
        the_pixel_size     =  the_keyframes->pixel_size     ;
        return;
    }
    
    // Find the two keyframes to interpolate between.
    params *list_reader = the_keyframes;
    while( list_reader->next != NULL )
    {        

        if (list_reader->time <= time &&
            list_reader->next->time > time)
            break; // We have the two keyframes to interp between.
            // Break and interp outside of wile loop.
        
        if (list_reader->next->next == NULL) 
        {
            // We've run out of keyframes, use the last one
            list_reader = list_reader->next;
            
            the_pos            =  list_reader->pos            ;
            the_coi            =  list_reader->coi            ;
            the_tilt           =  list_reader->tilt           ;
            the_half_angle_fov =  list_reader->half_angle_fov ;
            the_aspect_ratio   =  list_reader->aspect_ratio   ;
            the_lense_radius   =  list_reader->lense_radius   ;
            the_pixel_size     =  list_reader->pixel_size     ;
            return;
        }
       
        // Check next keyframes
        list_reader = list_reader->next;
    }

    // list_reader and list_reader->next are the frames to interp between.
    // INTERPOLATE and store in standard member variables

    params *m1 = list_reader;
    params *m2 = list_reader->next;
    float t = (time - m1->time)/(m2->time - m1->time);

    the_pos            =  m1->pos + t*(m2->pos - m1->pos);
    the_coi            =  m1->coi + t*(m2->coi - m1->coi);
    the_tilt           =  m1->tilt + t*(m2->tilt - m1->tilt); 
    the_half_angle_fov =  m1->half_angle_fov + t*(m2->half_angle_fov - m1->half_angle_fov); 
    the_aspect_ratio   =  m1->aspect_ratio + t*(m2->aspect_ratio - m1->aspect_ratio);  
    the_lense_radius   =  m1->lense_radius + t*(m2->lense_radius - m1->lense_radius);  
    the_pixel_size     =  m1->pixel_size + t*(m2->pixel_size - m1->pixel_size);    
}