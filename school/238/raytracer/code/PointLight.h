// PointLight.h: interface for the PointLight class.
//
//////////////////////////////////////////////////////////////////////
//
// Simplest version of a point light
//

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "SceneLight.h"
#include "Vec3f.h"

class PointLight : public SceneLight 
{
public:
    PointLight(const Vec3f position=Vec3f(), 
        const float radius=0, 
        const Vec3f color=Vec3f())
    { 
        the_position=position; 
        the_radius=radius; 
        the_color=color; 
    }
    virtual ~PointLight();

    // DATA REPRESENTATION FUNCTIONS

    void setPosition(const Vec3f position) { the_position=position; }
    void setRadius(const float radius)     { the_radius=radius; }
    void setColor(const Vec3f color)       { the_color=color; }
    Vec3f getPosition() { return the_position; }
    Vec3f getColor()    { return the_color; }


    // LIGHTING CLACULATION FUNCTIONS:

        // Returns vector from point to light UN-NORMALIZED
    virtual Vec3f getDirection(const Vec3f point);
    
        // Returns color and intensity of light from this light
        // which reaches point
    virtual Vec3f calculate_intensity(const Vec3f point) { return the_color; }

protected:
    Vec3f the_position;
    float the_radius;
    Vec3f the_color;
};

#endif 
