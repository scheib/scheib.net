// Parser.cpp: implementation of the Parser class.
//
//////////////////////////////////////////////////////////////////////

#include "Parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Parser::Parser(istream *_input)
{
  input = _input;
}

Parser::~Parser()
{

}


void Parser::make_uppercase(char * str)
{
    int i = 0;
    while(str[i] != NULL)
    {
        if('a'<=str[i] && str[i]<='z')
        {
            str[i] -= ' '; // make uppercase 
        }
        i++;
    }
}

//////////////////////////////////////////////////////////////////////
// GET NEXT LINE
//////////////////////////////////////////////////////////////////////

void Parser::get_next_line(char *str, int length)
{
    bool done = false;
    do 
    {
        input->getline(str, length); 

        if (!input->good()) 
        {
            cout << "\n\nSCRIPT PARSING ERROR: input error."
                 << "\n\t(most likely End Of File.)" <<endl;
            exit(666);
        }

        if (0==strlen(str)) continue; // Skip blank lines
        if (str[0]==' ') continue;
        if (str[0]=='_') continue;
        if (str[0]=='.') continue;
        if (str[0]==':') continue;
        if (str[0]==';') continue;
        if (str[0]=='!') continue;
        if (str[0]=='#') continue;

        done = true;
    } while (!done);

    // Remove whitespace from end of line
    int slength = strlen(str);
    while(length > 0)
    {
        if (str[slength-1]==' ')
        {
            str[slength-1]=NULL;
            slength--;
            continue;
        }
        else break;
    }
}

//////////////////////////////////////////////////////////////////////
// EXPECT STRING
//////////////////////////////////////////////////////////////////////

void Parser::expect_string(const char *str)
{
  char line[MAX_PARSER_LINE_LENGTH];
  get_next_line(line, MAX_PARSER_LINE_LENGTH);
  make_uppercase(line);

  char *str_cpy = new char[strlen(str)+1];
  strcpy(str_cpy, str);
  make_uppercase(str_cpy);

  if (strcmp(str_cpy, line))
  {
    cout << "\n\nSCRIPT PARSING ERROR: Expecting '" << str_cpy << "'." << endl;
    delete str_cpy;
    exit (1);
  }

  cout << "Expected & found '" << str_cpy << "'." << endl;
  delete str_cpy;
}



float Parser::get_float()
{
  float temp;
  *input >> temp;

  if (!input->good()) 
  {
    cout << "\n\nSCRIPT PARSING ERROR: Input error. Expected a float." << endl;
    exit(666);
  }

  return temp;
}



int Parser::get_int()
{
  int temp;
  *input >> temp;

  if (!input->good()) 
  {
    cout << "\n\nSCRIPT PARSING ERROR: Input error. Expected an int." << endl;
    exit(666);
  }

  return temp;
}



Vec3f Parser::get_Vec3f()
{
  float temp1;
  float temp2;
  float temp3;

  *input >> temp1;
  if (!input->good()) 
  {
    cout << "\n\nSCRIPT PARSING ERROR: Input error. Expected the 1st float in a vector of three." << endl;
    exit(666);
  }

  *input >> temp2;
  if (!input->good()) 
  {
    cout << "\n\nSCRIPT PARSING ERROR: Input error. Expected the 2nd float in a vector of three." << endl;
    exit(666);
  }

  *input >> temp3;
  if (!input->good()) 
  {
    cout << "\n\nSCRIPT PARSING ERROR: Input error. Expected the 3rd float in a vector of three." << endl;
    exit(666);
  }

  return Vec3f(temp1, temp2, temp3);
}

//////////////////////////////////////////////////////////////////////
// GET ENVIRONMENT
//////////////////////////////////////////////////////////////////////

