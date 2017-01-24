// ObjPoly.h: interface for the ObjPoly class.
//
//////////////////////////////////////////////////////////////////////
//
// polygon-based object

#ifndef OBJPOLY_H
#define OBJPOLY_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "SceneObject.h"
#include "Scene.h" // Need this AFTER "SceneObject.h"
#include "Vec3f.h"
#include "Mat3.h"



// PARSER:
//   -must give filename to read in w/constructor
//   -must manually tell it which shading type (default is flat)
//   -must set SCALE, ROTATE, and TRANSLATE
//   -

// to do:    
//   - calculate_normal(), using class internal saved info

//   - Vince changed lots of 123 accessors to vectors to be 012s, but it still doesn't
//     work. =I Lines changed were:
//        _crunch(0,i,pt1,pt2,pt3);
//                ^--
//        if ((line1val>0 && SLINE[i][0]>0) || (line1val<0 && SLINE[i][0]<0)) 
//                                    ^--                              ^--
//     and all similar lines.

//   - calculate_bounding_box has been renamed to update_geometry

//   - test the motherfucker

class ObjPoly : public SceneObject  
{
public:
    // TYPEDEFS
    enum PolyShadingType { FLAT, GOURAND, PHONG };

    // CONSTRUCTOR
    ObjPoly(char *filename);
    virtual ~ObjPoly();
    
    PolyShadingType eShading;   // FLAT, GOURAND, or PHONG
    
    Vec3f    scale;             // current interpolated object scale
    Vec3f    rotate;            // current interpolated object rotation (in RAD)
    Vec3f    translate;         // current interpolated object translation
    //KeyFrameProps* props;     // keyframe info
    
    Matrix   obj_to_world_matrix;  // set by update_geometry() 
    
    // Updates internal data for the specified time (including bounding).
    virtual void update_geometry(const float time);       // uses SCALE, ROTATE, and TRANSLATE to bring all world-space geometry up-to-date and generate obj_to_world_matrix and (world-space) bounding sphere
    
    
    // Finds intersection of object, Call AFTER intersect_bounding_sphere()
    // ray_direction must be normalized
    // intersect_type is value returned from intersect_bounding_sphere().
    // t must be intersection of bounding box, will be modified after actual intersection.
    virtual Intersect_Type intersect(const Vec3f ray_origin, 
        const Vec3f ray_direction,
        const Intersect_Type intersect_type,
        float &t);

    // Returns normal of intersection, Call AFTER intersect()
    // Returns NORMALIZED normal
    virtual Vec3f ObjPoly::calculate_normal();
    
protected:
    typedef struct 
    {
        int v1;
        int v2;
        int v3;
    } face;

    int      _CurrentFace;      // # of last face which was found to intersect.
    Vec3f    _CurrentIntPt;     // world-space point of last intersection
    bool     _NormalsReady;     // only has to be done ONCE for the object, EVER... done the first time a normal is calculated.

    Vec3f*   orig_vertices;     // list of the object-space vertices
    Vec3f*   orig_vert_normals; // list of vertices (simple 3d vectors)
    Vec3f*   orig_face_normals; // list of vertices (simple 3d vectors)
        
    int      iNumFaces;         
    int      iNumVerts;         
    Vec3f*   vertices;          // list of W.S. vertices - Vec3f[iNumVerts]
    Vec3f*   vert_normals;      // list of W.S. vertex normals - Vec3f[iNumVerts]
    Vec3f*   face_normals;      // list of W.S. face normals - Vec3f[iNumFaces]
    face*    faces;             // list of 'face' structs - each face has 3 integer vertex #s
    bool*    face_normal_aligned; // used to align all face normals with each other
    
    typedef struct
    {
        Vec3f   MLINE;
        Vec3f   BLINE;
        Vec3f   SLINE;
        float   PLANEA;
        float   PLANEB;
        float   PLANEC;
        float   PLANED;
        int     CUTDIM;
        bool    VERT[3];       // true: "vertical" line, BLINE is actually X-intercept
    } opts_td;

    opts_td*   opts;

    void _crunch(int L, int d, Vec3f &pt1, Vec3f &pt2, Vec3f &pt9);
    void _align_adjacent_faces(int i);
    Vec3f    _last_scale;    
    Vec3f    _last_rotate;   
    Vec3f    _last_translate;
    
    
};

#endif 
