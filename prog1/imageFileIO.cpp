/** **************************************************************************
 * @file
 * 
 * @brief The source code for any function that does file io, 
 * opening or closing files
 ****************************************************************************/

#include "netPBM.h"

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Opens an ifstream for file input
 *
 * @param[in,out] file - reference to ifstream
 * @param[in] fileName - name of file to be opened
 *
 *****************************************************************************/
void openFileIn(ifstream& file, string fileName)
{
    file.open(fileName, ios::in | ios::binary);

    if (!file)
    {
        cout << "Unable to open input file: " << fileName << endl;
        exit(0);
    }
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Opens an ofstream for file output
 *
 * @param[in,out] file - reference to ofstream
 * @param[in] fileName - name of file to be opened
 *
 *****************************************************************************/
void openFileOut(ofstream& file, string fileName)
{
    file.open(fileName, ios::out | ios::trunc | ios::binary);

    if (!file)
    {
        cout << "Unable to open output file: " << fileName << endl;
        exit(0);
    }
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Closes an ifstream
 *
 * @param[in] file - reference to ifstream
 *
 *****************************************************************************/
void closeFileIn(ifstream& file)
{
    file.close();
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Closes an ofstream
 *
 * @param[in] file - reference to ofstream
 *
 *****************************************************************************/
void closeFileOut(ofstream& file)
{
    file.close();
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Reads in the header of the image, including magic number, comment(s), rows 
 * and columns, and max pixel value
 *
 * @param[in] file - reference to ifstream
 * @param[out] magicNum - magic number of image
 * @param[out] comments - array of comments
 * @param[out] rows - rows in the image
 * @param[out] cols - columns in the image
 * @param[out] maxVal - max pixel value
 *
 *****************************************************************************/
void readHeader(ifstream& file, string &magicNum, vector<string>& comments, int& rows, int& cols, int& maxVal)
{
    string comment;

    // read magic number
    getline(file, magicNum, '\n');

    // check magic number
    if (magicNum.compare(P6) != 0 && magicNum.compare(P3) != 0)
    {
        cout << "Invalid magic number: P3 or P6 for input" << endl;
        exit(0);
    }

    //check for comments
    while (file.peek() == '#')
    {
        getline(file, comment);
        comments.push_back(comment);
    }

    // read cols and rows
    file >> cols >> rows;

    // read max pixel value
    file >> maxVal >> ws;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Reads in ASCII image data
 *
 * @param[in] file - reference to ifstream
 * @param[out] img - image structure
 *
 *****************************************************************************/
void readASCII(ifstream& file, image& img)
{
    int i, j, value;

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            file >> value;
            img.redgray[i][j] = value;

            file >> value;
            img.green[i][j] = value;

            file >> value;
            img.blue[i][j] = value;
        }
    }
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Reads in Binary image data
 *
 * @param[in] file - reference to ifstream
 * @param[out] img - image structure
 *
 *****************************************************************************/
void readBIN(ifstream& file, image& img)
{
    int i, j;

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            file.read((char*) &img.redgray[i][j], sizeof(pixel));
            file.read((char*) &img.green[i][j], sizeof(pixel));
            file.read((char*) &img.blue[i][j], sizeof(pixel));
        }
    }
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Outputs the header of the image, including magic number, comment(s), rows 
 * and columns, and max pixel value
 *
 * @param[out] file - reference to ofstream
 * @param[in] magicNum - magic number of image
 * @param[in] comments - array of comments
 * @param[in] rows - rows in the image
 * @param[in] cols - columns in the image
 * @param[in] maxVal - max pixel value
 *
 *****************************************************************************/
void writeHeader(ofstream& file, string magicNum, vector<string>& comments, int rows, int cols, int maxVal)
{
    int i;

    file << magicNum << endl;
    for (i = 0; i < comments.size(); i++)
    {
        file << comments.at(i) << endl;
    }
    file << cols << " " << rows << endl;
    file << maxVal << endl;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Writes out image data in ASCII
 *
 * @param[in] file - reference to ofstream
 * @param[in] img - image structure
 *
 *****************************************************************************/
void writeASCII(ofstream& file, image& img)
{
    int i, j, value;

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            if (img.redgray != nullptr)
            {
                value = img.redgray[i][j];
                file << value << endl;
            }

            if (img.green != nullptr)
            {
                value = img.green[i][j];
                file << value << endl;
            }

            if (img.blue != nullptr)
            {
                value = img.blue[i][j];
                file << value << endl;
            }
        }
    }
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Writes out image data in Binary
 *
 * @param[in] file - reference to ofstream
 * @param[in] img - image structure
 *
 *****************************************************************************/
void writeBIN(ofstream& file, image& img)
{
    int i, j;

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            if (img.redgray != nullptr)
            {
                file.write((char*)&img.redgray[i][j], sizeof(pixel));
            }
            
            if (img.green != nullptr)
            {
                file.write((char*)&img.green[i][j], sizeof(pixel));
            }

            if (img.blue != nullptr)
            {
                file.write((char*)&img.blue[i][j], sizeof(pixel));
            }
        }
    }
}