// Observer.h: interface for the Observer class.
//
//////////////////////////////////////////////////////////////////////
//
// Observer / Camera class. 

#ifndef OBSERVER_H
#define OBSERVER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Vec3f.h"

class Observer  
{
public:
    Observer(const Vec3f position = Vec3f(1,0,0), 
        const Vec3f coi = Vec3f(0,0,0), 
        const float tilt_deg = 0, 
        const float angle_of_view_deg = 45,
        const float aspect_ratio = 1.0,
        const float lense_radius = 0.0,
        const float pixel_size   = 1.0);
    virtual ~Observer();
    
    virtual void add_keyframe(const float time,
        const Vec3f position = Vec3f(1,0,0), 
        const Vec3f coi = Vec3f(0,0,0), 
        const float tilt_deg = 0, 
        const float angle_of_view_deg = 45,
        const float aspect_ratio = 1.0,
        const float lense_radius = 0.0,
        const float pixel_size   = 1.0);
    
    virtual void update_for_time(const float time);
    
    Vec3f get_position() const{ return the_pos; }
    Vec3f get_coi() const{ return the_coi; } // returns normalized
    float get_tilt_rad() const{ return the_tilt; }
    float get_half_angle_fov_rad() const { return the_half_angle_fov; }
    float get_aspect_ratio() const { return the_aspect_ratio; }
    
    /*
    // Returns the eye position, the top left corner of the pixel array,
    // and the right and down width and height of that array.
    virtual void generate_pix_array_vecs(Vec3f &eye,
    Vec3f &top_left, 
    Vec3f &right_dir, 
    Vec3f &down_dir);
    */
    
    float get_lense_radius() const{ return the_lense_radius; }
    float get_pixel_size() const{ return the_pixel_size; }
    
    // returns an offset eye posistion distributed to be on a virtual lense
    Vec3f make_lense_eye(); 
    Vec3f make_jittered_coi(
        const int pix_x, 
        const int buffer_width,
        const int pix_y, 
        const int buffer_height); 
    
protected:
    Vec3f the_pos;
    Vec3f the_coi;
    float the_tilt;             // in radians
    float the_half_angle_fov;   // in radians
    float the_aspect_ratio;     // vertical / width
    float the_lense_radius;     // radius of the lens, causes depth of feild bluring
    float the_pixel_size;       // size of area to sample for a pixel (relative to actual size of a pixel)
    
    struct params {
        float time;     // Time of this keyframe
        params *next;   // pointer to next keyframe
        
        Vec3f pos;            
        Vec3f coi;            
        float tilt;           
        float half_angle_fov; 
        float aspect_ratio;   
        float lense_radius;   
        float pixel_size;     
    } *the_keyframes;
};

#endif 
