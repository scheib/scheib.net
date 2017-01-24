// Buffer.cpp: implementation of the Buffer class.
//
//////////////////////////////////////////////////////////////////////
// Vincent Scheib

#include "Buffer.h"

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
}

Buffer::~Buffer()
{ 
    if (the_buffer && the_height != 0 && the_width != 0)
    {
        delete [] the_buffer; 
        the_height = 0;
        the_width  = 0;
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
    the_buffer[y*the_width+x] = color;
}



//////////////////////////////////////////////////////////////////////
// get_color
//////////////////////////////////////////////////////////////////////

const Vec3f Buffer::get_color(const int x, const int y)
{
    return the_buffer[y*the_width+x];
}


//////////////////////////////////////////////////////////////////////
// WriteTGA
//////////////////////////////////////////////////////////////////////

void Buffer::WriteTGA(char *filename)
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

void Buffer::ReadTGA(char *filename)
{
    // Delete current buffer
    if (the_buffer && the_height != 0 && the_width != 0)
    {
        delete [] the_buffer; 
        the_width  = 0;
        the_height = 0;
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

