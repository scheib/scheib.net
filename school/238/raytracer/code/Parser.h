// Parser.h: interface for the Parser class.
//
//////////////////////////////////////////////////////////////////////
//
// Parses components of a script file.

#ifndef PARSER_H
#define PARSER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>

#include "Buffer.h"
#include "Scene.h"
#include "SceneLight.h"
#include "PointLight.h"
#include "SceneObject.h"
#include "ObjSphere.h"
#include "ObjPoly.h"
#include "ObjTexturedFloorQuad.h"
#include "SceneEnvironment.h"
#include "CubeSkyMap.h"
#include "SimpleSkyEnv.h"
#include "Observer.h"
#include "Material.h"


#define MAX_PARSER_LINE_LENGTH 500


class Parser  
{
public:
	Parser(istream *_input);
	virtual ~Parser();

  // Reads the next line from 'input' to 'str' of maximum 'length'
  void get_next_line(char *str, int length);

  // Gets the next line from file and compare it to 'str' 
  // Exit program if line was not what we expected.
  // Case INsensitive
  void expect_string(const char *str);

  // Read a float 
  float get_float();

  // Read an int
  int get_int();

  // Read a 3 float Vector
  Vec3f get_Vec3f();

  // Read parameters for an environment, this is dynamically created and CALLER must delete.
  SceneEnvironment* get_environment();

  // Read parameters for the specified number of lights. 
  // This dynamically creates an array of pointers to SceneLights and CALLER must delete.
  SceneLight** get_lights(const int number_of_lights);

  // Read parameters for the specified number of materials. 
  // This dynamically creates an array of pointers to Material objects and CALLER must delete.
  Material** get_materials(const int number_of_materials);

  // Read parameters for the specified number of objects. 
  // This dynamically creates an array of pointers to SceneObject objects and CALLER must delete.
  // Warning, obj_num can be modified!
  SceneObject** get_objects(int &obj_num, Material** material_list);

  // Read parameters for the observer
  // This dynamically creates an Observer object and CALLER must delete.
  Observer* get_observer(const float aspect_ratio);

  // Read keyframes for components and update them
  void get_keyframes(
      SceneEnvironment* environment,
      SceneLight** light_list,
      const int number_of_lights,
      Material** material_list,
      const int number_of_materials,
      SceneObject** object_list,
      const int number_of_objects,
      Observer* observer);

protected:
  // Changes string to all uppercase
  void make_uppercase(char * str);

  istream *input;
  char line[MAX_PARSER_LINE_LENGTH]; // Internal use, lines are read to this and stored temporarily.
};

#endif 
