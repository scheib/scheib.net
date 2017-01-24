// Vec3f.h: interface for the Vec3f class.
//
//////////////////////////////////////////////////////////////////////
// Vincent Scheib
//
// 3 Component Vector class
//
//-
//00-09-11 changed accessor from switch to cascaded if 


#ifndef VEC3_H
#define VEC3_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <assert.h>
#include <iostream.h>
#include <math.h>
#include "Mat3.h"

class Vec3f  
{
public:
	Vec3f( const float _x = 0.0f, 
           const float _y = 0.0f, 
           const float _z = 0.0f )
        { x = _x;  y = _y;  z = _z; }
	Vec3f( const Vec3f &vec )  
        { x = vec.x;  y = vec.y;  z = vec.z; }
    //virtual ~Vec3f() 
    //    { }
    
    // DATA MEMBERS
    /////////////////

    float x;
    float y;
    float z;
    
    // FUNCTION MEMEBERS
    //==================

    // Accessor	
    float &operator[]( const int &i )           // [0], [1], [2] return x, y, z
		{      if (i == 0) return x;
		  else if (i == 1) return y;
		  else if (i == 2) return z;
		  else assert(0); return x;
		}

    // Vector Addition
    Vec3f operator+( const Vec3f & vec ) const  // returns this + vec
        { return Vec3f(x+vec.x, y+vec.y, z+vec.z); } 
    Vec3f &operator+=( const Vec3f & vec )      // this += vec
        { x+=vec.x; y+=vec.y; z+=vec.z;
          return *this; } 

    // Vector Subtraction
    Vec3f operator-() const                     // returns -this
        { return Vec3f(-x, -y, -z); } 
    Vec3f operator-( const Vec3f & vec ) const  // returns this - vec
        { return Vec3f(x-vec.x, y-vec.y, z-vec.z); } 
    Vec3f &operator-=( const Vec3f & vec )      // this -= vec
        { x-=vec.x; y-=vec.y; z-=vec.z;
	      return *this; } 

    // Scaling Multiplication
    Vec3f operator*( const float f ) const      // returns this * f
        { return Vec3f(x*f, y*f, z*f); } 
    friend Vec3f operator*( const float f, const Vec3f &vec )  // returns f * this
        { return Vec3f(vec.x*f, vec.y*f, vec.z*f); } 
    Vec3f &operator*=( const float f )          // this *= f
        { x*=f; y*=f; z*=f;
          return *this; } 

    // Scaling Division
    Vec3f operator/( const float f ) const      // returns this / f
        { return Vec3f(x/f, y/f, z/f); } 
    Vec3f &operator/=( const float f )          // this /= f
        { x/=f; y/=f; z/=f;
          return *this; } 

    // Vector Multiplication
    Vec3f operator*( const Vec3f & vec ) const  // !WARNING (MEMBERWISE): returns this.? * vec.?
        { return Vec3f(x*vec.x, y*vec.y, z*vec.z); } 
    Vec3f &operator*=( const Vec3f & vec )      // !WARNING (MEMBERWISE): this.? *= vec.?
        { x*=vec.x; y*=vec.y; z*=vec.z;
          return *this; } 

    // Vector Division
    Vec3f operator/( const Vec3f & vec ) const  // !WARNING (MEMBERWISE): returns this.? / vec.?
        { return Vec3f(x/vec.x, y/vec.y, z/vec.z); } 
    Vec3f &operator/=( const Vec3f & vec )      // !WARNING (MEMBERWISE): this.? /= vec.?
        { x/=vec.x; y/=vec.y; z/=vec.z;
          return *this; } 

    // Dot Product
    float dot( const Vec3f & vec ) const        // returns dot value of this and vec
        { return x*vec.x + y*vec.y + z*vec.z; } 
    
    // Cross Product
    Vec3f cross( const Vec3f & vec ) const      // returns cross product of this and vec
        { return Vec3f(y*vec.z - z*vec.y, 
                       z*vec.x - x*vec.z, 
                       x*vec.y - y*vec.x); } 
    Vec3f &cross_equals( const Vec3f & vec )    // this = this cross vec
        { float _x = y*vec.z - z*vec.y;
          float _y = z*vec.x - x*vec.z; 
          float _z = x*vec.y - y*vec.x;
          x = _x;  y = _y;  z = _z; 
          return *this; } 

    // Length
    float length() const                // returns length
        { return (float)sqrt(x*x + y*y + z*z); } 
    float length_square() const         // returns length squared
        { return (x*x + y*y + z*z); } 
    
    // Normalize
    Vec3f &normalize()                  // normalizes this
        { float f=(float)sqrt(x*x + y*y + z*z);
          x/=f; y/=f; z/=f;
          return *this; } 
    Vec3f norm_value() const            // returns normalized value, does not modify this
        { float f=length();
          return Vec3f(x/f, y/f, z/f); } 

    // Clamping
    Vec3f &clamp(const float min = 0.0f,    // clamps this to range specified, default 0-1
                 const float max = 1.0f)
        { if (x < min) x = min; if (x > max) x = max;
          if (y < min) y = min; if (y > max) y = max;
          if (z < min) z = min; if (z > max) z = max;
          return *this; }


    // Print
    friend ostream &operator<<( ostream &o, const Vec3f vec )
        { return o << vec.x << " " << vec.y << " " << vec.z; }

    // Crank a vector through a matrix
    Vec3f operator* (const Matrix& mat) const
    {
      Vec3f ret;
      ret.x = x*mat.mat[0][0] + y*mat.mat[1][0] + z*mat.mat[2][0] + mat.mat[3][0];
      ret.y = x*mat.mat[0][1] + y*mat.mat[1][1] + z*mat.mat[2][1] + mat.mat[3][1];
      ret.z = x*mat.mat[0][2] + y*mat.mat[1][2] + z*mat.mat[2][2] + mat.mat[3][2];
      //float w = x*mat.mat[0][3] + y*mat.mat[1][3] + z*mat.mat[2][3] + mat.mat[3][3];
      //ret.x /= w;
      //ret.y /= w;
      //ret.z /= w;
      return ret;
    }

    // Crank a vector through a matrix
    void operator*=(const Matrix& mat)
    {
      Vec3f vec = *this;
      x = vec.x*mat.mat[0][0] + vec.y*mat.mat[1][0] + vec.z*mat.mat[2][0] + mat.mat[3][0];
      y = vec.x*mat.mat[0][1] + vec.y*mat.mat[1][1] + vec.z*mat.mat[2][1] + mat.mat[3][1];
      z = vec.x*mat.mat[0][2] + vec.y*mat.mat[1][2] + vec.z*mat.mat[2][2] + mat.mat[3][2];
      //float w = vec.x*mat.mat[0][3] + vec.y*mat.mat[1][3] + vec.z*mat.mat[2][3] + mat.mat[3][3];
      //x /= w;
      //y /= w;
      //z /= w;
    }

};



#endif

