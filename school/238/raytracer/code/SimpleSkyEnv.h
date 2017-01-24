// SimpleSkyEnv.h: interface for the SimpleSkyEnv class.
//
//////////////////////////////////////////////////////////////////////
//
// Environment with a simple sky and ground background, + ambient light
//

#ifndef SIMPLESKYENV_H
#define SIMPLESKYENV_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SceneEnvironment.h"

class SimpleSkyEnv : public SceneEnvironment  
{
public:
    SimpleSkyEnv(const Vec3f ambient_color = Vec3f(),
                 const Vec3f top_color =         Vec3f(0.0f, 0.6f, 1.0f),
                 const Vec3f horizon_top_color = Vec3f(0.9f, 0.9f, 1.0f),
                 const Vec3f horizon_bot_color = Vec3f(0.4f, 0.3f, 0.0f),
                 const Vec3f bot_color =         Vec3f(0.8f, 0.6f, 0.4f)) 
        {   the_ambient_color     = ambient_color    ;
            the_top_color         = top_color        ;
            the_horizon_top_color = horizon_top_color;
            the_horizon_bot_color = horizon_bot_color;
            the_bot_color         = bot_color        ; }

    virtual ~SimpleSkyEnv() { }

    // returns color at an infinite distance, the wall of the universe.
    virtual Vec3f get_universe_wall(const Vec3f dir);

protected:
    Vec3f the_top_color;
    Vec3f the_horizon_top_color;
    Vec3f the_horizon_bot_color;
    Vec3f the_bot_color;
};

#endif 