SceneEnvironment* Parser::get_environment()
{
  expect_string("ENVIRONMENT");
  
  SceneEnvironment *environment;
  
  get_next_line(line, MAX_PARSER_LINE_LENGTH);
  make_uppercase(line);
  
  if (0==strcmp("CUBESKYMAP", line))
  {
    cout << "Gathering CubeSkyMap environment information." << endl;
    
    expect_string("ambient");
    Vec3f ambient = get_Vec3f();
    cout << "ambient light: " << ambient << endl;

    expect_string("background");
    Vec3f background = get_Vec3f();
    cout << "background light: " << background << endl;
    
    expect_string("topfile");
    char topfile[MAX_PARSER_LINE_LENGTH] = {0};
    get_next_line(topfile, MAX_PARSER_LINE_LENGTH);
    if (0==strlen(topfile))
    {
      cout << "\n\nSCRIPT PARSING ERROR: Expecting a filename" << endl;
      exit (1);
    }
    cout << "Image file:" << topfile << endl;
    expect_string("frontfile");
    char frontfile[MAX_PARSER_LINE_LENGTH] = {0};
    get_next_line(frontfile, MAX_PARSER_LINE_LENGTH);
    if (0==strlen(frontfile))
    {
      cout << "\n\nSCRIPT PARSING ERROR: Expecting a filename" << endl;
      exit (1);
    }
    cout << "Image file:" << frontfile << endl;
    expect_string("rightfile");
    char rightfile[MAX_PARSER_LINE_LENGTH] = {0};
    get_next_line(rightfile, MAX_PARSER_LINE_LENGTH);
    if (0==strlen(rightfile))
    {
      cout << "\n\nSCRIPT PARSING ERROR: Expecting a filename" << endl;
      exit (1);
    }
    cout << "Image file:" << rightfile << endl;
    expect_string("backfile");
    char backfile[MAX_PARSER_LINE_LENGTH] = {0};
    get_next_line(backfile, MAX_PARSER_LINE_LENGTH);
    if (0==strlen(backfile))
    {
      cout << "\n\nSCRIPT PARSING ERROR: Expecting a filename" << endl;
      exit (1);
    }
    cout << "Image file:" << backfile << endl;
    expect_string("leftfile");
    char leftfile[MAX_PARSER_LINE_LENGTH] = {0};
    get_next_line(leftfile, MAX_PARSER_LINE_LENGTH);
    if (0==strlen(leftfile))
    {
      cout << "\n\nSCRIPT PARSING ERROR: Expecting a filename" << endl;
      exit (1);
    }
    cout << "Image file:" << leftfile << endl;
    expect_string("bottomfile");
    char bottomfile[MAX_PARSER_LINE_LENGTH] = {0};
    get_next_line(bottomfile, MAX_PARSER_LINE_LENGTH);     
    if (0==strlen(bottomfile))                             
    {
      cout << "\n\nSCRIPT PARSING ERROR: Expecting a filename" << endl;
      exit (1);
    }
    cout << "Image file:" << bottomfile << endl;
    
    
    environment = new CubeSkyMap(ambient, background, topfile, rightfile, frontfile, leftfile, backfile, bottomfile);

    get_next_line(line, MAX_PARSER_LINE_LENGTH);
    make_uppercase(line);

  }
  else if (0==strcmp("SIMPLESKY", line))
  {
    cout << "Gathering SimpleSky environment information." << endl;
    
    expect_string("ambient");
    Vec3f ambient = get_Vec3f();
    cout << "ambient light: " << ambient << endl;
    
    get_next_line(line, MAX_PARSER_LINE_LENGTH);
    make_uppercase(line);
    if (0==strcmp("COLORS", line))
    {
      expect_string("top");
      Vec3f top = get_Vec3f();
      expect_string("top_horizon");
      Vec3f top_horizon = get_Vec3f();
      expect_string("bottom_horizon");
      Vec3f bottom_horizon = get_Vec3f();
      expect_string("bottom");
      Vec3f bottom = get_Vec3f();

      environment = new SimpleSkyEnv(ambient, top, top_horizon, bottom_horizon, bottom);

      get_next_line(line, MAX_PARSER_LINE_LENGTH);
      make_uppercase(line);
    }
    else 
    {
      environment = new SimpleSkyEnv(ambient);
    }
  }
  else
  {
    environment = new SceneEnvironment();

    if (0==strcmp("AMBIENT", line))
    {
      Vec3f ambient = get_Vec3f();
      cout << "ambient light: " << ambient << endl;
      environment->set_ambient_color(ambient);

      get_next_line(line, MAX_PARSER_LINE_LENGTH);
      make_uppercase(line);
    }

    if (0==strcmp("BACKGROUND", line))
    {
      Vec3f back = get_Vec3f();
      cout << "background color: " << back << endl;
      environment->set_background_color(back);

      get_next_line(line, MAX_PARSER_LINE_LENGTH);
      make_uppercase(line);
    }

  }

  // moved the get_next_line code up because of simple sky.

  if (strcmp("END ENVIRONMENT", line))
  {
    cout << "\n\nSCRIPT PARSING ERROR: Expecting 'end environment'" << endl;
    exit (1);
  }

  return environment;
}



