// Material.h: interface for the Material class.
//
//////////////////////////////////////////////////////////////////////
// 
// Material properties for an object. 
// 

#ifndef MATERIAL
#define MATERIAL

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vec3f.h"

class Material  
{
public:
    Material(const Vec3f &color = Vec3f(1.0f,1.0f,1.0f),
             const float Kd = 1.0f,
             const float Ks = 0.0f,
             const float Kn = 1.0f,
             const float Kl = 0.0f,
             const float Kr = 0.0f,
             const float density = 1.1f,
             const float reflection_angle = 1.0f,
             const float refraction_angle = 1.0f);

    virtual ~Material();

    virtual void add_keyframe(const float time,
             const Vec3f &color = Vec3f(1.0f,1.0f,1.0f),
             const float Kd = 1.0f,
             const float Ks = 0.0f,
             const float Kn = 1.0f,
             const float Kl = 0.0f,
             const float Kr = 0.0f,
             const float density = 1.1f,
             const float reflection_angle = 1.0f,
             const float refraction_angle = 1.0f);

    virtual void update_for_time(const float time);

    // Watch out. If animating a material these won't work right.
    virtual void  set_color(const Vec3f &c)           ;
    virtual void  set_Kdiffuse(const float Kd)        ;
    virtual void  set_Kspecular(const float Ks)       ;
    virtual void  set_Kspecular_power(const float Kn) ;
    virtual void  set_Kreflectance(const float Kl)    ;
    virtual void  set_Krefraction(const float Kr)     ;
    virtual void  set_density(const float density)    ;
    virtual void  set_reflection_angle(const float angle);
    virtual void  set_refraction_angle(const float angle);

    virtual Vec3f get_color()           ;
    virtual float get_Kdiffuse()        ;
    virtual float get_Kspecular()       ;
    virtual float get_Kspecular_power() ;
    virtual float get_Kreflectance()    ;
    virtual float get_Krefraction()     ;
    virtual float get_density()         ;
    virtual float get_reflection_angle();
    virtual float get_refraction_angle();

protected:
    Vec3f the_color;
    float the_Kdiffuse;
    float the_Kspecular;
    float the_Kspecular_power;
    float the_Kreflectance;
    float the_Krefraction;
    float the_density;
    float the_reflection_angle; // Angle (RAD) to distribute reflections over
    float the_refraction_angle; // Angle (RAD) to distribute refractions over

    struct params {
        float time;     // Time of this keyframe
        params *next;   // pointer to next keyframe

        Vec3f color;
        float Kdiffuse;
        float Kspecular;
        float Kspecular_power;
        float Kreflectance;
        float Krefraction;
        float density;
        float reflection_angle;
        float refraction_angle;
    } *the_keyframes;

};

#endif
