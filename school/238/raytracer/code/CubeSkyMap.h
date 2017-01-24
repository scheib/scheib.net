// CubeSkyMap.h: interface for the CubeSkyMap class.
//
//////////////////////////////////////////////////////////////////////
//
// Cube Texture Mapped environment

#ifndef CUBESKYMAP_H
#define CUBESKYMAP_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SceneEnvironment.h"
#include "Buffer.h"

class CubeSkyMap : public SceneEnvironment  
{
public:
	CubeSkyMap(const Vec3f ambient,
               const Vec3f background,
               const char* file_z, 
               const char* file_x, 
               const char* file_y, 
               const char* file_nx, 
               const char* file_ny, 
               const char* file_nz);
	//virtual ~CubeSkyMap();

    // returns color at an infinite distance, the wall of the universe.
    virtual Vec3f get_universe_wall(const Vec3f dir);

protected:

	Buffer 
		buffer_z , 
		buffer_x , 
		buffer_y , 
		buffer_nx, 
		buffer_ny, 
		buffer_nz; // top, right, front, left, back, bottom
};

#endif 
