// Buffer.cpp: implementation of the Buffer class.
//
//////////////////////////////////////////////////////////////////////
// Vincent Scheib

#include "Buffer.h"

#include <stdio.h>
#include <fstream.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Buffer::Buffer(const int w, const int h)
{
    the_buffer = new Vec3f[h*w];
    if(!the_buffer)
    {
        cout << "\nOUT OF MEMORY: can not create buffer.\n" << endl;
        the_height = the_width = 0;
    }
    else
    {
        the_height = h;
        the_width  = w;
    }

    is_adaptive = 0;
    adaptive_full_screen_count =0;
    adaptive_total_samples =0;
}

Buffer::~Buffer()
{ 
    if (the_buffer && the_height != 0 && the_width != 0)
    {
        delete [] the_buffer; 
        the_height = 0;
        the_width  = 0;
    }

    if (is_adaptive)
    {
        delete [] the_adaptive_stuff;
//        delete [] the_sorter;
    }
}


//////////////////////////////////////////////////////////////////////
// Clear
//////////////////////////////////////////////////////////////////////

void Buffer::Clear(const Vec3f color)
{ 
    for(int y=0; y<the_height; y++) 
    {
        int yw = y*the_width;
        for(int x=0; x<the_width; x++)
            the_buffer[yw+x] = color;
    }
}


//////////////////////////////////////////////////////////////////////
// put_color
//////////////////////////////////////////////////////////////////////

void Buffer::put_color(const int x, const int y, const Vec3f color)
{
	assert ((x >= 0) && (x < the_width) &&
			(y >= 0) && (y < the_height));

	if (is_adaptive==0)
  {
    the_buffer[y*the_width+x] = color;
  }
  else
  {
    Vec3f old_avg;
    float old_weight;
    float old_error;
    float new_weight;
    Vec3f new_avg;
    float new_error;

    old_avg = the_buffer[y*the_width+x];
    old_error = the_adaptive_stuff[y*the_width+x].y;
    old_weight = the_adaptive_stuff[y*the_width+x].x;
    new_weight = old_weight + 1.0f;

    new_avg = old_avg * (old_weight / new_weight) + color * ( 1.0f / new_weight );
    new_error = (color - new_avg).length();
    new_error = old_error * (old_weight / new_weight) + new_error * ( 1.0f / new_weight );

    the_buffer[y*the_width+x] = new_avg;
    the_adaptive_stuff[y*the_width+x].x = new_weight;
    the_adaptive_stuff[y*the_width+x].y = new_error;
    the_adaptive_stuff[y*the_width+x].z = new_error/new_weight;

    adaptive_total_samples++;

    /*
    the_sorter[y*the_width+x+1].prev->next = the_sorter[y*the_width+x+1].next;
    the_sorter[y*the_width+x+1].next->prev = the_sorter[y*the_width+x+1].prev;
    insert(y*the_width+x+1);
    */
  }
}

/*
void Buffer::insert(const int i)
{
  int j = i-1;
  while (the_adaptive_stuff[i-1].z < the_adaptive_stuff[j-1].z)
  {
    j = (the_sorter[j].prev - the_sorter[0])
}
*/

//////////////////////////////////////////////////////////////////////
// get_color
//////////////////////////////////////////////////////////////////////

const Vec3f Buffer::get_color(const int x, const int y) // Linear interp
{
  assert ((x >= 0) && (x < the_width) &&
    (y >= 0) && (y < the_height));
  
  return the_buffer[y*the_width+x];
}


const Vec3f Buffer::get_color(const float x, const float y) // Linear Interpolation
{
  float rx, ry;
  int   ix, iy, ix2, iy2;
  float wx, wy, wx2, wy2;

  assert (0 < the_width);
  assert (0 < the_height);

  // remap to a safe of 0 - (size-1)
  rx = x - (float)0.5;
  ry = y - (float)0.5;

  ix = (int)rx;
  iy = (int)ry;
  
  ix2 = ix + 1;
  iy2 = iy + 1;

  wx = rx - ix;
  wy = ry - iy;

  wx2 = (float)1.0-wx;
  wy2 = (float)1.0-wy;
  
  // Clamp
  if (ix < 0) ix = 0;
  if (iy < 0) iy = 0;
  if (ix2 < 0) ix2 = 0;
  if (iy2 < 0) iy2 = 0;
  if (ix > (the_width-1)) ix = (the_width-1);
  if (iy > (the_height-1)) iy = (the_height-1);
  if (ix2 > (the_width-1)) ix2 = (the_width-1);
  if (iy2 > (the_height-1)) iy2 = (the_height-1);

  return wx2*wy2*the_buffer[iy *the_width+ix ] + 
         wx *wy2*the_buffer[iy *the_width+ix2] + 
         wx2*wy *the_buffer[iy2*the_width+ix ] + 
         wx *wy *the_buffer[iy2*the_width+ix2];
}


