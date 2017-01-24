// ObjPoly.cpp: implementation of the ObjPoly class.
//
//////////////////////////////////////////////////////////////////////

#include "ObjPoly.h"

#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ObjPoly::ObjPoly(char *filename)
{
    // defaults:
    eShading = FLAT;
    _NormalsReady = false;

    scale = Vec3f(1, 1, 1);
    rotate = Vec3f(0, 0, 0);
    translate = Vec3f(0, 0, 0);
    _last_scale = Vec3f(999, 999, 999);
    _last_rotate = Vec3f(999, 999, 999);
    _last_translate = Vec3f(999, 999, 999);



    ifstream fin(filename);
    int i, temp;
    float x, y, z;

    cout << "Reading object: " << filename << endl;

    char str[16];
    fin >> str;
    if (!strcmp(str, "data"))
    {
        // ------------------------------
        // read DET
        // ------------------------------

        fin >> iNumVerts >> iNumFaces;
        cout << "  DET file with " << iNumVerts << " vertices and " << iNumFaces << " faces." << endl;
        
        // allocate mem
        orig_vertices = new Vec3f[iNumVerts];
        faces = new face[iNumFaces];
   
        // read vertices
        for (i=0; i<iNumVerts; i++)
        {
            fin >> x >> y >> z;
            orig_vertices[i] = Vec3f(x, y, z);
        }
        
        // read faces
        for (i=0; i<iNumFaces; i++)
        {
            fin >> temp;        // # of vertices to this poly
            if (temp != 3)
            {
                cout << "WARNING: Chopping non-3-sided-poly." << endl;
                if (temp < 3) 
                {
                    cout << "Polygon had " << temp << "vertices, quitting." << endl;
                    exit(666);
                }
            }
            fin >> faces[i].v1 >> faces[i].v2 >> faces[i].v3;
            faces[i].v1--;      // our arrays start at zero,
            faces[i].v2--;      // but in the .D file vertices
            faces[i].v3--;      // start at 1.

            if (temp > 3) // If more points were specified ignore them
            {
                int i, junk;
                for (i=0; i<temp-3; i++) fin >> junk;
            }

        }


    }
    else
    {
        // ------------------------------
        // read DXF
        // ------------------------------

        char strSECTION[16], strENTITIES[16], strPOLYLINE[16];
        int  n1, n2, n3;
        
        fin >> strSECTION >> n1 >> strENTITIES >> n2 >> strPOLYLINE;

        // assertion violations mean it's not a known DXF format.
        assert(!strcmp(strSECTION, "SECTION"));
        assert(!strcmp(strENTITIES, "ENTITIES"));
        assert(!strcmp(strPOLYLINE, "POLYLINE"));
        assert(n1 == 2);
        assert(n2 == 0);
        
        for (i=0; i<13; i++) fin >> x;
        fin >> iNumVerts >> x >> iNumFaces >> x;

        cout << "  DXF file with " << iNumVerts << " vertices and " << iNumFaces << " faces." << endl;

        // allocate mem
        orig_vertices = new Vec3f[iNumVerts];
        faces = new face[iNumFaces];
        
        // read vertices
        for (i=0; i<iNumVerts; i++)
        {
            fin >> str;
            assert(!strcmp(str, "VERTEX"));
            fin >> n1 >> n1 >> n1 >> x >> n1 >> y >> n1 >> z >> n1 >> n2 >> n3;
            assert(n2 == 192);
            orig_vertices[i] = Vec3f(x, y, z);
        }

        // read faces
        for (i=0; i<iNumFaces; i++)
        {
            fin >> str;
            assert(!strcmp(str, "VERTEX"));
            fin >> n1 >> n1 >> n1 >> x >> n1 >> x >> n1 >> x >> n1 >> n1;
            assert(n1 == 128);
            fin >> n1 >> faces[i].v1 >> n1 >> faces[i].v2 >> n1 >> faces[i].v3 >> n1;
            faces[i].v1--;      // our arrays start at zero,
            faces[i].v2--;      // but in the .D file vertices
            faces[i].v3--;      // start at 1.
        }
    }

    fin.close();
    cout << "Finished reading object." << endl;

    // ------------------------------
    // integrity checks
    // ------------------------------
    for (i=0; i<iNumFaces; i++)
    {
        assert(faces[i].v1 >= 0 && faces[i].v1 < iNumVerts);
        assert(faces[i].v2 >= 0 && faces[i].v2 < iNumVerts);
        assert(faces[i].v3 >= 0 && faces[i].v3 < iNumVerts);
    }


    // ------------------------------
    // finish allocation
    // ------------------------------
    orig_vert_normals = new Vec3f[iNumVerts];
    orig_face_normals = new Vec3f[iNumFaces];
    vertices = new Vec3f[iNumVerts];
    vert_normals = new Vec3f[iNumVerts];
    face_normals = new Vec3f[iNumFaces];
    opts = new opts_td[iNumFaces];
    face_normal_aligned = new bool[iNumFaces];
    
    // ------------------------------
    // calculate face normals
    // ------------------------------
    Vec3f edge1, edge2;
    Vec3f norm;
    for (i=0; i<iNumFaces; i++)
    {
        edge1 = orig_vertices[faces[i].v1] - orig_vertices[faces[i].v2];
        edge2 = orig_vertices[faces[i].v3] - orig_vertices[faces[i].v2];
        orig_face_normals[i] = edge1.cross(edge2);
        orig_face_normals[i].normalize();
    }
    
    // spider to align all original face normals to be in same direction;
    //  doesn't matter if that's inward or outward, as long as they are homogenous.
    for (i=0; i<iNumFaces; i++) face_normal_aligned[i] = false;
    for (i=0; i<iNumFaces; i++) 
        if (!face_normal_aligned[i])
        {
            face_normal_aligned[i] = true;
            _align_adjacent_faces(i);
        }
    for (i=0; i<iNumFaces; i++) assert(face_normal_aligned[i]);
    // ***keep in mind that all normals are now oriented along the surface in 
    //   the same way, but they might ALL be backwards!  That's why
    //   _NormalsReady is false.  The first time you try to get a normal
    //   it will use the scene geometry to figure out if it needs to flip
    //   ALL the normals.  **This could be a problem if your camera starts
    //   INSIDE a poly object.

    // ------------------------------
    // calculate vertex normals
    // ------------------------------
    for (i=0; i<iNumVerts; i++) orig_vert_normals[i] = Vec3f(0,0,0);
    for (i=0; i<iNumFaces; i++)
    {
        orig_vert_normals[faces[i].v1] += orig_face_normals[i];
        orig_vert_normals[faces[i].v2] += orig_face_normals[i];
        orig_vert_normals[faces[i].v3] += orig_face_normals[i];
    }
    for (i=0; i<iNumVerts; i++) 
    {
        orig_vert_normals[i].normalize();
    }



}

