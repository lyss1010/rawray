/////////////////////////////////////////////////////////////////////////////
// pfm_loader.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "pfm_loader.h"
#include "base/conversions.h"
#include <stdexcept>

namespace tools {

Vector4* PFMLoader::ReadPFMImage(const char* filename, int* width, int* height) {
    FILE *infile = 0;
    float *lineBuffer = 0;
    Vector4 *img = 0;
    char junk;

    try
    {
        infile = fopen(filename, "rb");
        if (!infile)
            throw std::runtime_error("cannot open file.");

        int a = fgetc(infile);
        int b = fgetc(infile);
        fgetc(infile);

        if ((a != 'P') || ((b != 'F') && (b != 'f')))
            throw std::runtime_error("not a PFM image file.");

        b = (b == 'F');		// 'F' = RGB,  'f' = monochrome

        fscanf(infile, "%d %d%c", width, height, &junk);
        if ((*width <= 0) || (*height <= 0))
            throw std::runtime_error("invalid width or height.");

        float scaleFactor;
        fscanf(infile, "%f%c", &scaleFactor, &junk);

        img = new Vector4[*width * *height];

        a = *width * (b ? 3 : 1);
        lineBuffer = new float[a];
        for (int y = 0; y < *height; ++y)
        {
            Vector4 *cur = &img[y * *width];
            if (fread(lineBuffer, sizeof(float), a, infile) != (size_t) a)
                throw std::runtime_error("cannot read pixel data.");

            float *temp = lineBuffer;
            for (int x = 0; x < *width; x++)
            {
                if (b)
                {   // color
                    cur->x = *temp++;
                    cur->y = *temp++;
                    cur->z = *temp++;
					cur->w = 0.0f;

                    if (scaleFactor > 0.0)
                    {
                        base::BigEndianFloat( cur->x );
                        base::BigEndianFloat( cur->y );
                        base::BigEndianFloat( cur->z );
						base::BigEndianFloat( cur->w );
                    }
                    else
                    {
                        base::LittleEndianFloat( cur->x );
						base::LittleEndianFloat( cur->y );
						base::LittleEndianFloat( cur->z );
						base::LittleEndianFloat( cur->w );
                    }
                }
                else
                {   // black and white
                    float c = *temp++;

                    if (scaleFactor > 0.0)
                        base::BigEndianFloat(c);
                    else
                        base::LittleEndianFloat(c);

					cur->x = cur->y = cur->z = c;
					cur->w = 0.0f;
                }
                cur++;
            }
        }

        delete [] lineBuffer;
        fclose(infile);

        return img;
    }
    catch (const std::exception &e)
    {
        printf("Unable to read image file \"%s\": %s",
               filename, e.what());
        delete [] lineBuffer;
        delete [] img;
        if (infile)
            fclose (infile);
        return 0;
    }
    catch (...)
    {
        printf("Unable to read image file \"%s\".", filename);
        delete [] lineBuffer;
        delete [] img;
        if (infile)
            fclose (infile);
        return 0;
    }
}

} // namespace tools