const Vec3f Buffer::get_color_01(const float x, const float y) // Linear Interpolation
{
  float rx, ry;
  int   ix, iy, ix2, iy2;
  float wx, wy, wx2, wy2;

  assert (0 < the_width);
  assert (0 < the_height);

  // remap to a safe of 0 - (size-1)
  rx = x*the_width - (float)0.5;
  ry = y*the_height - (float)0.5;

  ix = (int)rx;
  iy = (int)ry;
  
  ix2 = ix + 1;
  iy2 = iy + 1;

  wx = rx - ix;
  wy = ry - iy;

  wx2 = (float)1.0-wx;
  wy2 = (float)1.0-wy;
  
  // Clamp
  if (ix < 0) ix = 0;
  if (iy < 0) iy = 0;
  if (ix2 < 0) ix2 = 0;
  if (iy2 < 0) iy2 = 0;
  if (ix > (the_width-1)) ix = (the_width-1);
  if (iy > (the_height-1)) iy = (the_height-1);
  if (ix2 > (the_width-1)) ix2 = (the_width-1);
  if (iy2 > (the_height-1)) iy2 = (the_height-1);

  return wx2*wy2*the_buffer[iy *the_width+ix ] + 
         wx *wy2*the_buffer[iy *the_width+ix2] + 
         wx2*wy *the_buffer[iy2*the_width+ix ] + 
         wx *wy *the_buffer[iy2*the_width+ix2];
}


//////////////////////////////////////////////////////////////////////
// WriteTGA
//////////////////////////////////////////////////////////////////////

void Buffer::WriteTGA(const char *filename)
{
    ofstream f(filename, ios::out | ios::binary);

    if (!f.good())
    {
        cout << "\nUNABLE TO OPEN FILE FOR WRITE: " << filename
            << "\n\taborting file write, sorry.\n" << endl;
        return;
    }
    cout << "\nWriting buffer to file: " << filename << endl;

    typedef char byte;
    typedef unsigned short word;

    // Header.
    f.put((char)0);   // 1 byte   Length of image identification field (below)
    f.put((char)0);   // 1 byte   Color map type :
                      //          0 - no color map
                      //          1 - 256 entry palette
    f.put((char)2);   // 1 byte   Image type :
                      //           0 - no image data included
                      //           1 - Uncompressed, color-mapped image
                      //           2 - Uncompressed, RGB image
                      //           3 - Uncompressed, black and white image
                      //           9 - RLE encoded color-mapped image
                      //          10 - RLE encoded RGB image
                      //          11 - Compressed, black and white image
                      //          32 - Compressed color-mapped data, using
                      //               Huffman, Delta, and runlength encoding.
                      //          33 - Compressed color-mapped data, using
                      //               Huffman, Delta, and RLE.  4-pass quadtree-
                      //               type process.
    f.put((char)0);   
    f.put((char)0);   //     1 word   Index of first color map entry
    f.put((char)0);   
    f.put((char)0);   //     1 word   Count of color map entries
    f.put((char)0);   //     1 byte   Number of bits per color map entry
    f.put((char)0);   
    f.put((char)0);   //     1 word   X coordinate of the lower left corner of
                      //              the image.
    f.put((char)0);   
    f.put((char)0);   //     1 word   Y coordinate of the lower left corner of
                      //              the image.
    f.put((char)(the_width & 0xFF));
    f.put((char)(the_width >> 8));
                      //     1 word   Width of the image in pixels
    f.put((char)(the_height & 0xFF));
    f.put((char)(the_height >> 8));
                      //     1 word   Height of the image in pixels
    f.put((char)24);   
                      //     1 byte   Bits per pixel

    f.put((char)0);   
                      //     1 byte   Flags (bitmapped):
                      //              0-3 : Number of attribute bits
                      //                4 : reserved
                      //                5 : Screen origin in upper left corner
                      //              6-7 : Data storage interleave
                      //                    00 - no interleave
                      //                    01 - even/odd interleave
                      //                    10 - four way interleave
                      //                    11 - reserved
                      //              The byte should be set to 0. Don't know why.
                      //     ? char   Image identification string, usually not there,
                      //              when the length (see up) is 0.
                      //     ? byte   Color map data
                      //              Depending on the number of bits per color map
                      //              entry, the entries here have a different size.
                      //             4 bytes : 1 byte for blue
                      //                       1 byte for green
                      //                       1 byte for red
                      //                       1 byte for attribute
                      //             3 bytes : 1 byte for blue
                      //                       1 byte for green
                      //                       1 byte for red
                      //             2 bytes : Bitmapped as a word in Intel byte
                      //                       order as follows :
                      //                       ARRRRRGG GGGBBBBB
                      //    ? byte   Image data
                      //             For images of type 9 (using RLE), the image
                      //             data is divided into packets, the first byte
                      //             being the indicator for repetition or copy.
                      //             If bit 7 of the first byte is set, then repeat
                      //           ((char)first byte and 07Fh+1) times the next byte,
                      //             otherwise copy first byte+1 pixels from data
                      //             stream. RLE packets may cross scan lines !

    Vec3f temp_vec;
    for(int y=the_height-1; y>=0; y--)      // bottom up to top
    {
        int yw = y*the_width;
        for(int x=0; x<the_width; x++)      // left to right
        {
            temp_vec = the_buffer[yw+x];
            temp_vec.clamp();
            f.put((char)(temp_vec.z*255));  // blue
            f.put((char)(temp_vec.y*255));  // green
            f.put((char)(temp_vec.x*255));  // red
        }            
    }

    f.close();
}





