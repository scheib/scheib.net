// Raycaster
// Vince Scheib
// -------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include <time.h>

#include "Parser.h"
#include "Buffer.h"
#include "Scene.h"
#include "SceneLight.h"
#include "PointLight.h"
#include "SceneObject.h"
#include "ObjSphere.h"
#include "SceneEnvironment.h"
#include "SimpleSkyEnv.h"
#include "Observer.h"
#include "Material.h"
#include "Merge.h"

int main(int argc, char* argv[])
{
  {  /*
    Buffer test;
    test.ReadTGA("snowcliff_ft.tga");

    test.put_color(0,0,Vec3f(0,0,0));
    test.put_color(0,1,Vec3f(0,0,0));
    test.put_color(2,0,Vec3f(0,0,0));
    test.put_color(2,1,Vec3f(0,0,0));

    test.WriteTGA("t.tga");
    exit(0); //*/
  } 

    srand( (unsigned)time( NULL ) ); // Randomize seeded by timer
        
    istream *input;
    
    if (argc == 2)
    {
        input = new ifstream(argv[1]);
        if (!input)
        {
            cout << "Could not open scriptfile: " << argv[1] << endl;
            exit (1);
            cout << "Raytracer reading script file from" << argv[1] << "." << endl;
        }
    }
    else
    {
        input = &cin;
        cout << "Raytracer waiting for redirected script file input." << endl;
    }
    
    Parser parser(input);
    
    
    // SCRIPT HEADER
    parser.expect_string("raycaster scriptfile v2.1");
    
    
    
    // BUFFER INFORMATION
    parser.expect_string("screen resolution");
    int screen_x = parser.get_int();
    int screen_y = parser.get_int();
    cout << "Buffer resolution: width:" << screen_x << " height:" << screen_y << endl;
    
    
    
    parser.expect_string("filename");
    char filename[100] = {0};
    parser.get_next_line(filename, 100);
    if (0==strlen(filename))
    {
        cout << "\n\nSCRIPT PARSING ERROR: Expecting a filename" << endl;
        exit (1);
    }
    cout << "Output file base name:" << filename << endl;
    
    
    // SCENE INFORMATION
    parser.expect_string("number of lights");
    int light_num = parser.get_int();
    cout << "Lights in scene:" << light_num << endl;
    
    parser.expect_string("number of materials");
    int material_num = parser.get_int();
    cout << "Lights in scene:" << material_num << endl;
    
    parser.expect_string("number of objects");
    int obj_num = parser.get_int();
    cout << "Objects in scene:" << obj_num << endl;
    
    parser.expect_string("recursion depth");
    int recursion_depth = parser.get_int();
    cout << "Recursion depth of ray:" << recursion_depth << endl;
    
    parser.expect_string("samples per pixel");
    int samples_per_pixel = parser.get_int();
    cout << "oversample:" << samples_per_pixel << endl;
    
    parser.expect_string("BEGIN / END FRAME");
    int frame_begin = parser.get_int();
    int frame_end   = parser.get_int();
    cout << "frame begin / end:" << frame_begin << " " << frame_end << endl;
    
    parser.expect_string("FRAME INCREMENT / WIDTH");
    int frame_increment = parser.get_int();
    float frame_width = parser.get_float();
    cout << "frame_increment:" << frame_increment << endl;
    cout << "frame_width:" << frame_width << endl;

    parser.expect_string("ADAPTIVE BUFFER");
    int use_adaptive_buffer = 0;
    int adaptive_min;
    int adaptive_samples;
    if (parser.get_int() == 1)
    {
      use_adaptive_buffer = 1;
      adaptive_min = parser.get_int();
      adaptive_samples = parser.get_int();
    }


    // ENVIRONMENT
    SceneEnvironment *environment = parser.get_environment();
    
    // LIGHTS
    SceneLight **light_list = parser.get_lights(light_num);
    
    // MATERIALS
    Material **material_list = parser.get_materials(material_num);
    
    // OBJECTS
    SceneObject **obj_list = parser.get_objects(obj_num, material_list);
    
    // OBSERVER INFORMATION
    Observer *observer = parser.get_observer(screen_y / (float)screen_x);
    
    // KEYFRAMES
    parser.get_keyframes(environment, light_list, light_num, material_list, material_num, obj_list, obj_num, observer);
    
    parser.expect_string("GO");
    
    
    
    cout << "\n---------------\n  Rendering... \n---------------" << endl;
    
    //------------------------------------------
    // DO IT
    //------------------------------------------
    
    Buffer buffer(screen_x, screen_y);
    if (use_adaptive_buffer==1) buffer.makeAdaptive();

    Scene scene = Scene(light_num, obj_num, recursion_depth);
    
    { // Place lights and objects in scene
        int i;
        for (i=0; i<light_num; i++)
            scene.add_light( light_list[i] );
        for (i=0; i<obj_num; i++)
            scene.add_object( obj_list[i] );
    }
    
    scene.set_environment(environment);
    scene.set_observer(observer);  // MUST SET OBSERVER BEFORE UPDATING OBJECT GEOMETRY (so objects know where camera is)
    scene.set_material_list(material_list, material_num);


    int frame = 0;      // to be expanded upon later

    if (use_adaptive_buffer == 0)
    {
      for (int subframe=0; subframe<samples_per_pixel; subframe++)
      {
        for (frame = frame_begin; frame <= frame_end; frame += frame_increment)
        {
          // generate filename for this image
          char sub_filename[256], temp[16];
          sprintf(temp, "-%04d-%03d.tga", frame, subframe);
          strcpy(sub_filename, filename);
          strcat(sub_filename, temp);
          
          FILE *fCheckFileExists = fopen(sub_filename, "r");
          if (fCheckFileExists) fclose(fCheckFileExists);
          
          if (fCheckFileExists)            // skip this subframe
          {
            cout << "Skipping frame " << frame << ", subsample #" << subframe << endl;
          }
          else                                // otherwise render the subframe
          {
            FILE *fPlaceHolder = fopen(sub_filename, "wb");
            fclose(fPlaceHolder);
            
            cout << "Rendering frame " << frame << ", subsample #" << subframe << endl;
            
            scene.draw(buffer, (float)frame, frame_width);
            buffer.WriteTGA(sub_filename);
            
          }
        }
      }
      
      //------------------------------------------
      // Merge subframes into one final frame
      //------------------------------------------
      for (frame = frame_begin; frame <= frame_end; frame += frame_increment)
      {
        Merge_Frame(filename, frame, screen_x, screen_y, samples_per_pixel);
      }

      //------------------------------------------
      // Merge subframes into one final frame
      //------------------------------------------
      for (frame = frame_begin; frame <= frame_end; frame += frame_increment)
      {
        Merge_Frame(filename, frame, screen_x, screen_y, samples_per_pixel);
      }

    }
    else // Adaptive
    {
      for (int justonce=0; justonce<1; justonce++)
      {
        {
          FILE *fStopFileExists = fopen("stop", "r");
          if (fStopFileExists) 
          {
            fclose(fStopFileExists);        
            break;
          }        
        }
        
        for (frame = frame_begin; frame <= frame_end; frame += frame_increment)
        {
          // generate filename for this image
          char sub_filename[256], temp[256];
          sprintf(temp, "-%04d-adaptive", frame);
          strcpy(sub_filename, filename);
          strcat(sub_filename, temp);
          strcat(sub_filename, ".rad");
          
          FILE *fCheckFileExists = fopen(sub_filename, "r");
          if (fCheckFileExists) fclose(fCheckFileExists);
          
          if (fCheckFileExists)            // load accumulation buffer
          {
            fclose(fCheckFileExists);
            cout << "Loading " << sub_filename << endl;
            buffer.ReadAdaptive(sub_filename);
          buffer.WriteAdaptiveDebug("t.tga");
          }
          
          while (buffer.adaptive_full_screen_count < adaptive_min)
          {
            cout << "Rendering Full scene " << buffer.adaptive_full_screen_count << " / " << adaptive_min << endl;
            scene.draw(buffer, (float)frame, frame_width);
            buffer.adaptive_full_screen_count++;
            {
              FILE *fStopFileExists = fopen("stop", "r");
              if (fStopFileExists) 
              {
                fclose(fStopFileExists);        
                buffer.WriteAdaptive(sub_filename);
                break;
              }        
            }
          }

          sprintf(temp, "-%04d-adaptiveD1", frame);
          strcpy(sub_filename, filename);
          strcat(sub_filename, temp);
          strcat(sub_filename, ".tga");
          buffer.WriteAdaptiveDebug(sub_filename);

          {
            cout << "Rendering part scene " << buffer.adaptive_full_screen_count << " / " << adaptive_min << endl;
            scene.adaptive_draw(buffer, (float)frame, frame_width, adaptive_samples);            
          }

          sprintf(temp, "-%04d-adaptive", frame);
          strcpy(sub_filename, filename);
          strcat(sub_filename, temp);
          strcat(sub_filename, ".rad");
          buffer.WriteAdaptive(sub_filename);
          
          sprintf(temp, "-%04d-adaptive(%d)", frame, buffer.adaptive_total_samples);
          strcpy(sub_filename, filename);
          strcat(sub_filename, temp);
          strcat(sub_filename, ".tga");
          buffer.WriteTGA(sub_filename);

          sprintf(temp, "-%04d-adaptive(%d)D2", frame, buffer.adaptive_total_samples);
          strcpy(sub_filename, filename);
          strcat(sub_filename, temp);
          strcat(sub_filename, ".tga");
          buffer.WriteAdaptiveDebug(sub_filename);

        }
      }
      
    }
    
    //------------------------------------------
    // CLEANUP
    //------------------------------------------
    {
        int i;
        
        for (i=0; i<light_num; i++)
            delete light_list[i];
        delete [] light_list;
        
        for (i=0; i<material_num; i++)
            delete material_list[i];
        delete [] material_list;
        
        for (i=0; i<obj_num; i++)
            delete obj_list[i];
        delete [] obj_list;
        
        delete environment;
        delete observer;
    }
    
    return 0;
}

