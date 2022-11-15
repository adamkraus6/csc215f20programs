/** **************************************************************************
 * @file
 * 
 * @brief The source code for structures, library includes and all 
 * function prototypes
 ****************************************************************************/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

using namespace std;
#ifndef __NETPBM__H__
#define __NETPBM__H__
/**
 * @brief A value of a colorband in an image
 */
typedef unsigned char pixel;

/**
 * @brief Command line supplied options to alter image
 */
enum imageOption{NEGATE, /**< Negate color values        */
            BRIGHTEN,    /**< Brighten color values      */
            SHARPEN,     /**< Sharpen image              */
            SMOOTH,      /**< Smooth image               */
            GRAYSCALE,   /**< Convert image to grayscale */
            CONTRAST,    /**< Increase image contrast    */
            SCALE,       /**< Scale image                */
            EDGE         /**< Detect edges               */
};

/**
 * @brief Command line supplied output mode
 */
enum outputMode{ASCII, /**< Output as ASCII  */
            BINARY     /**< Output as Binary */
};

/**
 * @brief Holds data about an image
 */
struct image
{
    int rows;        /**< Number of rows in the image */
    int cols;        /**< Number of columns in the image */
    pixel** redgray; /**< 2D array for red/gray color values */
    pixel** green;   /**< 2D array for green color values */
    pixel** blue;    /**< 2D array for blue color values */
};

/**
 * @brief Magic Number of P3
 */
const string P3 = "P3";
/**
 * @brief Magic Number of P6
 */
const string P6 = "P6";

void openFileIn(ifstream& file, string fileName);
void openFileOut(ofstream& file, string fileName);
void closeFileIn(ifstream& file);
void closeFileOut(ofstream& file);
void readHeader(ifstream& file, string& magicNum, vector<string>& comments, 
    int& rows, int& cols, int& maxVal);
void readASCII(ifstream& file, image& img);
void readBIN(ifstream& file, image& img);
void writeHeader(ofstream& file, string magicNum, vector<string>& comments, 
    int rows, int cols, int maxVal);
void writeASCII(ofstream& file, image& img);
void writeBIN(ofstream& file, image& img);
pixel** alloc2D(int rows, int cols);
void free2D(pixel**& ptr, int rows);
void copy2D(pixel**& ptr1, pixel**& ptr2, int rows, int cols);
bool** alloc2DBool(int rows, int cols);
void free2DBool(bool**& ptr, int rows);
#endif