//////////////////////////////////////////////////////////////////////
// ReadTGA
//////////////////////////////////////////////////////////////////////

void Buffer::ReadTGA(const char *filename)
{
    // Delete current buffer
    if (the_buffer && the_height != 0 && the_width != 0)
    {
        delete [] the_buffer; 
        the_width  = 0;
        the_height = 0;
    }

    {
        FILE *fCheckFileExists = fopen(filename, "r");
        if (fCheckFileExists) fclose(fCheckFileExists);
        else { cout << "File does not exist." << endl; return; }
    }

    // Open file
    ifstream f(filename, ios::in | ios::binary); 

    cout << "\nReading file to buffer: " << filename << endl;


    // Header.
    int image_id_length = f.get();
    if (!f.good()) { cout << "Error reading file. byte:" << f.tellg() << endl; return; }
                  // 1 byte   Length of image identification field (below)

    int color_map_type = f.get();
    if (!f.good()) { cout << "Error reading file. byte: " << f.tellg() << endl; return; }
                  // 1 byte   Color map type :
                  //          0 - no color map
                  //          1 - 256 entry palette

    int image_type = f.get();
    if (!f.good()) { cout << "Error reading file. byte: " << f.tellg() << endl; return; }
                  // 1 byte   Image type :
                  //           0 - no image data included
                  //           1 - Uncompressed, color-mapped image
                  //           2 - Uncompressed, RGB image
                  //           3 - Uncompressed, black and white image
                  //           9 - RLE encoded color-mapped image
                  //          10 - RLE encoded RGB image
                  //          11 - Compressed, black and white image
                  //          32 - Compressed color-mapped data, using
                  //               Huffman, Delta, and runlength encoding.
                  //          33 - Compressed color-mapped data, using
                  //               Huffman, Delta, and RLE.  4-pass quadtree-
                  //               type process.

    int color_map_index =  f.get();
        color_map_index += f.get() << 8;
    if (!f.good()) { cout << "Error reading file. byte: " << f.tellg() << endl; return; }
                      //     1 word   Index of first color map entry
    
    int color_map_count =  f.get();
        color_map_count += f.get() << 8;
    if (!f.good()) { cout << "Error reading file. byte: " << f.tellg() << endl; return; }
                      //     1 word   Count of color map entries

    int color_map_bits  = f.get();
    if (!f.good()) { cout << "Error reading file. byte: " << f.tellg() << endl; return; }
                      //     1 byte   Number of bits per color map entry

    int lower_left_corner_x_pos =  f.get();
        lower_left_corner_x_pos += f.get() << 8;
    if (!f.good()) { cout << "Error reading file. byte: " << f.tellg() << endl; return; }
                      //     1 word   X coordinate of the lower left corner of
                      //              the image.

    int lower_left_corner_y_pos =  f.get();
        lower_left_corner_y_pos += f.get() << 8;
    if (!f.good()) { cout << "Error reading file. byte: " << f.tellg() << endl; return; }
                      //     1 word   Y coordinate of the lower left corner of
                      //              the image.

    int image_width =  f.get();
        image_width += f.get() << 8;
    if (!f.good()) { cout << "Error reading file. byte: " << f.tellg() << endl; return; }
                  //     1 word   Width of the image in pixels

    int image_height =  f.get(); 
        image_height += f.get() << 8;
    if (!f.good()) { cout << "Error reading file. byte: " << f.tellg() << endl; return; }
                  //     1 word   Height of the image in pixels

    int bits_per_pixel = f.get();
    if (!f.good()) { cout << "Error reading file. byte: " << f.tellg() << endl; return; }
                  //     1 byte   Bits per pixel

    int image_flags = f.get();
    if (!f.good()) { cout << "Error reading file. byte: " << f.tellg() << endl; return; }
                  //     1 byte   Flags (bitmapped):
                  //              0-3 : Number of attribute bits
                  //                4 : reserved
                  //                5 : Screen origin in upper left corner
                  //              6-7 : Data storage interleave
                  //                    00 - no interleave
                  //                    01 - even/odd interleave
                  //                    10 - four way interleave
                  //                    11 - reserved
                  //              The byte should be set to 0. Don't know why.


                  //     ? char   Image identification string, usually not there,
                  //              when the length (see up) is 0.


                  //     ? byte   Color map data
                  //              Depending on the number of bits per color map
                  //              entry, the entries here have a different size.
                  //             4 bytes : 1 byte for blue
                  //                       1 byte for green
                  //                       1 byte for red
                  //                       1 byte for attribute
                  //             3 bytes : 1 byte for blue
                  //                       1 byte for green
                  //                       1 byte for red
                  //             2 bytes : Bitmapped as a word in Intel byte
                  //                       order as follows :
                  //                       ARRRRRGG GGGBBBBB
                  //    ? byte   Image data
                  //             For images of type 9 (using RLE), the image
                  //             data is divided into packets, the first byte
                  //             being the indicator for repetition or copy.
                  //             If bit 7 of the first byte is set, then repeat
                  //           ((char)first byte and 07Fh+1) times the next byte,
                  //             otherwise copy first byte+1 pixels from data
                  //             stream. RLE packets may cross scan lines !

    //! only read most simple of file formats.
    if( ! (   (image_id_length == 0)
           && (color_map_type == 0)
           && (image_type == 2) 
           && (bits_per_pixel == 24)
           && (image_flags == 0) ) ) 
    {
        cout << "ERROR: Don't know how to decode this tga file, make simple." << endl;
        cout << "image_id_length = " << image_id_length << ", wanted 0 " << endl;
        cout << "color_map_type  = " << color_map_type  << ", wanted 0 " << endl;
        cout << "image_type      = " << image_type      << ", wanted 2 " << endl;
        cout << "bits_per_pixel  = " << bits_per_pixel  << ", wanted 24" << endl;
        cout << "image_flags     = " << image_flags     << ", wanted 0 " << endl;
            
        return;
    }


    // Allocate memory
    the_buffer = new Vec3f[image_height*image_width];
    if(!the_buffer)
    {
        cout << "\nOUT OF MEMORY: can not create buffer.\n" << endl;
        return;
    }
    else
    {
        the_height = image_height;
        the_width  = image_width;
    }


    // Read pixels
    Vec3f *temp_vec;
    for(int y=the_height-1; y>=0; y--)      // bottom up to top
    {
        int yw = y*the_width;
        for(int x=0; x<the_width; x++)      // left to right
        {
            temp_vec = &the_buffer[yw+x];
            temp_vec->z = f.get()/255.0f;  // blue
            temp_vec->y = f.get()/255.0f;  // green
            temp_vec->x = f.get()/255.0f;  // red

            if(!f.good()) { 
                cout << "ERROR reading file in color data. byte:" << f.tellg() << endl; 
                return; 
            }
        }            
    }

    f.close();
}


