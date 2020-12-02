/** **************************************************************************
 * @file
 * 
 * @brief Main file
 ****************************************************************************/
/** **************************************************************************
 * @mainpage Program 3
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
 * @date Due November 24, 2020
 *
 * @section program_section Program Information
 *
 * @details
 * This program recursively changes pixels to fill a region of the same 
 * initial color.
 * 
 * It does this by going out in each direction from a pixel and comparing the 
 * original color of the pixel to the color of the origin pixel. If it matches
 * and has not been changed, then it changes the pixel to a new color that is 
 * input at the command line.
 * 
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      Go to Project -> Properties -> Linker -> System. Set "Stack Reserve 
 * Size" and "Stack Commit Size" to 4 billion with no commas (nine zeros).
 *
 * @par Usage:
    @verbatim
    c:\> prog3.exe image row col red green blue
             image - filename of input image
             row   - row to start image fill
             col   - column to start image fill
             red   - red value of new image fill color
             green - green value of new image fill color
             blue  - blue value of new image fill color
    @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 *****************************************************************************/

#include "netPBM.h"

void imageFill(image& img, bool** used, int row, int col, int origRed,
    int origGreen, int origBlue, int fillRed, int fillGreen, int fillBlue);
void initBool(bool** ptr, int rows, int cols);

/** ***************************************************************************
 * @author Adam Kraus
 * 
 * @par Description: 
 * Main function
 * 
 * @param[in] argc - number of command line arguments supplied.
 * @param[in] argv - 2D char array of command line arguments.
 * 
 * @returns exit code
 * 
 *****************************************************************************/
int main(int argc, char** argv)
{
    ifstream fin;
    ofstream fout;
    string imageName, magicNum;
    vector<string> comments;
    image img;
    int row, col, rows, cols, red, green, blue, maxVal;
    bool** used;

    // check command line argument count
    if (argc != 7)
    {
        cout << "Usage: prog3.exe image row col red green blue" << endl;
        exit(0);
    }

    // set values from command line arguments
    imageName = argv[1];
    row = atoi(argv[2]);
    col = atoi(argv[3]);
    red = atoi(argv[4]);
    green = atoi(argv[5]);
    blue = atoi(argv[6]);

    // open input image
    openFileIn(fin, imageName);

    // read header
    readHeader(fin, magicNum, comments, rows, cols, maxVal);

    // create image structure
    img.cols = cols;
    img.rows = rows;
    img.redgray = alloc2D(rows, cols);
    img.blue = alloc2D(rows, cols);
    img.green = alloc2D(rows, cols);

    // read in image data
    if (magicNum == P3)
    {
        readASCII(fin, img);
    }
    else {
        readBIN(fin, img);
    }

    // close and reopen file
    closeFileIn(fin);
    openFileOut(fout, imageName);

    // create boolean array
    used = alloc2DBool(rows, cols);
    initBool(used, rows, cols);

    // recursive stuff here
    imageFill(img, used, row, col, img.redgray[row][col], img.green[row][col], 
        img.blue[row][col], red, green, blue);

    // write image data
    writeHeader(fout, magicNum, comments, rows, cols, maxVal);
    if (magicNum == P3)
    {
        writeASCII(fout, img);
    }
    else {
        writeBIN(fout, img);
    }

    // free memory and close files
    free2D(img.redgray, rows);
    free2D(img.blue, rows);
    free2D(img.green, rows);
    free2DBool(used, rows);
    closeFileOut(fout);
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Recursively changes pixel values to fill a region.
 *
 * @param[in,out] img - image structure
 * @param[in] used - 2d array of booleans to determine if a pixel has been
 * changed
 * @param[in] row - row of pixel to change
 * @param[in] col - column of pixel to change
 * @param[in] origRed - red color value of origin pixel before it was changed
 * @param[in] origGreen - green color value of origin pixel before it was
 * changed
 * @param[in] origBlue - blue color value of origin pixel before it was changed
 * @param[in] fillRed - red color value to change pixel to
 * @param[in] fillGreen - green color value to change pixel to
 * @param[in] fillBlue - blue color value to change pixel to
 *
 *****************************************************************************/
void imageFill(image& img, bool** used, int row, int col, int origRed, 
    int origGreen, int origBlue, int fillRed, int fillGreen, int fillBlue)
{
    // check if in image boundary, if pixel has been changed, and if pixel
    // matches origin pixel color
    if (row < 0 || row >= img.rows || col < 0 || col >= img.cols ||
        used[row][col] || img.redgray[row][col] != origRed || 
        img.green[row][col] != origGreen || img.blue[row][col] != origBlue)
    {
        return;
    }

    // change pixel color
    img.redgray[row][col] = fillRed;
    img.green[row][col] = fillGreen;
    img.blue[row][col] = fillBlue;

    // mark pixel as changed
    used[row][col] = true;

    // recursively change pixels in each direction
    imageFill(img, used, row - 1, col, origRed, origGreen, origBlue,
        fillRed, fillGreen, fillBlue);
    imageFill(img, used, row + 1, col, origRed, origGreen, origBlue,
        fillRed, fillGreen, fillBlue);
    imageFill(img, used, row, col - 1, origRed, origGreen, origBlue,
        fillRed, fillGreen, fillBlue);
    imageFill(img, used, row, col + 1, origRed, origGreen, origBlue,
        fillRed, fillGreen, fillBlue);
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Initializes all values in a 2D boolean array to false
 *
 * @param[in,out] ptr - pointer to the 2D boolean array
 * @param[in] rows - rows in the 2D array
 * @param[in] cols - columns in the 2D array
 *
 *****************************************************************************/
void initBool(bool** ptr, int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            ptr[i][j] = false;
        }
    }
}