ObjPoly::~ObjPoly()
{
    if (orig_vertices)     { delete orig_vertices;     orig_vertices = NULL;     }
    if (orig_vert_normals) { delete orig_vert_normals; orig_vert_normals = NULL; }
    if (orig_face_normals) { delete orig_face_normals; orig_face_normals = NULL; }
    if (vertices)          { delete vertices;          vertices = NULL;          }
    if (vert_normals)      { delete vert_normals;      vert_normals = NULL;      } 
    if (face_normals)      { delete face_normals;      face_normals = NULL;      }
    if (faces)             { delete faces;             faces = NULL;             }
    if (opts)              { delete opts;              opts = NULL;              }
    if (face_normal_aligned) { delete face_normal_aligned; face_normal_aligned = NULL; }
}




void ObjPoly::update_geometry(const float time)   
{
    // using SCALE, ROTATE, and TRANSLATE, brings all world-
    // space geometry up-to-date and generates obj_to_world_matrix
    // and w.s. bounding sphere
    //
    // input:
    //   - original vertex & face information (never changes)
    //   + scale
    //   + rotate
    //   + translate (applied in this order)
    //
    // generates:
    //   - vertices[]     in WORLD SPACE
    //   - vert_normals[] in WORLD SPACE
    //   - face_normals[] in WORLD SPACE
    //   - obj_to_world_matrix
    //   - the_bounding_sphere_center
    //   - the_bounding_sphere_radius
    //   - the_bounding_sphere_radius_squared

    // Updates vertices & face normals from current S/R/T values, 
    // and generates the obj_to_world_matrix.  


    // don't update geometry unless necessary!
    if ( (rotate - _last_rotate).length() < 0.0001 &&
         (scale - _last_scale).length() < 0.0001 && 
         (translate - _last_translate).length() < 0.0001 )
    {
        return;
    }
    _last_scale = scale;
    _last_rotate = rotate;
    _last_translate = translate;

    //--------------------------------------------------------------
    // STEP 1: set up obj_to_world_matrix
    //--------------------------------------------------------------
    Matrix m;
    int i;
    
    obj_to_world_matrix.scale(scale.x, scale.y, scale.z);
    
    if (rotate.x != 0)
    {
        m.rot_x(rotate.x);
        obj_to_world_matrix = obj_to_world_matrix*m;
    }
    if (rotate.y != 0)
    {
        m.rot_y(rotate.y);
        obj_to_world_matrix = obj_to_world_matrix*m;
    }
    if (rotate.z != 0)
    {
        m.rot_z(rotate.z);
        obj_to_world_matrix = obj_to_world_matrix*m;
    }
    
    m.translate(translate.x, translate.y, translate.z);
    obj_to_world_matrix = obj_to_world_matrix * m;
    //cout << obj_to_world_matrix;


    //--------------------------------------------------------------
    // STEP 2: transform orig_vertices, orig_vert_normals, and 
    // orig_face_normals into world space.
    //--------------------------------------------------------------
    //Vec3f cam = the_scene->get_observer()->get_position();

    for (i=0; i<iNumFaces; i++) 
    {
        face_normals[i] = orig_face_normals[i] * obj_to_world_matrix;
        face_normals[i].normalize();
    }

    for (i=0; i<iNumVerts; i++) 
    {
        vertices[i] = orig_vertices[i] * obj_to_world_matrix;
    }
    if (eShading == PHONG)
    {
        for (i=0; i<iNumVerts; i++) 
        {
            vert_normals[i] = orig_vert_normals[i] * obj_to_world_matrix;
            vert_normals[i].normalize();
        }
    }


    //! -- put this here 10/2/00  as the above vert stuff is fucked.
    // ------------------------------
    // calculate vertex normals
    // ------------------------------
    for (i=0; i<iNumVerts; i++) orig_vert_normals[i] = Vec3f(0,0,0);
    for (i=0; i<iNumFaces; i++)
    {
        orig_vert_normals[faces[i].v1] += orig_face_normals[i];
        orig_vert_normals[faces[i].v2] += orig_face_normals[i];
        orig_vert_normals[faces[i].v3] += orig_face_normals[i];
    }
    for (i=0; i<iNumVerts; i++) 
    {
        orig_vert_normals[i].normalize();
    }
    //!


    //--------------------------------------------------------------
    // STEP 3: get bounding sphere
    //--------------------------------------------------------------
    Vec3f max = vertices[0];
    Vec3f min = vertices[0];
    float r;

    // get max x,y,z values (so we know sphere's center)
    for (i=1; i<iNumVerts; i++)
    {
        if (max.x < vertices[i].x) max.x = vertices[i].x;
        if (max.y < vertices[i].y) max.y = vertices[i].y;
        if (max.z < vertices[i].z) max.z = vertices[i].z;
        if (min.x > vertices[i].x) min.x = vertices[i].x;
        if (min.y > vertices[i].y) min.y = vertices[i].y;
        if (min.z > vertices[i].z) min.z = vertices[i].z;
    }

    the_bounding_sphere_center = min + (max-min)*0.5;

    the_bounding_sphere_radius = 0;
    for (i=0; i<iNumVerts; i++)
    {
        r = (the_bounding_sphere_center - vertices[i]).length();
        if (the_bounding_sphere_radius < r) the_bounding_sphere_radius = r;
    }

    the_bounding_sphere_radius_squared = the_bounding_sphere_radius * the_bounding_sphere_radius;


    //-------------------------------------------------
    // STEP 4: do some precalx for poly-inside-testing
    //-------------------------------------------------

    // 1. get MLINE, BLINE, and SLINE for each polygon based on current camera. }
    // 2. define ABCD of each polygon's plane }
    for (i=0; i<iNumFaces; i++)
    {
        Vec3f pt1, pt2, pt3, pt9, a, b;
        
        pt1 = vertices[faces[i].v1];
        pt2 = vertices[faces[i].v2];
        pt3 = vertices[faces[i].v3];

        // pt9 is the polygon's center 
        pt9 = Vec3f( (pt1.x+pt2.x+pt3.x)/(float)3.0, 
                     (pt1.y+pt2.y+pt3.y)/(float)3.0, 
                     (pt1.z+pt2.z+pt3.z)/(float)3.0 );

        // we also want to precalculate the coefficients of each poly's plane:
        // a and b are vectors from P to Q and R, respectively 
        a = pt2 - pt1;
        b = pt3 - pt1;
        opts[i].PLANEA = a.y*b.z - a.z*b.y;                             
        opts[i].PLANEB = a.z*b.x - a.x*b.z;                  
        opts[i].PLANEC = a.x*b.y - a.y*b.x;                  // plug in pt.3 for D
        opts[i].PLANED = -(pt3.x*opts[i].PLANEA + pt3.y*opts[i].PLANEB + pt3.z*opts[i].PLANEC);

        r = (float)1.0/(float)sqrt(opts[i].PLANEA*opts[i].PLANEA + opts[i].PLANEB*opts[i].PLANEB + opts[i].PLANEC*opts[i].PLANEC);
        opts[i].PLANEA *= r;
        opts[i].PLANEB *= r;
        opts[i].PLANEC *= r;
        opts[i].PLANED *= r;     // Pa/b/c/d is the normalized ABCD of plane}


        // Goal: determine which dimension is the shortest, to cut it out
        //   of the calculations.  Do this by getting a bounding box for 
        //   this face... a is min pt., b is max pt.  Then examine b - a.
        a = pt1;
        b = pt1;
        if (pt2.x < a.x) a.x = pt2.x;
        if (pt2.y < a.y) a.y = pt2.y;
        if (pt2.z < a.z) a.z = pt2.z;
        if (pt2.x > b.x) b.x = pt2.x;
        if (pt2.y > b.y) b.y = pt2.y;
        if (pt2.z > b.z) b.z = pt2.z;
        if (pt3.x < a.x) a.x = pt3.x;
        if (pt3.y < a.y) a.y = pt3.y;
        if (pt3.z < a.z) a.z = pt3.z;
        if (pt3.x > b.x) b.x = pt3.x;
        if (pt3.y > b.y) b.y = pt3.y;
        if (pt3.z > b.z) b.z = pt3.z;
        b -= a;

        opts[i].CUTDIM = 3;          // assume z is smallest
        if (b.y > b.x && b.z > b.x)  // if x is smaller, cut it out instead
            opts[i].CUTDIM = 1;
        if (b.x > b.y && b.z > b.y)  // if y is smaller, cut it out instead
            opts[i].CUTDIM = 2;

        if (opts[i].CUTDIM==1)       // no matter what, calx use x & y values
        {
           pt1.x = pt1.z;
           pt2.x = pt2.z;
           pt3.x = pt3.z;
           pt9.x = pt9.z;
        }
        else if (opts[i].CUTDIM==2)
        {
           pt1.y = pt1.z;
           pt2.y = pt2.z;
           pt3.y = pt3.z;
           pt9.y = pt9.z;
        }

        // pretending Z is to be cut out: use X and Y 

        // line 1: P1 - P2.  Crunch sets  mline[a,1]  bline[a,1]  sline[a,1] }
        _crunch(0,i,pt1,pt2,pt9);
        // line 2: P2 - P3.  Crunch sets  mline[a,1]  bline[a,1]  sline[a,1] }
        _crunch(1,i,pt2,pt3,pt9);
        // line 3: P3 - P1.  Crunch sets  mline[a,1]  bline[a,1]  sline[a,1] }
        _crunch(2,i,pt3,pt1,pt9);
    }

    

}

