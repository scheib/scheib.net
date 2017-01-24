// Mat3.h: interface for the Matrix class.
//
//////////////////////////////////////////////////////////////////////
// Vincent Scheib
//
// 3x3 Matrix class
//

#ifndef MAT3_H
#define MAT3_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <assert.h>
#include <iostream.h>


class Matrix
{
public:

   // THE ONLY DATA MEMBER
   float mat[4][4];


   // MEMBER FUNCTIONS

   void identity()       // Builds an Identity matrix.
   {
     for (int i = 0 ; i < 4 ; ++i)
       for (int j = 0 ; j < 4 ; ++j)
         mat[i][j] = ( i == j ) ? (float) 1.0 : (float) 0.0;
   }

   void scale(float x, float y, float z)         //  Builds a scaling matrix
   {
     identity();
     mat[0][0] = x; 
     mat[1][1] = y; 
     mat[2][2] = z;
   }
   
   void translate(float x, float y, float z)     // Builds a translation matrix
   {
     identity();
     
     mat[3][0] = x; 
     mat[3][1] = y; 
     mat[3][2] = z;
   }
   
   void rot_z(float rad)          // Builds a rotation-about-z matrix; input in RADIANS.
   {
     identity();
    
     mat[0][0] = (float)cos(rad);
     mat[0][1] = (float)sin(rad);
     mat[1][0] = (float)-sin(rad);
     mat[1][1] = (float)cos(rad);  
   }
   
   void rot_y(float rad)                   // Builds a rotation-about-y matrix; input in RADIANS.
   {
     identity();
     
     mat[0][0] = (float)cos(rad);
     mat[0][2] = (float)-sin(rad);
     mat[2][0] = (float)sin(rad);
     mat[2][2] = (float)cos(rad);  
   }
   
   void rot_x(float rad)           // Builds a rotation-about-x matrix; input in RADIANS.
   {
     identity();
     
     mat[1][1] = (float)cos(rad);
     mat[1][2] = (float)sin(rad);
     mat[2][1] = (float)-sin(rad);
     mat[2][2] = (float)cos(rad);  
   }
   
   void transpose()               // Transposes the matrix (flips rows & columns).
   {
     int i,j;
     Matrix ret;
     
     for (i = 0 ; i < 4 ; ++i)
       for (j = 0 ; j < 4 ; ++j)
         ret.mat[i][j] = mat[j][i]; 
   
     *this = ret;
   }

   bool invert()                 // Takes the inverse of the matrix.  Returns true for success, or FALSE if the matrix was singular (not invertible).
   {
      int lp,i,j,k;
      double wrk[4][8];
      double a, b;
  
      for( i=0; i<4; i++ )	/* Set up matrices */
        {
          for( j=0; j<4; j++ )
	    {
	      wrk[i][j]=(double)mat[i][j];
	      wrk[i][j+4]=0.0;
	    }
          wrk[i][i+4]=1.0;
        }
  
      for( lp=0; lp<4; lp++ )	/* Loop over all rows */
        {
          a=0.0;
          j=(-1);
          for( i=lp; i<4; i++ )	/* Find largest non-zero element */
	    {
	      b=wrk[i][lp];
	      if( b< 0.0 )
	        b=(-b);
	      if( b>a )
	        {
	          a=b;
	          j=i;
	        }
	    }
          if( j!=lp )			/* If not on diagonal, put it there */
	    {
	      if( j<0 )		/* Singular if none found */
	        return false;
	      else			/* Exchange rows from lp to end */
	        for( k=lp; k<8; k++ )
	          {
		    a=wrk[j][k];
		    wrk[j][k]=wrk[lp][k];
		    wrk[lp][k]=a;
	          }
	    }
          a=wrk[lp][lp];		/* Normalize working row */
          for( i=lp; i<8; i++ )
	    wrk[lp][i]/=a;
      
          for( i=lp+1; i<8; i++ )  /* Adjust rest of work space */
	    {
	      b=wrk[lp][i];
	      for( j=0; j<4; j++ )	/* One column at a time */
	        if( j!=lp )
	          wrk[j][i]-=wrk[j][lp]*b;
	    }
        }
      for( i=0; i<4; i++ )	/* Return result matrix */
        for( j=0; j<4; j++ )
          mat[i][j]=(float)wrk[i][j+4];
      return true;
   }


   friend Matrix operator* (const Matrix& multMat1, const Matrix& multMat2)
   {
   //  Purpose: Multiply two matricies
   //  Input: multMat1 - the first matrix
   //         multMat2 - the second matrix
   //  Output: returned matrix
   
     Matrix ret;
   
     for (int i = 0 ; i < 4 ; ++i)
       for (int j = 0 ; j < 4 ; ++j)
         ret.mat[i][j] = 
   	        multMat1.mat[i][0] * multMat2.mat [0][j] +
   	        multMat1.mat[i][1] * multMat2.mat [1][j] +
   	        multMat1.mat[i][2] * multMat2.mat [2][j] + 
            multMat1.mat[i][3] * multMat2.mat [3][j];
   
     return ret;
   }

   Matrix& operator=(const Matrix& eqMat)
   {  
   //  Purpose: Set one matrix equal to another.
   //  Input: eqMat - the matrix to copy
   //  Output: return matrix
   
     for (int i = 0 ; i < 4; ++i)
       for (int j = 0 ; j < 4 ; ++j)
         mat[i][j] = eqMat.mat[i][j];
   
     return *this;
   }

   friend ostream& operator<<(ostream& os, const Matrix& matToPrint)
   {
   //  Purpose: Output the matrix to the screen 
   //  Input: os - the output stream
   //         matToPrint - the matrix to print to the screen
   
     for (int i = 0 ; i < 4 ; ++i)
     {
       for (int j = 0 ; j < 4 ; ++j)
       	os <<  matToPrint.mat[i][j] << "\t"; 
       os << endl;
     }  
     os << endl;
    
     return os;
   }


};






#endif










