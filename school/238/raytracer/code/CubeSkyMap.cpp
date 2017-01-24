// CubeSkyMap.cpp: implementation of the CubeSkyMap class.
//
//////////////////////////////////////////////////////////////////////

#include "CubeSkyMap.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CubeSkyMap::CubeSkyMap(const Vec3f ambient,
                       const Vec3f background,
                       const char* file_z, 
                       const char* file_x, 
                       const char* file_y, 
                       const char* file_nx, 
                       const char* file_ny, 
                       const char* file_nz) : SceneEnvironment(ambient, background)
{
	buffer_z.ReadTGA(file_z);
	buffer_x.ReadTGA(file_x);
	buffer_y.ReadTGA(file_y);
	buffer_nx.ReadTGA(file_nx);
	buffer_ny.ReadTGA(file_ny);
	buffer_nz.ReadTGA(file_nz);
}


//////////////////////////////////////////////////////////////////////
// get_universe_wall
//////////////////////////////////////////////////////////////////////

Vec3f CubeSkyMap::get_universe_wall(const Vec3f dir)
{
    float x = dir.x;
    float y = dir.y;
    float z = dir.z;
    float ax = (x<0) ? -x : x;
    float ay = (y<0) ? -y : y;
    float az = (z<0) ? -z : z; // also functions as direction to plane

    Buffer *buffer = NULL;

//    int pixel_x, pixel_y;

    switch ( 4*(ax > ay) + 2*(ay > az) + 1*(az > ax) )
    {
    case 0: // all equal
    case 1: // z
      if (z >= 0) { buffer = &buffer_z;  az = z; ax = x; ay =  y; } // debug  return Vec3f(0.0,0.0,1.0); }
      else        { buffer = &buffer_nz; az =-z; ax = x; ay = -y; } // debug  return Vec3f(0.0,0.0,0.5); }
      break;
    case 2: // y
    case 3: // y
      if (y >= 0) { buffer = &buffer_y;  az = y; ax = x; ay = -z; } // debug  return Vec3f(0.0,1.0,0.0); }
      else        { buffer = &buffer_ny; az =-y; ax =-x; ay = -z; } // debug  return Vec3f(0.0,0.5,0.0); }
      break;
    case 4: // x
      if (x >= 0) { buffer = &buffer_x;  az = x; ax =-y; ay = -z; } // debug  return Vec3f(1.0,0.0,0.0); }
      else        { buffer = &buffer_nx; az =-x; ax = y; ay = -z; } // debug  return Vec3f(0.5,0.0,0.0); }
      break;
    case 5: // z
      if (z >= 0) { buffer = &buffer_z;  az = z; ax = x; ay =  y; } // debug  return Vec3f(0.0,0.0,1.0); }
      else        { buffer = &buffer_nz; az =-z; ax = x; ay = -y; } // debug  return Vec3f(0.0,0.0,0.5); }
      break;
    case 6: // x
    case 7: // never should
    default:
      if (x >= 0) { buffer = &buffer_x;  az = x; ax =-y; ay = -z; } // debug  return Vec3f(1.0,0.0,0.0); }
      else        { buffer = &buffer_nx; az =-x; ax = y; ay = -z; } // debug  return Vec3f(0.5,0.0,0.0); }
      break;
    }

//    pixel_x = (int)( ((ax/az)/2 + 0.5)*buffer->get_width()  );
    //pixel_y = (int)( ((ay/az)/2 + 0.5)*buffer->get_height() );
    ax = ((ax/az)/2 + (float)0.5)*buffer->get_width() ;
    ay = ((ay/az)/2 + (float)0.5)*buffer->get_height();


    //if (pixel_x < 0) pixel_x = 0;
    //if (pixel_y < 0) pixel_y = 0;
    //if (pixel_x >=buffer->get_width())  pixel_x = buffer->get_width()-1;
    //if (pixel_y >=buffer->get_height()) pixel_y = buffer->get_height()-1;

    // debug  return Vec3f( ((float)pixel_x)/buffer->get_width(), ((float)pixel_y)/buffer->get_height(),  0.5);

    return buffer->get_color(ax, ay)*the_background_color; 
}