void ObjPoly::_crunch(int L, int d, Vec3f &pt1, Vec3f &pt2, Vec3f &pt9)
{
    float u;

    float dx = pt1.x - pt2.x;
    float dy = pt1.y - pt2.y;

    // x1,y1  and  x2,y2  : the two points.         x9,y9 : the polygon's ctr 
    if (fabs(dx) > 0.00000000001)      // m = var1    b = var2    s = var3 
    {
        opts[d].MLINE[L] = dy/dx;       // d = # of the polygon }
        opts[d].BLINE[L] = pt2.y - opts[d].MLINE[L]*pt2.x;
        u = opts[d].MLINE[L]*pt9.x + opts[d].BLINE[L] - pt9.y;  // = sign of inequality for points within
        opts[d].SLINE[L] = u;
        opts[d].VERT[L] = false;
        //cout << ".";
    }
    else 
    {
        opts[d].BLINE[L] = pt1.x;
        opts[d].SLINE[L] = (pt9.x - pt1.x);
        opts[d].VERT[L] = true;
        //cout << "|";
    }

}

void ObjPoly::_align_adjacent_faces(int z)
{
    // z = # of the face whose orientation its siblings should take on

    int z1, z2, z3;
    int v1, v2, v3;

    z1 = faces[z].v1;
    z2 = faces[z].v2;
    z3 = faces[z].v3;

    for (int i=0; i<iNumFaces; i++) 
    {
        v1 = faces[i].v1;
        v2 = faces[i].v2;
        v3 = faces[i].v3;

        if ((i != z) && (
            v1 == z1 || v2 == z1 || v3 == z1 ||
            v1 == z2 || v2 == z2 || v3 == z2 ||
            v1 == z3 || v2 == z3 || v3 == z3))
        {
            if (!face_normal_aligned[i] &&
                orig_face_normals[i].dot(orig_face_normals[z]) < 0)
            {
                orig_face_normals[i] *= -1.0f;
                face_normal_aligned[i] = true;
                _align_adjacent_faces(i);
            }
        }
    }          
}


