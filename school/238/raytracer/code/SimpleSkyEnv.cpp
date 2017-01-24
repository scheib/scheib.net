// SimpleSkyEnv.cpp: implementation of the SimpleSkyEnv class.
//
//////////////////////////////////////////////////////////////////////

#include "SimpleSkyEnv.h"


//////////////////////////////////////////////////////////////////////
// get_universe_wall
//////////////////////////////////////////////////////////////////////

Vec3f SimpleSkyEnv::get_universe_wall(const Vec3f dir)
{
    if(dir.z > 0)
    {
        return (  dir.z)*the_top_color + 
               (1-dir.z)*the_horizon_top_color;
    }
    else
    {
        return (1+dir.z)*the_horizon_bot_color + 
               ( -dir.z)*the_bot_color;
    }
}