//////////////////////////////////////////////////////////////////////
// makeAdaptive
//////////////////////////////////////////////////////////////////////
void Buffer::makeAdaptive()
{
  is_adaptive = 1;

  the_adaptive_stuff = new Vec3f[the_width * the_height + 2];
  /*
  the_sorter = new sorter[the_width * the_height];
  sorthead.prev = null;
  sorthead.next = the_sorter;
  sorttail.prev = &(the_sorter[the_width * the_height - 1]);
  sorttail.next = null;
  */
  /*
  {
    int i;
    for (i=0; i< (the_width * the_height + 2); i++)
    {
      the_sorter[i].prev = &(the_sorter[i-1]);
      the_sorter[i].next = &(the_sorter[i+1]);
    }
  }
  */
}




//////////////////////////////////////////////////////////////////////
// WriteAdaptive
//////////////////////////////////////////////////////////////////////

void Buffer::WriteAdaptive(const char *filename)
{
    ofstream f(filename, ios::out | ios::binary);

    if (!f.good())
    {
        cout << "\nUNABLE TO OPEN FILE FOR WRITE: " << filename
            << "\n\taborting file write, sorry.\n" << endl;
        return;
    }
    cout << "\nWriting buffer to file: " << filename << endl;

    typedef char byte;
    typedef unsigned short word;

    // Header.
    f.put('a');
    f.put('d');
    f.put('a');
    f.put('p');
    f.put('t');
    f.put('i');
    f.put('v');
    f.put('e');
    f.put(' ');
    f.put('1');
    f.put('.');
    f.put('0');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put('-');
    f.put((char)(the_width & 0xFF));
    f.put((char)(the_width >> 8));
                      //     1 word   Width of the image in pixels
    f.put((char)(the_height & 0xFF));
    f.put((char)(the_height >> 8));
                      //     1 word   Height of the image in pixels

    f.put((char)((adaptive_full_screen_count >> 24) & 0xFF));
    f.put((char)((adaptive_full_screen_count >> 16) & 0xFF));
    f.put((char)((adaptive_full_screen_count >>  8) & 0xFF));
    f.put((char)((adaptive_full_screen_count >>  0) & 0xFF));

    f.put((char)((adaptive_total_samples >> 24) & 0xFF));
    f.put((char)((adaptive_total_samples >> 16) & 0xFF));
    f.put((char)((adaptive_total_samples >>  8) & 0xFF));
    f.put((char)((adaptive_total_samples >>  0) & 0xFF));

    f.write((char*)the_buffer, the_width*the_height*sizeof(Vec3f));
    f.write((char*)the_adaptive_stuff, the_width*the_height*sizeof(Vec3f));


    f.close();
}