//////////////////////////////////////////////////////////////////////
// GET LIGHTS
//////////////////////////////////////////////////////////////////////

SceneLight** Parser::get_lights(const int number_of_lights)
{
  expect_string("LIGHTS");
  cout << "\n\nGathering " << number_of_lights << " light definitions.\n" << endl;

  SceneLight **light_list = new SceneLight*[number_of_lights];
  assert(light_list);

  for(int i=0; i<number_of_lights; i++) 
  {
    get_next_line(line, MAX_PARSER_LINE_LENGTH);
    make_uppercase(line);
    if (0==strcmp("POINTLIGHT", line))
    {        
      expect_string("position");      
      Vec3f position = get_Vec3f();
      
      expect_string("radius");      
      float radius = get_float();
      
      expect_string("color");      
      Vec3f color = get_Vec3f();
      
      light_list[i] = new PointLight(position, radius, color);
      cout << "Light " << i+1 << " is a PointLight:\n";
      cout << "\tposition: " << position 
          << "  radius: " << radius 
          << "  color: " << color << endl;
      
      get_next_line(line, MAX_PARSER_LINE_LENGTH);
      make_uppercase(line);
      if (0==strcmp("CAST SHADOWS", line))
      {
        light_list[i]->cast_shadows = true;
      }
    }
    else
    {
      cout << "\n\nSCRIPT PARSING ERROR: Expecting a light (num " 
        << i+1 << " of " << number_of_lights << ")" << endl;
      exit (1);
    }
    
  }

  return light_list;
}



//////////////////////////////////////////////////////////////////////
// GET MATERIALS
//////////////////////////////////////////////////////////////////////

Material** Parser::get_materials(const int number_of_materials)
{
  expect_string("MATERIALS");
  cout << "\n\nGathering " << number_of_materials << " material definitions.\n" << endl;

  Material **mat_list = new Material*[number_of_materials];
  assert(mat_list);

  for(int i=0; i<number_of_materials; i++) 
  {
    get_next_line(line, MAX_PARSER_LINE_LENGTH);
    make_uppercase(line);
    if (0==strcmp("BASIC", line))
    {
      expect_string("COLOR");
      Vec3f color = get_Vec3f();

      expect_string("KD KS KN");
      Vec3f ks = get_Vec3f();
        
      expect_string("REFLECTION REFRACTION");
      float kl = get_float();
      float kr = get_float();
        
      expect_string("DENSITY");
      float density = get_float();

      expect_string("REFLECTION / REFRACTION BLUR ANGLES");
      float refl_ang = get_float() * 0.5f * (3.1415927f/180.0f);
      float refr_ang = get_float() * 0.5f * (3.1415927f/180.0f);

      mat_list[i] = new Material(color, ks.x, ks.y, ks.z, kl, kr, density, refl_ang, refr_ang);
        cout << "Basic Material " << i+1
          << "\n\tColor: " << color
          << "\n\tKd: " << ks.x 
          << "  Ks: " << ks.y
          << "  Kn: " << ks.z 
          << "  density: " << density 
          << "  reflection angle: " << refl_ang 
          << "  refraction angle: " << refr_ang 
          << "\n\treflection: " << kl << "  refraction: " << kr << endl;
    }
    else
    {
      cout << "\n\nSCRIPT PARSING ERROR: Expecting a material (num " 
        << i+1 << " of " << number_of_materials << ")" << endl;
      exit (1);
    }
  }

  return mat_list;
}



//////////////////////////////////////////////////////////////////////
// GET OBJECTS
//////////////////////////////////////////////////////////////////////

