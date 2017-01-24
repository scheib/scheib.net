// Buffer.h: interface for the Buffer class.
//
//////////////////////////////////////////////////////////////////////
// Vincent Scheib
//
// TODO: make this buffer much more generalized.
//
//
// Buffer origin is in TOP LEFT

#ifndef BUFFER_H
#define BUFFER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Vec3f.h"

class Buffer  
{
public:
    // Constructor/Destructor
    //////////////////////////
	Buffer(const int w = 0, const int h = 0);
	virtual ~Buffer();

    // Member Fucntions
    /////////////////////
    void Clear(const Vec3f color = Vec3f(0,0,0));
	virtual void put_color(const int x, const int y, const Vec3f color);
	virtual const Vec3f get_color(const int x, const int y);
	virtual const Vec3f get_color(const float x, const float y); // Linear Interpolation
	virtual const Vec3f get_color_01(const float x, const float y); // Linear Interpolation
    void WriteTGA(const char *filename);
    void ReadTGA(const char *filename);
    void WriteAdaptive(const char *filename);
    void WriteAdaptiveDebug(const char *filename);
    void ReadAdaptive(const char *filename);
    int  get_width()  { return the_width;  }
    int  get_height() { return the_height; }
    void makeAdaptive(); //! SO such a HACK -- needs overhaul I garrontee
/*
    void dosort(); //! SO such a HACK -- needs overhaul I garrontee
    void insert(const int i); //! SO such a HACK -- needs overhaul I garrontee
*/

    ///!!!!!!!!!!!!!!!
    int is_adaptive;
    Vec3f *the_adaptive_stuff; /// .x is weights .y is error  z error/weight
  /*
  struct sorter {
      sorter * prev;
      sorter * next;
    } *the_sorter; 
    //struct sorter sorthead;
    //struct sorter sorttail;
*/

    int adaptive_full_screen_count;
    int adaptive_total_samples;

protected:
    // DATA MEMBERS
    ////////////////
    Vec3f *the_buffer;
    int the_width;
    int the_height;

    
};

#endif 
