// Material.cpp: implementation of the Material class.
//
//////////////////////////////////////////////////////////////////////

#include "Material.h"

#include <stdlib.h>

Material::Material(const Vec3f &color,
             const float Kd,
             const float Ks,
             const float Kn,
             const float Kl,
             const float Kr,
             const float density,
             const float reflection_angle,
             const float refraction_angle )
{   
    the_color = color;
    the_Kdiffuse = Kd;
    the_Kspecular = Ks;
    the_Kspecular_power = Kn;
    the_Kreflectance = Kl;
    the_Krefraction = Kr; 
    the_density = density; 
    the_reflection_angle = reflection_angle; 
    the_refraction_angle = refraction_angle; 

    the_keyframes = new params;
    the_keyframes->time = 0;
    the_keyframes->next = NULL;

    the_keyframes->color = color;                       
    the_keyframes->Kdiffuse = Kd;                       
    the_keyframes->Kspecular = Ks;                      
    the_keyframes->Kspecular_power = Kn;                
    the_keyframes->Kreflectance = Kl;                   
    the_keyframes->Krefraction = Kr;                    
    the_keyframes->density = density;                   
    the_keyframes->reflection_angle = reflection_angle; 
    the_keyframes->refraction_angle = refraction_angle; 
}

Material::~Material() 
{ 
    // Delete keyframe list

    params *list_reader;

    while(the_keyframes->next)
    {
        list_reader = the_keyframes;

        while( list_reader->next->next != NULL )
            list_reader = list_reader->next;

        delete list_reader->next;
        list_reader->next = NULL;
    }

    delete the_keyframes;
}



void  Material::set_color(const Vec3f &c)           { the_color = c; }
void  Material::set_Kdiffuse(const float Kd)        { the_Kdiffuse = Kd; }
void  Material::set_Kspecular(const float Ks)       { the_Kspecular = Ks; }
void  Material::set_Kspecular_power(const float Kn) { the_Kspecular_power = Kn; }
void  Material::set_Kreflectance(const float Kl)    { the_Kreflectance = Kl; }
void  Material::set_Krefraction(const float Kr)     { the_Krefraction = Kr; }
void  Material::set_density(const float density)    { the_density = density; }
void  Material::set_reflection_angle(const float angle) { the_reflection_angle=angle;}
void  Material::set_refraction_angle(const float angle) { the_refraction_angle=angle;}

Vec3f Material::get_color()           { return the_color;           }
float Material::get_Kdiffuse()        { return the_Kdiffuse;        }
float Material::get_Kspecular()       { return the_Kspecular;       }
float Material::get_Kspecular_power() { return the_Kspecular_power; }
float Material::get_Kreflectance()    { return the_Kreflectance;    }
float Material::get_Krefraction()     { return the_Krefraction;     }
float Material::get_density()         { return the_density;         }
float Material::get_reflection_angle(){ return the_reflection_angle;}
float Material::get_refraction_angle(){ return the_refraction_angle;}


void Material::add_keyframe(const float time,
             const Vec3f &color,
             const float Kd,
             const float Ks,
             const float Kn,
             const float Kl,
             const float Kr,
             const float density,
             const float reflection_angle,
             const float refraction_angle)
{   
    params *new_keyframe;
    new_keyframe = new params;
    new_keyframe->time = time;
    new_keyframe->next = NULL;

    new_keyframe->color = color;                       
    new_keyframe->Kdiffuse = Kd;                       
    new_keyframe->Kspecular = Ks;                      
    new_keyframe->Kspecular_power = Kn;                
    new_keyframe->Kreflectance = Kl;                   
    new_keyframe->Krefraction = Kr;                    
    new_keyframe->density = density;                   
    new_keyframe->reflection_angle = reflection_angle; 
    new_keyframe->refraction_angle = refraction_angle; 

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


void Material::update_for_time(const float time)
{
    if ( the_keyframes->next == NULL ) return; // If we have no keyframes to interp. quit

    if (the_keyframes->time >= time) 
    {
        // Use the first keyframe only, time was less than first keyframe.
        the_color =            the_keyframes->color;
        the_Kdiffuse =         the_keyframes->Kdiffuse;
        the_Kspecular =        the_keyframes->Kspecular;          
        the_Kspecular_power =  the_keyframes->Kspecular_power;          
        the_Kreflectance =     the_keyframes->Kreflectance;          
        the_Krefraction =      the_keyframes->Krefraction;          
        the_density =          the_keyframes->density;   
        the_reflection_angle = the_keyframes->reflection_angle;
        the_refraction_angle = the_keyframes->refraction_angle;   
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
            
            the_color =            list_reader->color;
            the_Kdiffuse =         list_reader->Kdiffuse;
            the_Kspecular =        list_reader->Kspecular;          
            the_Kspecular_power =  list_reader->Kspecular_power;          
            the_Kreflectance =     list_reader->Kreflectance;          
            the_Krefraction =      list_reader->Krefraction;          
            the_density =          list_reader->density;   
            the_reflection_angle = list_reader->reflection_angle;
            the_refraction_angle = list_reader->refraction_angle;   
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

    the_color =            m1->color + t*(m2->color - m1->color);           
    the_Kdiffuse =         m1->Kdiffuse + t*(m2->Kdiffuse - m1->Kdiffuse);            
    the_Kspecular =        m1->Kspecular + t*(m2->Kspecular - m1->Kspecular);           
    the_Kspecular_power =  m1->Kspecular_power + t*(m2->Kspecular_power - m1->Kspecular_power);            
    the_Kreflectance =     m1->Kreflectance + t*(m2->Kreflectance - m1->Kreflectance);           
    the_Krefraction =      m1->Krefraction + t*(m2->Krefraction - m1->Krefraction);            
    the_density =          m1->density + t*(m2->density - m1->density);       
    the_reflection_angle = m1->reflection_angle + t*(m2->reflection_angle - m1->reflection_angle);
    the_refraction_angle = m1->refraction_angle + t*(m2->refraction_angle - m1->refraction_angle);    
}
