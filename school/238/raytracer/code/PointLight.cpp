// PointLight.cpp: implementation of the PointLight class.
//
//////////////////////////////////////////////////////////////////////

#include "PointLight.h"

#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PointLight::~PointLight()
{

}

inline Vec3f PointLight::getDirection(const Vec3f point)
{ 
    // Biased for inner point of light source filter:
/*
    // Randomly distribute the position of the point light in a sphere 
    // around the_point with a max distance of the_radius
    
    // angle1 is angle down from z axis, angle 2 is angle rotated around z axis

    float angel1 = rand()/(float)RAND_MAX*3.141f; // Angle from 0 to 180 degrees (but in rad)                                
    float angel2 = rand()/(float)RAND_MAX*6.283f; // Angle from 0 to 360 degrees (but in rad)
    float xy_magnitude = (float)(the_radius * rand()/(float)RAND_MAX * sin(angel1)); 

    return     the_position + Vec3f( // random offset
        (float)(xy_magnitude * cos(angel2)),
        (float)(xy_magnitude * sin(angel2)), 
        (float)(the_radius * cos(angel1))
        ) 
        - point; 
*/

    // BOX FILTER over a disk perpendicular to the direction to the point:

    Vec3f to_point(point - the_position);
    Vec3f up(0, 0, 1);
    Vec3f right = to_point.cross(up);
    if (right.length() <= 0.0001f)
    {
        // If the light was directly above or below we need another 'up'
        right = to_point.cross(Vec3f(1, 0, 0)); 
    }
    up = right.cross(to_point);

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

    return the_position
        + the_radius * y * up
        + the_radius * x * right
        - point;

}