//////////////////////////////////////////////////////////////////////
// ReadAdaptive
//////////////////////////////////////////////////////////////////////

void Buffer::ReadAdaptive(const char *filename)
{
    // Delete current buffer
    if (the_buffer && the_height != 0 && the_width != 0)
    {
        delete [] the_buffer; 
        the_width  = 0;
        the_height = 0;
        delete [] the_adaptive_stuff;
    }

    {
        FILE *fCheckFileExists = fopen(filename, "r");
        if (fCheckFileExists) fclose(fCheckFileExists);
        else { cout << "File does not exist." << endl; return; }
    }

    // Open file
    ifstream f(filename, ios::in | ios::binary); 

    cout << "\nReading file to buffer: " << filename << endl;


    // Header.
    {
      int i;
      for (i=0; i<32; i++)
      {
        f.get();
        if (!f.good()) { cout << "Error reading file. byte:" << f.tellg() << endl; return; }
      }
    }

    int image_width =  f.get();
        image_width += f.get() << 8;
    if (!f.good()) { cout << "Error reading file. byte: " << f.tellg() << endl; return; }
                  //     1 word   Width of the image in pixels

    int image_height =  f.get(); 
        image_height += f.get() << 8;
    if (!f.good()) { cout << "Error reading file. byte: " << f.tellg() << endl; return; }
                  //     1 word   Height of the image in pixels

    adaptive_full_screen_count =  f.get() << 24;
    adaptive_full_screen_count += f.get() << 16;
    adaptive_full_screen_count += f.get() << 8;
    adaptive_full_screen_count += f.get() << 0;
    if (!f.good()) { cout << "Error reading file. byte: " << f.tellg() << endl; return; }
    
    adaptive_total_samples =  f.get() << 24; 
    adaptive_total_samples += f.get() << 16;
    adaptive_total_samples += f.get() << 8;
    adaptive_total_samples += f.get() << 0;
    if (!f.good()) { cout << "Error reading file. byte: " << f.tellg() << endl; return; }

    // Allocate memory
    the_buffer = new Vec3f[image_height*image_width];
    the_adaptive_stuff= new Vec3f[image_height*image_width];
    if(!the_buffer || !the_adaptive_stuff)
    {
        cout << "\nOUT OF MEMORY: can not create buffer.\n" << endl;
        return;
    }
    else
    {
        the_height = image_height;
        the_width  = image_width;
    }


    f.read((char*)the_buffer, the_width*the_height*sizeof(Vec3f));
    f.read((char*)the_adaptive_stuff, the_width*the_height*sizeof(Vec3f));

    f.close();
}