SceneObject::Intersect_Type ObjPoly::intersect(const Vec3f ray_origin, 
                          const Vec3f ray_direction,
                          const Intersect_Type intersect_type,
                          float &t)
{
    _CurrentFace = -1;
    float fDot, line1val, line2val, line3val, t_temp;
    Vec3f pt;
    t = 99999;
    
    for (int i=0; i<iNumFaces; i++)
    {
        fDot = opts[i].PLANEA*ray_direction.x + opts[i].PLANEB*ray_direction.y + opts[i].PLANEC*ray_direction.z;
        t_temp = -(opts[i].PLANEA*ray_origin.x + opts[i].PLANEB*ray_origin.y + opts[i].PLANEC*ray_origin.z + opts[i].PLANED)/fDot;
        if (t_temp < t)
        {
            pt = Vec3f( ray_origin.x + ray_direction.x*t_temp,
                        ray_origin.y + ray_direction.y*t_temp,
                        ray_origin.z + ray_direction.z*t_temp);
            
            // now, if pt is inside the poly, then set t = t_temp and _CurrentFace = i.
            
            if (opts[i].CUTDIM==1)    // no matter what, we work with x & y
                pt.x = pt.z;
            else if (opts[i].CUTDIM==2)
                pt.y = pt.z;

            line1val = (opts[i].VERT[0]) ? (pt.x - opts[i].BLINE[0]) : (opts[i].MLINE[0]*pt.x + opts[i].BLINE[0] - pt.y);
            if (line1val * opts[i].SLINE[0] > 0)
            {
                line2val = (opts[i].VERT[1]) ? (pt.x - opts[i].BLINE[1]) : (opts[i].MLINE[1]*pt.x + opts[i].BLINE[1] - pt.y);
                if (line2val * opts[i].SLINE[1] > 0)
                {
                    line3val = (opts[i].VERT[2]) ? (pt.x - opts[i].BLINE[2]) : (opts[i].MLINE[2]*pt.x + opts[i].BLINE[2] - pt.y);
                    if (line3val * opts[i].SLINE[2] > 0)
                    {
                        t = t_temp;
                        _CurrentFace = i;
                    }
                }
            }
        }
    }

    _CurrentIntPt = ray_origin + t*ray_direction;

    // If _CurrentFace = -1 there was no intersection, else there was and we'll just promote everything
    // to an INTERSECT_OUTSIDE
    if (_CurrentFace == -1)
      return SceneObject::NO_INTERSECTION;
    else
      // dot ray_direction with surface normal to determine inside/outside
      return SceneObject::OUTSIDE_INTERSECTION;
}


