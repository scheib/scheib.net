
#ifndef IMAGEFILE_MERGE_H
#define IMAGEFILE_MERGE_H



void Merge_Frame(char *filename, 
                 int frame, 
                 int screen_x, 
                 int screen_y, 
                 int samples_per_pixel)
{
    // generate filename for merged image
    char merge_filename[256], temp[16];
    sprintf(temp, "_%04d.tga", frame);
    strcpy(merge_filename, filename);
    strcat(merge_filename, temp);

    FILE *fCheckMergefileExists = fopen(merge_filename, "r");
    if (fCheckMergefileExists) fclose(fCheckMergefileExists);

    if (fCheckMergefileExists)
    {
        cout << "Merged image already exists - skipping." << endl;
    }
    else
    {
        // Make a 0 size placeholder file before we start working on this
        FILE *fPlaceHolder = fopen(merge_filename, "wb");
        fclose(fPlaceHolder);

        cout << "Merging " << samples_per_pixel << " samples for frame " << frame << endl;

        unsigned int *merge_buffer = new unsigned int[screen_x*screen_y*3];
        unsigned char *temp_buffer = new unsigned char[screen_x*screen_y*3];

        memset(merge_buffer, 0, screen_x*screen_y*3*sizeof(int));

        for (int subframe=0; subframe<samples_per_pixel; subframe++)
        {
            // open subframe
            char sub_filename[256], temp[16];
            sprintf(temp, "-%04d-%03d.tga", frame, subframe);
            strcpy(sub_filename, filename);
            strcat(sub_filename, temp);

            FILE *infile = fopen(sub_filename, "rb");
            assert(infile);

            fread(temp_buffer, 18, 1, infile);
            assert(temp_buffer[12]+temp_buffer[13]*256 == screen_x);
            assert(temp_buffer[14]+temp_buffer[15]*256 == screen_y);
            assert(temp_buffer[16] == 24);

            fread(temp_buffer, screen_x*screen_y*3, 1, infile);

            for (int a = screen_x*screen_y*3-1; a>=0; a--)
                merge_buffer[a] += (int)temp_buffer[a];

            fclose(infile);
        }

        // divide by n; store merged image into regular old BYTE buffer
        for (int a=screen_x*screen_y*3-1; a>=0; a--)
            temp_buffer[a] = merge_buffer[a] / samples_per_pixel;

        // now write output file
        FILE *outfile = fopen(merge_filename, "wb");
        assert(outfile);
        fprintf(outfile, "%c%c%c%c%c%c",  0,  0,  2,  0,  0,  0);
        fprintf(outfile, "%c%c%c%c%c%c",  0,  0,  0,  0,  0,  0);
        fprintf(outfile, "%c%c%c%c%c%c", screen_x % 256, screen_x/256, screen_y % 256, screen_y/256, 24, 0);
        fwrite(temp_buffer, screen_x*screen_y*3, 1, outfile);

        // cleanup
        delete [] merge_buffer;
        delete [] temp_buffer;
    }
}





#endif