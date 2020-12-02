/** **************************************************************************
 * @file
 * 
 * @brief Main file for program
 ****************************************************************************/
/** **************************************************************************
  * @mainpage Program 1 - Image Manipulations
  *
  * @section course_section Course Information
  *
  * @author Adam Kraus
  *
  * @par Professor:
  *         Roger L. Schrader
  *
  * @par Course:
  *         CSC215 - M002 - Programming Techniques
  *
  * @par Location:
  *         Classroom Building - 203
  *
  * @date Due October 16, 2020
  *
  * @section program_section Program Information
  *
  * @details
  * This program is used in input, manipulate, and then output images.
  *
  * Images can be input and output in either ASCII or Binary. Valid manipulation 
  * options include negating, brightening/darkening, sharpening, smoothing, 
  * converting to grayscale, contrasting, and scaling.
  * 
  * The '.ppm' image format consists of a header followed by the image data. 
  * The header has a magic number, which determines what format (ASCII/Binary) 
  * the data is stored in, comments that do not affect the image, the rows and 
  * columns in the image, and the max pixel value, which in our case is 255. 
  * Image data is formatted as the red, green, and then blue color value, 
  * repeating for each column in each row.
  *
  * @section compile_section Compiling and Usage
  *
  * @par Compiling Instructions:
  *      none - a straight compile and link with no external libraries.
  *
  * @par Usage:
    @verbatim
    c:\> prog1.exe [option] -o[ab] basename image.ppm
             [option] - option to manipulate input image, -[n, b #, p, s, g, c, k #]
             -o[ab] - output in ASCII [a] or Binary [b]
             basename - name/location of output file with no extension
             image.ppm - name/location of input file with .ppm extension
    @endverbatim
  *
  * @par Options:
    @verbatim
    -n    - Negates the image (ex: "prog1.exe -n -oa output input.ppm")
    -b #  - Brightens the image by the number supplied (ex: "prog1.exe -b 40 -ob output input.ppm", brightens the image by 40)
    -p    - Sharpens the image (ex: "prog1.exe -p -ob output input.ppm")
    -s    - Smooths the image (ex: "prog1.exe -s -oa output input.ppm")
    -g    - Converts the image to grayscale (ex: "prog1.exe -g -oa output input.ppm")
    -c    - Converts to grayscale, then contrast the image (ex: "prog1.exe -c -ob output input.ppm")
    -k #  - Scale the image (ex: "prog1.exe -k 200 -oa output input.ppm", scales the image by 200%, valid scale input: [50, 200])
    -e    - Detects edges from change in intensity
    @endverbatim
  * @section todo_bugs_modification_section Todo, Bugs, and Modifications
  * 
  * @bug Edge Detection hysteresis appears to timeout
  *
  *****************************************************************************/

#include "netPBM.h"

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Main function of program
 *
 * @param[in] argc - number of arguments supplied
 * @param[in] argv - array of arguments supplied as cstring
 *
 * @returns returns the exit code
 *
 *****************************************************************************/
int main(int argc, char** argv)
{
    int briNum = 0, scaleNum = 100, rows, cols,
        maxPixelVal = 0;
    string inputImage, outputName,
        outputMagicNumber, magicNumber;
    vector<string> comments;

    imageOption option = BRIGHTEN;
    outputMode mode;

    image img;

    ifstream fin;
    ofstream fout;

    // invalid argument amount
    if (argc < 4 || argc > 6)
    {
        cout << "Usage: prog1.exe [option] -o[ab] basename image.ppm" << endl;
        exit(0);
    }

    // options selected
    if (argc > 4)
    {
        if (argc == 5)
        {
            if (strcmp(argv[1], "-n") == 0)
            {
                option = NEGATE;
            }
            else if (strcmp(argv[1], "-p") == 0)
            {
                option = SHARPEN;
            }
            else if (strcmp(argv[1], "-s") == 0)
            {
                option = SMOOTH;
            }
            else if (strcmp(argv[1], "-g") == 0)
            {
                option = GRAYSCALE;
            }
            else if (strcmp(argv[1], "-c") == 0)
            {
                option = CONTRAST;
            }
            else if (strcmp(argv[1], "-e") == 0)
            {
                option = EDGE;
            }
            else {
                cout << "Usage: prog1.exe [option] -o[ab] basename image.ppm" << endl;
                exit(0);
            }
        }
        else if (argc == 6)
        {
            if (strcmp(argv[1], "-b") == 0)
            {
                option = BRIGHTEN;
                briNum = atoi(argv[2]);
            }
            else if (strcmp(argv[1], "-k") == 0)
            {
                option = SCALE;
                scaleNum = atoi(argv[2]);
            }
            else {
                cout << "Usage: prog1.exe [option] -o[ab] basename image.ppm" << endl;
                exit(0);
            }
        }
    }

    if (strcmp(argv[argc - 3], "-oa") == 0)
    {
        mode = ASCII;
    }
    else if (strcmp(argv[argc - 3], "-ob") == 0) {
        mode = BINARY;
    }
    else {
        cout << "Invalid Output: -oa for ASCII, -ob for Binary" << endl;
        exit(0);
    }
    outputName = argv[argc - 2];
    inputImage = argv[argc - 1];

    // open input image
    openFileIn(fin, inputImage);

    // read in header
    readHeader(fin, magicNumber, comments, rows, cols, maxPixelVal);

    // dynamically allocate 3 2d arrays
    img.cols = cols;
    img.rows = rows;
    img.redgray = alloc2D(img.rows, img.cols);
    img.blue = alloc2D(img.rows, img.cols);
    img.green = alloc2D(img.rows, img.cols);

    // read in image data
    if (magicNumber.compare(P3) == 0)
    {
        readASCII(fin, img);
    }
    else 
    {
        readBIN(fin, img);
    }

    // apply options
    switch (option)
    {
    case(NEGATE):
        imageNegate(img);
        break;
    case(BRIGHTEN):
        imageBrighten(img, briNum);
        break;
    case(SHARPEN):
        imageSharpen(img);
        break;
    case(SMOOTH):
        imageSmooth(img);
        break;
    case(GRAYSCALE):
        imageGrayscale(img);
        break;
    case(CONTRAST):
        imageContrast(img);
        break;
    case(SCALE):
        imageScale(img, scaleNum);
        break;
    case(EDGE):
        imageEdgeDetection(img);
        break;
    }

    // determine output file magic number and filename
    if (option == GRAYSCALE || option == CONTRAST || option == EDGE)
    {
        if (mode == ASCII)
        {
            outputMagicNumber = P2;
        }
        else
        {
            outputMagicNumber = P5;
        }
        outputName.append(".pgm");
    }
    else {
        if (mode == ASCII)
        {
            outputMagicNumber = P3;
        }
        else
        {
            outputMagicNumber = P6;
        }
        outputName.append(".ppm");
    }

    // open output file
    openFileOut(fout, outputName);

    // write image data
    writeHeader(fout, outputMagicNumber, comments, img.rows, img.cols, maxPixelVal);
    if (mode == ASCII)
    {
        writeASCII(fout, img);
    }
    else {
        writeBIN(fout, img);
    }

    // clean up/free memory
    free2D(img.redgray, img.rows);
    free2D(img.blue, img.rows);
    free2D(img.green, img.rows);
    closeFileIn(fin);
    closeFileOut(fout);
}