SceneObject** Parser::get_objects(int &obj_num, Material** material_list)
{
  expect_string("objects");
  
  cout << "\n\nGathering " << obj_num << " object definitions.\n" << endl;
  
  
  // PREPARE OBJECT LIST
  SceneObject **obj_list = new SceneObject*[obj_num];
  assert(obj_list);
  
  int i=0;
  while(i<obj_num)
  {
    get_next_line(line, MAX_PARSER_LINE_LENGTH);
    make_uppercase(line);
    if (0==strcmp("SPHERE", line))
    {
      expect_string("POSITION");
      Vec3f temp_vec = get_Vec3f();
      
      expect_string("RADIUS");
      float radius = get_float();
      
      expect_string("MATERIAL");
      int mat = get_int();
      
      expect_string("GET / CAST SHADOWS");
      int get_shad = get_int();
      int cast_shad = get_int();
      
      obj_list[i] = new ObjSphere(temp_vec, radius);
      obj_list[i]->set_material(material_list[mat-1]);
      obj_list[i]->receive_shadows = (get_shad==0) ? false : true;
      obj_list[i]->cast_shadows = (cast_shad==0) ? false : true;
        
      cout << "Object " << i+1 << " is a Sphere:\n";
      cout << "\tposition: " << temp_vec 
        << "  radius: " << radius 
        << "  material: " << mat 
        << endl;
      
      i++; // We loaded an object, inc counter
    }
    else if (0==strcmp("SPHERE ARRAY", line))
    {
      expect_string("TGA FILE");
      
      char arrayfile[MAX_PARSER_LINE_LENGTH] = {0};
      get_next_line(arrayfile, MAX_PARSER_LINE_LENGTH);
      if (0==strlen(arrayfile))
      {
        cout << "\n\nSCRIPT PARSING ERROR: Expecting a filename" << endl;
        exit (1);
      }
      cout << "Array file:" << arrayfile << endl;
      
      
      expect_string("BOUNDING BOX MIN");
      Vec3f bb_min = get_Vec3f(); 
      
      expect_string("BOUNDING BOX MAX");
      Vec3f bb_max = get_Vec3f(); 
      
      expect_string("RADIUS MAX");
      float radius_max = get_float(); 
      
      expect_string("MATERIAL");
      int mat = get_int();
      
      expect_string("GET / CAST SHADOWS");
      int get_shad = get_int();
      int cast_shad = get_int();
      
      Buffer sphere_array;
      sphere_array.ReadTGA(arrayfile);
      if (i + sphere_array.get_width() * sphere_array.get_height() > obj_num)
      {
        cout << "\n\nERROR: Sphere array contains " 
          << sphere_array.get_width() * sphere_array.get_height()
          << " objects, \nbut script file did not expect this many."
          << " increase script file object number by " 
          << i + sphere_array.get_width() * sphere_array.get_height() - obj_num
          << endl;
        exit(1);
      }
      
      // Make the array of spheres
      {
        int w = sphere_array.get_width();
        int h = sphere_array.get_height();
        int x;
        int y;
        for (x=0; x<w; x++)
        {
          for (y=0; y<h; y++)
          {
            Vec3f attr = sphere_array.get_color(x, h-1-y);
            if (attr.y == 0) // If radius is zero don't bother
            {
              obj_num--;
              continue;
            }
            
            Vec3f pos(bb_min.x + (x/(float)(w-1))*(bb_max.x - bb_min.x),
              bb_min.y + (y/(float)(h-1))*(bb_max.y - bb_min.y),
              bb_min.z + (attr.x )*(bb_max.z - bb_min.z));
            
            obj_list[i] = new ObjSphere(pos, attr.y*radius_max);
            obj_list[i]->set_material(material_list[mat-1]);
            obj_list[i]->receive_shadows = (get_shad==0) ? false : true;
            obj_list[i]->cast_shadows = (cast_shad==0) ? false : true;
            
            i++; // We loaded an object, inc counter
          }
        }
      }
      
      cout << "Objects are Sphere Array:\n";
      cout << "\tmin: " << bb_min << "  max: " << bb_max << endl;
      cout << "\tmax radius: " << radius_max << endl;
      cout << "\tmaterial: " << mat << endl;        
    }
    else if (0==strcmp("POLY", line))
    {
      expect_string("FILENAME");
      
      char datafile[MAX_PARSER_LINE_LENGTH] = {0};
      get_next_line(datafile, MAX_PARSER_LINE_LENGTH);
      if (0==strlen(datafile))
      {
        cout << "\n\nSCRIPT PARSING ERROR: Expecting a filename" << endl;
        exit (1);
      }
      cout << "Polygon data file:" << datafile << endl;
      
      expect_string("SHADING");
      ObjPoly::PolyShadingType shading_type;
      char shading[MAX_PARSER_LINE_LENGTH] = {0};
      get_next_line(shading, MAX_PARSER_LINE_LENGTH);
      make_uppercase(shading);
      if (0==strcmp(shading, "FLAT")) shading_type = ObjPoly::FLAT;
      else if (0==strcmp(shading, "GOURAND")) shading_type = ObjPoly::GOURAND;
      else if (0==strcmp(shading, "PHONG")) shading_type = ObjPoly::PHONG;
      else
      {
        cout << "\n\nSCRIPT PARSING ERROR: Expecting 'flat' 'gourand' or 'phong' for shading type for polygon object." << endl;
        exit (1);
      }
      
      expect_string("SCALE");
      Vec3f scale = get_Vec3f();
      
      expect_string("ROTATE");
      Vec3f rotate= get_Vec3f();
      rotate *= 3.14159f / 180.0f;

      expect_string("TRANSLATE");
      Vec3f translate = get_Vec3f();
      
      expect_string("MATERIAL");
      int mat = get_int();
      
      expect_string("GET / CAST SHADOWS");
      int get_shad = get_int();
      int cast_shad = get_int();
      
      obj_list[i] = new ObjPoly(datafile);
      obj_list[i]->set_material(material_list[mat-1]);
      obj_list[i]->receive_shadows = (get_shad==0) ? false : true;
      obj_list[i]->cast_shadows = (cast_shad==0) ? false : true;
      ((ObjPoly*)(obj_list[i]))->scale = scale;
      ((ObjPoly*)(obj_list[i]))->rotate = rotate;
      ((ObjPoly*)(obj_list[i]))->translate = translate;
      ((ObjPoly*)(obj_list[i]))->eShading = shading_type;

      cout << "Object " << i+1 << " is a Polygon Object:\n";
      cout << "\tscale: " << scale 
        << "  rotate: " << rotate 
        << "  translate: " << translate 
        << endl;
      
      i++; // We loaded an object, inc counter
    }
    else if (0==strcmp("TEXTUREDFLOORQUAD", line))
    {
      expect_string("POSITION");
      Vec3f temp_vec = get_Vec3f();
      
      expect_string("SCALE");
      float xs = get_float();
      float ys = get_float();
      
      expect_string("TEXTURE");
      
      char datafile[MAX_PARSER_LINE_LENGTH] = {0};
      get_next_line(datafile, MAX_PARSER_LINE_LENGTH);
      if (0==strlen(datafile))
      {
        cout << "\n\nSCRIPT PARSING ERROR: Expecting a filename" << endl;
        exit (1);
      }
      cout << "texture data file:" << datafile << endl;

      expect_string("MATERIAL");
      int mat = get_int();
      
      expect_string("GET / CAST SHADOWS");
      int get_shad = get_int();
      int cast_shad = get_int();


      obj_list[i] = new ObjTexturedFloorQuad(temp_vec, xs, ys, datafile);
      obj_list[i]->set_material(material_list[mat-1]);
      obj_list[i]->receive_shadows = (get_shad==0) ? false : true;
      obj_list[i]->cast_shadows = (cast_shad==0) ? false : true;
        
      cout << "Object " << i+1 << " is a Textured Floor Quad:\n";
      cout << "\tposition: " << temp_vec 
        << "  scale: " << xs << " " << ys
        << "  material: " << mat 
        << endl;
      
      i++; // We loaded an object, inc counter
    }
    else
    {
      cout << "\n\nSCRIPT PARSING ERROR: Expecting "
        << "object (num " 
        << i+1 << " of " << obj_num << ")" << endl;
      exit (1);
    }
  }

  return obj_list;
}