//! Make normal work better. 
// Base of of internaly stored information, save what you need to know when the intersect
// function is called, use it here to calculate the normal when requested.
//
// One question is 'should the calculate normal be forced to be able to do so for
// any position given, or should this function really have 0 params, and the resulting
// normal be the normal of the last intersected point. (assuming that it may be
// dificult to determine 
//
// Normal must be normalized
Vec3f ObjPoly::calculate_normal()
{
    assert(_CurrentFace >= 0);
    assert(_CurrentFace < iNumFaces);

    Vec3f normal;

    if (!_NormalsReady)
    {
        // ***all normals are oriented along the surface in 
        //   the same way, but they might ALL be backwards!  That's why
        //   _NormalsReady is false.  Now we use the scene geometry to figure 
        //   out if we needs to flip ALL the normals.  **This could be a 
        //   problem if your camera starts INSIDE a poly object.
        if (face_normals[_CurrentFace].dot(the_scene->get_observer()->get_position() - _CurrentIntPt) < 0)
        {
            int i;
            for (i=0; i<iNumFaces; i++) orig_face_normals[i] *= -1.0f;
            for (i=0; i<iNumVerts; i++) orig_vert_normals[i] *= -1.0f;
            for (i=0; i<iNumFaces; i++) face_normals[i] *= -1.0f;
            for (i=0; i<iNumVerts; i++) vert_normals[i] *= -1.0f;
        }
        _NormalsReady = true;
    }

    if (eShading == FLAT)
    {
        normal = face_normals[_CurrentFace];
    }
    else if (eShading == PHONG)
    {
        float ang1, ang2, t1, t2, t3;
        Vec3f v1 = vertices[faces[_CurrentFace].v1];
        Vec3f v2 = vertices[faces[_CurrentFace].v2];
        Vec3f v3 = vertices[faces[_CurrentFace].v3];
        Vec3f i = _CurrentIntPt;
        Vec3f p;

        ang1 = (float)acos( (i - v1).norm_value().dot(  (v2-v1).norm_value()  ) );
        ang2 = (float)acos( (i - v1).norm_value().dot(  (v3-v1).norm_value()  ) );
        p = v2 + (v3-v2)*(ang1 / (ang1+ang2));
        t1 = 1.0f  -  (i-v1).length()/(p-v1).length();

        ang1 = (float)acos( (i - v2).norm_value().dot(  (v1-v2).norm_value()  ) );
        ang2 = (float)acos( (i - v2).norm_value().dot(  (v3-v2).norm_value()  ) );
        p = v1 + (v3-v1)*(ang1 / (ang1+ang2));
        t2 = 1.0f  -  (i-v2).length()/(p-v2).length();

        ang1 = (float)acos( (i - v3).norm_value().dot(  (v2-v3).norm_value()  ) );
        ang2 = (float)acos( (i - v3).norm_value().dot(  (v1-v3).norm_value()  ) );
        p = v2 + (v1-v2)*(ang1 / (ang1+ang2));
        t3 = 1.0f  -  (i-v3).length()/(p-v3).length();

        normal = vert_normals[faces[_CurrentFace].v1] * t1 +
                 vert_normals[faces[_CurrentFace].v2] * t2 +
                 vert_normals[faces[_CurrentFace].v3] * t3;
        normal.normalize(); 
    }
    else if (eShading == GOURAND)
    {



    }

    // flip normal toward camera if necessary
    //if (normal.dot(the_scene->get_observer()->get_position() - _CurrentIntPt) < 0)
    //{
        //normal *= -1.0f;
    //}

    return normal;
}






