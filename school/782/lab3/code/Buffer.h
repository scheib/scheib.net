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
    void WriteTGA(char *filename);
    void ReadTGA(char *filename);
    int  get_width()  { return the_width;  }
    int  get_height() { return the_height; }

protected:
    // DATA MEMBERS
    ////////////////
    Vec3f *the_buffer;
    int the_width;
    int the_height;
    
};

#endif 