//////////////////////////////////////////////////////////////////////
// GET OBSERVER
//////////////////////////////////////////////////////////////////////

Observer* Parser::get_observer(const float aspect_ratio)
{
    expect_string("OBSERVER");

    expect_string("POSITION");
    Vec3f obs_pos = get_Vec3f();
    
    expect_string("LOOK AT");
    Vec3f obs_coi = get_Vec3f();
    
    expect_string("TILT");
    float obs_tilt = get_float();
    
    expect_string("ANGLE OF VIEW");
    float obs_fov = get_float();
    
    expect_string("LENSE RADIUS");
    float obs_lens_rad = get_float();
    
    expect_string("PIXEL SIZE");
    float obs_pix_size = get_float();
    
    cout << "\nObserver\n\tposition: " << obs_pos 
      << "\n\tlookat: " << obs_coi 
      << "\n\ttilt: " << obs_tilt << "  angle of view: " << obs_fov
      << "\n\taspect ratio: " << aspect_ratio 
      << "\n\tlesne radius: " << obs_lens_rad 
      << "\n\tpixel size: " << obs_pix_size 
      << endl;

    return new Observer(obs_pos, 
        obs_coi, 
        obs_tilt, 
        obs_fov, 
        aspect_ratio, 
        obs_lens_rad, 
        obs_pix_size);
}