void Buffer::WriteAdaptiveDebug(const char *filename)
{
    ofstream f(filename, ios::out | ios::binary);

    if (!f.good())
    {
        cout << "\nUNABLE TO OPEN FILE FOR WRITE: " << filename
            << "\n\taborting file write, sorry.\n" << endl;
        return;
    }
    cout << "\nWriting buffer to file: " << filename << endl;

    typedef char byte;
    typedef unsigned short word;

    // Header.
    f.put((char)0);   // 1 byte   Length of image identification field (below)
    f.put((char)0);   // 1 byte   Color map type :
                      //          0 - no color map
                      //          1 - 256 entry palette
    f.put((char)2);   // 1 byte   Image type :
                      //           0 - no image data included
                      //           1 - Uncompressed, color-mapped image
                      //           2 - Uncompressed, RGB image
                      //           3 - Uncompressed, black and white image
                      //           9 - RLE encoded color-mapped image
                      //          10 - RLE encoded RGB image
                      //          11 - Compressed, black and white image
                      //          32 - Compressed color-mapped data, using
                      //               Huffman, Delta, and runlength encoding.
                      //          33 - Compressed color-mapped data, using
                      //               Huffman, Delta, and RLE.  4-pass quadtree-
                      //               type process.
    f.put((char)0);   
    f.put((char)0);   //     1 word   Index of first color map entry
    f.put((char)0);   
    f.put((char)0);   //     1 word   Count of color map entries
    f.put((char)0);   //     1 byte   Number of bits per color map entry
    f.put((char)0);   
    f.put((char)0);   //     1 word   X coordinate of the lower left corner of
                      //              the image.
    f.put((char)0);   
    f.put((char)0);   //     1 word   Y coordinate of the lower left corner of
                      //              the image.
    f.put((char)(the_width & 0xFF));
    f.put((char)(the_width >> 8));
                      //     1 word   Width of the image in pixels
    f.put((char)(the_height & 0xFF));
    f.put((char)(the_height >> 8));
                      //     1 word   Height of the image in pixels
    f.put((char)24);   
                      //     1 byte   Bits per pixel

    f.put((char)0);   
                      //     1 byte   Flags (bitmapped):
                      //              0-3 : Number of attribute bits
                      //                4 : reserved
                      //                5 : Screen origin in upper left corner
                      //              6-7 : Data storage interleave
                      //                    00 - no interleave
                      //                    01 - even/odd interleave
                      //                    10 - four way interleave
                      //                    11 - reserved
                      //              The byte should be set to 0. Don't know why.
                      //     ? char   Image identification string, usually not there,
                      //              when the length (see up) is 0.
                      //     ? byte   Color map data
                      //              Depending on the number of bits per color map
                      //              entry, the entries here have a different size.
                      //             4 bytes : 1 byte for blue
                      //                       1 byte for green
                      //                       1 byte for red
                      //                       1 byte for attribute
                      //             3 bytes : 1 byte for blue
                      //                       1 byte for green
                      //                       1 byte for red
                      //             2 bytes : Bitmapped as a word in Intel byte
                      //                       order as follows :
                      //                       ARRRRRGG GGGBBBBB
                      //    ? byte   Image data
                      //             For images of type 9 (using RLE), the image
                      //             data is divided into packets, the first byte
                      //             being the indicator for repetition or copy.
                      //             If bit 7 of the first byte is set, then repeat
                      //           ((char)first byte and 07Fh+1) times the next byte,
                      //             otherwise copy first byte+1 pixels from data
                      //             stream. RLE packets may cross scan lines !

    Vec3f temp_vec;
    for(int y=the_height-1; y>=0; y--)      // bottom up to top
    {
        int yw = y*the_width;
        for(int x=0; x<the_width; x++)      // left to right
        {
            temp_vec = the_adaptive_stuff[yw+x];
            temp_vec.x*=0.5f/255.0f;
            temp_vec.y*=250.0f/255.0f;
            temp_vec.z*=200000.0f/255.0f;
            temp_vec.clamp();
            f.put((char)(temp_vec.z*255));  // blue
            f.put((char)(temp_vec.y*255));  // green
            f.put((char)(temp_vec.x*255));  // red
        }            
    }

    f.close();
}