//////////////////////////////////////////////////////////////////////
// GET KEYFRAMES
//////////////////////////////////////////////////////////////////////

void Parser::get_keyframes(SceneEnvironment* environment,
                           SceneLight** light_list,
                           const int number_of_lights,
                           Material** material_list,
                           const int number_of_materials,
                           SceneObject** object_list,
                           const int number_of_objects,
                           Observer* observer)
{
    
    expect_string("keyframes");
    
    while(1)
    {
        get_next_line(line, MAX_PARSER_LINE_LENGTH);
        make_uppercase(line);
        
        if (0==strcmp("MATERIAL", line))
        {
            int i = get_int();
            if (0 >= i || i > number_of_materials)
            {
                cout << "ERROR: Keyframe specified for material " << i 
                    << "\nmust specify in range 1 to " << number_of_materials << endl;
                exit(666);
            }
            float time = get_float();
            
            get_next_line(line, MAX_PARSER_LINE_LENGTH);
            make_uppercase(line);
            if (0==strcmp("BASIC", line))
            {
                expect_string("COLOR");
                Vec3f color = get_Vec3f();
                
                expect_string("KD KS KN");
                Vec3f ks = get_Vec3f();
                
                expect_string("REFLECTION REFRACTION");
                float kl = get_float();
                float kr = get_float();
                
                expect_string("DENSITY");
                float density = get_float();
                
                expect_string("REFLECTION / REFRACTION BLUR ANGLES");
                float refl_ang = get_float();
                float refr_ang = get_float();
                
                
                material_list[i-1]->add_keyframe(time, color, ks.x, ks.y, ks.z, kl, kr, density, refl_ang, refr_ang);
            }
            else
            {
                cout << "PARSING ERROR: Keyframe for unknown material type: " << line << endl;
                exit(666);
            }
        }
        else if (0==strcmp("OBSERVER", line))
        {
            float time = get_float();
            
            expect_string("POSITION");
            Vec3f obs_pos = get_Vec3f();
            
            expect_string("LOOK AT");
            Vec3f obs_coi = get_Vec3f();
            
            expect_string("TILT");
            float obs_tilt = get_float();
            
            expect_string("ANGLE OF VIEW");
            float obs_fov = get_float();
            
            expect_string("LENSE RADIUS");
            float obs_lens_rad = get_float();
            
            expect_string("PIXEL SIZE");
            float obs_pix_size = get_float();
            
            observer->add_keyframe(
                time,
                obs_pos, 
                obs_coi, 
                obs_tilt, 
                obs_fov, 
                observer->get_aspect_ratio(), 
                obs_lens_rad, 
                obs_pix_size);
        }
        else if(0 == strcmp("END KEYFRAMES", line))
        {
            break;
        }
        else
        {
            cout << "PARSING ERROR: Expecting a keyframe definition or 'END KEYFRAMES'" << endl;
            exit(666);
        }
    }
}
