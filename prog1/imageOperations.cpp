/** **************************************************************************
 * @file
 * 
 * @brief The source code for any function that does image processing
 ****************************************************************************/

#include "netPBM.h"

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Negates image color values
 *
 * @param[in,out] img - image structure
 *
 *****************************************************************************/
void imageNegate(image& img)
{
    int i, j;

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            img.redgray[i][j] = 255 - img.redgray[i][j];
            img.green[i][j] = 255 - img.green[i][j];
            img.blue[i][j] = 255 - img.blue[i][j];
        }
    }
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Brighten image color values
 *
 * @param[in,out] img - image structure
 * @param[in] value - value to be added to color values
 *
 *****************************************************************************/
void imageBrighten(image& img, int value)
{
    int i, j;

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            img.redgray[i][j] = cropNum(img.redgray[i][j] + value);
            img.green[i][j] = cropNum(img.green[i][j] + value);
            img.blue[i][j] = cropNum(img.blue[i][j] + value);
        }
    }
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Sharpens image
 *
 * @param[in,out] img - image structure
 *
 *****************************************************************************/
void imageSharpen(image& img)
{
    int i, j, rows = img.rows, cols = img.cols;
    int b, d, f, h;

    pixel** newRed = alloc2D(rows, cols);
    pixel** newGreen = alloc2D(rows, cols);
    pixel** newBlue = alloc2D(rows, cols);

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            if (i == 0 || i == img.rows - 1 || j == 0 || j == img.cols - 1)
            {
                newRed[i][j] = 0;
                newGreen[i][j] = 0;
                newBlue[i][j] = 0;
            }
            else {
                getSurrSha(img.redgray, b, d, f, h, i, j);
                newRed[i][j] = cropNum(5 * img.redgray[i][j] - b - d - f - h);

                getSurrSha(img.green, b, d, f, h, i, j);
                newGreen[i][j] = cropNum(5 * img.green[i][j] - b - d - f - h);

                getSurrSha(img.blue, b, d, f, h, i, j);
                newBlue[i][j] = cropNum(5 * img.blue[i][j] - b - d - f - h);
            }
        }
    }

    copy2D(newRed, img.redgray, rows, cols);
    copy2D(newGreen, img.green, rows, cols);
    copy2D(newBlue, img.blue, rows, cols);
    
    free2D(newRed, rows);
    free2D(newGreen, rows);
    free2D(newBlue, rows);
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Gets the surrounding values of the location not including diagonally
 *
 * @param[in] colorband - the colorband to get values from
 * @param[out] b - value above current position
 * @param[out] d - value left of current position
 * @param[out] f - value right of current position
 * @param[out] h - value below current postion
 * @param[out] iPos - current row position
 * @param[out] jPos - current column position
 *
 *****************************************************************************/
void getSurrSha(pixel**& colorband, int& b, int& d, int& f, int& h, int iPos, int jPos)
{
    b = colorband[iPos - 1][jPos];
    d = colorband[iPos][jPos - 1];
    f = colorband[iPos][jPos + 1];
    h = colorband[iPos + 1][jPos];
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Smooths image by averaging values of 3x3 around a pixel
 *
 * @param[in,out] img - image structure
 *
 *****************************************************************************/
void imageSmooth(image& img)
{
    int iPos, jPos, rows = img.rows, cols = img.cols;
    int a, b, c, d, f, g, h, i;
    double average;

    pixel** newRed = alloc2D(rows, cols);
    pixel** newGreen = alloc2D(rows, cols);
    pixel** newBlue = alloc2D(rows, cols);

    for (iPos = 0; iPos < img.rows; iPos++)
    {
        for (jPos = 0; jPos < img.cols; jPos++)
        {
            if (iPos == 0 || iPos == img.rows - 1 
                || jPos == 0 || jPos == img.cols - 1)
            {
                newRed[iPos][jPos] = 0;
                newGreen[iPos][jPos] = 0;
                newBlue[iPos][jPos] = 0;
            }
            else {
                getSurrSmo(img.redgray, a, b, c, d, f, g, h, i, iPos, jPos);
                average = ((unsigned long)a + b + c + d + img.redgray[iPos][jPos]
                    + f + g + h + i) / 9.0;
                newRed[iPos][jPos] = cropNum((int)average);

                getSurrSmo(img.green, a, b, c, d, f, g, h, i, iPos, jPos);
                average = ((unsigned long)a + b + c + d + img.green[iPos][jPos]
                    + f + g + h + i) / 9.0;
                newGreen[iPos][jPos] = cropNum((int)average);

                getSurrSmo(img.blue, a, b, c, d, f, g, h, i, iPos, jPos);
                average = ((unsigned long)a + b + c + d + img.blue[iPos][jPos]
                    + f + g + h + i) / 9.0;
                newBlue[iPos][jPos] = cropNum((int)average);
            }
        }
    }

    copy2D(newRed, img.redgray, rows, cols);
    copy2D(newGreen, img.green, rows, cols);
    copy2D(newBlue, img.blue, rows, cols);

    free2D(newRed, rows);
    free2D(newGreen, rows);
    free2D(newBlue, rows);
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Gets the surrounding values of the location including diagonally
 *
 * @param[in] colorband - the colorband to get values from
 * @param[out] a - value above/left of current postion
 * @param[out] b - value above current position
 * @param[out] c - value above/right current postion
 * @param[out] d - value left of current position
 * @param[out] f - value right of current position
 * @param[out] g - value below/left of current position
 * @param[out] h - value below current postion
 * @param[out] i - value below/right of current position
 * @param[out] iPos - current row position
 * @param[out] jPos - current column position
 *
 *****************************************************************************/
void getSurrSmo(pixel**& colorband, int& a, int& b, int& c, int& d, int& f, int& g, int& h, int& i, int iPos, int jPos)
{
    a = colorband[iPos - 1][jPos - 1];
    b = colorband[iPos - 1][jPos];
    c = colorband[iPos - 1][jPos + 1];
    d = colorband[iPos][jPos - 1];
    f = colorband[iPos][jPos + 1];
    g = colorband[iPos + 1][jPos - 1];
    h = colorband[iPos + 1][jPos];
    i = colorband[iPos + 1][jPos + 1];
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Convert image to grayscale
 *
 * @param[in,out] img - image structure
 *
 *****************************************************************************/
void imageGrayscale(image& img)
{
    int i, j;

    pixel** grayscale = alloc2D(img.rows, img.cols);

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            grayscale[i][j] = cropNum((int)round(0.3 * img.redgray[i][j]
                + 0.6 * img.green[i][j] + 0.1 * img.blue[i][j]));
        }
    }

    copy2D(grayscale, img.redgray, img.rows, img.cols);

    free2D(grayscale, img.rows);
    img.blue = nullptr;
    img.green = nullptr;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Convert image to grayscale, then contrasts it
 *
 * @param[in,out] img - image structure
 *
 *****************************************************************************/
void imageContrast(image& img)
{
    imageGrayscale(img);
    int i, j;
    int min = img.redgray[0][0], max = img.redgray[0][0];
    double scale;

    // find min/max value
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            if (img.redgray[i][j] < min) min = img.redgray[i][j];
            if (img.redgray[i][j] > max) max = img.redgray[i][j];
        }
    }

    scale = 255.0 / (max - min);

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            img.redgray[i][j] = cropNum((int)round(scale * 
                (img.redgray[i][j] - min)));
        }
    }

    //cout << scale << ',' << max << ',' << min << endl;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Scales an image up or down in size
 *
 * @param[in,out] img - image structure
 * @param[in] scale - percent to scale by, valid scale: [50, 200]
 *
 *****************************************************************************/
void imageScale(image& img, int scale)
{
    if (scale < 50 || scale > 200 || scale == 100) return;
    int i, j;
    double percent = scale / 100.0;
    int newRows = int(img.rows * percent);
    int newCols = int(img.cols * percent);
    int mappedRow, mappedCol;

    pixel** newRed = alloc2D(newRows, newCols);
    pixel** newGreen = alloc2D(newRows, newCols);
    pixel** newBlue = alloc2D(newRows, newCols);

    for (i = 0; i < newRows - 1; i++)
    {
        mappedRow = mapNum(i, 0.0, (double)newRows, 0.0, (double)img.rows);
        for (j = 0; j < newCols - 1; j++)
        {
            mappedCol = mapNum(j, 0.0, (double)newCols, 0.0, (double)img.cols);

            newRed[i][j] = img.redgray[mappedRow][mappedCol];
            newGreen[i][j] = img.green[mappedRow][mappedCol];
            newBlue[i][j] = img.blue[mappedRow][mappedCol];
        }
    }

    // free existing colorbands
    free2D(img.redgray, img.rows);
    free2D(img.green, img.rows);
    free2D(img.blue, img.rows);

    // reallocate and copy in new colorbands
    img.redgray = alloc2D(newRows, newCols);
    copy2D(newRed, img.redgray, newRows, newCols);
    img.green = alloc2D(newRows, newCols);
    copy2D(newGreen, img.green, newRows, newCols);
    img.blue = alloc2D(newRows, newCols);
    copy2D(newBlue, img.blue, newRows, newCols);

    //set new rows/columns
    img.rows = newRows;
    img.cols = newCols;

    // free temporary colorbands
    free2D(newRed, newRows);
    free2D(newGreen, newRows);
    free2D(newBlue, newRows);

    imageSmooth(img);
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Detects edges in the image. For more in-depth information, visit 
 * https://en.wikipedia.org/wiki/Sobel_operator and 
 * https://en.wikipedia.org/wiki/Canny_edge_detector.
 *
 * @param[in,out] img - image structure
 *
 *****************************************************************************/
void imageEdgeDetection(image& img)
{
    int i, j, rows = img.rows, cols = img.cols,
        Gx, Gy, lowerThreshold, upperThreshold;
    pixel** newGray = nullptr;
    int** gradientAngle = nullptr;
    //bool complete = false;
    //int a, b, c, d, f, g, h, iNum;

    // apply filter to remove noise
    imageSmooth(img);

    // find the intensity gradients
    imageGrayscale(img);
    newGray = alloc2D(rows, cols);
    gradientAngle = alloc2DInt(rows, cols);
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
            {
                // ignore border pixel
                newGray[i][j] = 0;
            }
            else {
                // compute vertical/horizontal intensity changes
                Gx = sobelX(img, i, j);
                Gy = sobelY(img, i, j);

                // set pixel to magnitude of changes
                newGray[i][j] = (int)round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                // compute gradient angle
                if (Gx != 0)
                {
                    gradientAngle[i][j] = roundAngle(atan(Gy / Gx) * 180 / PI);
                }
                else {
                    gradientAngle[i][j] = 90;
                }
            }
        }
    }

    copy2D(newGray, img.redgray, rows, cols);

    // apply non-maximum suppression
    for (i = 1; i < rows - 1; i++)
    {
        for (j = 1; j < cols - 1; j++)
        {
            if (gradientAngle[i][j] != -1)
            {
                switch (gradientAngle[i][j])
                {
                case(0):
                    if (img.redgray[i][j] <= img.redgray[i][j - 1] || img.redgray[i][j] <= img.redgray[i][j + 1])
                    {
                        newGray[i][j] = 0;
                    }
                    break;
                case(45):
                    if (img.redgray[i][j] <= img.redgray[i + 1][j - 1] || img.redgray[i][j] <= img.redgray[i - 1][j + 1])
                    {
                        newGray[i][j] = 0;
                    }
                    break;
                case(90):
                    if (img.redgray[i][j] <= img.redgray[i + 1][j] || img.redgray[i][j] <= img.redgray[i - 1][j])
                    {
                        newGray[i][j] = 0;
                    }
                    break;
                case(135):
                    if (img.redgray[i][j] <= img.redgray[i + 1][j + 1] || img.redgray[i][j] <= img.redgray[i - 1][j - 1])
                    {
                        newGray[i][j] = 0;
                    }
                    break;
                }
            }
        }
    }

    copy2D(newGray, img.redgray, rows, cols);

    // apply double threshold
    lowerThreshold = 30;
    upperThreshold = 125;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (img.redgray[i][j] < lowerThreshold)
            {
                newGray[i][j] = 0;
            }
            else if (img.redgray[i][j] > upperThreshold)
            {
                newGray[i][j] = 255;
            }
            else if (img.redgray[i][j] >= lowerThreshold && img.redgray[i][j] <= upperThreshold)
            {
                newGray[i][j] = 127;
            }
        }
    }

    // track edge by hysteresis - suppress edges not connected to strong edges
    /*while (!complete)
    {
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < cols; j++)
            {
                if (img.redgray[i][j] == 127)
                {
                    getSurrSmo(img.redgray, a, b, c, d, f, g, h, iNum, i, j);
                    if (a == 255 || b == 255 || c == 255 || d == 255 ||
                        f == 255 || g == 255 || h == 255 || iNum == 255)
                    {
                        img.redgray[i][j] = 255;
                    }
                }
            }
        }

        complete = true;
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < cols; j++)
            {
                if (img.redgray[i][j] == 127)
                {
                    complete = false;
                }
            }
        }
    }*/

    copy2D(newGray, img.redgray, rows, cols);
    free2D(newGray, rows);
    free2DInt(gradientAngle, rows);
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Calculates change in intensity in the x-direction
 *
 * @param[in,out] img - image structure
 * @param[in] i - current row position
 * @param[in] j - current column position
 * 
 * @returns change in intensity in the x-direction 
 *
 *****************************************************************************/
int sobelX(image& img, int i, int j)
{
    int formulation = 0;

    formulation += (img.redgray[i - 1][j - 1] + 2 * img.redgray[i][j - 1]
        + img.redgray[i + 1][j - 1]);
    formulation -= (img.redgray[i - 1][j + 1] + 2 * img.redgray[i][j + 1]
        + img.redgray[i + 1][j + 1]);

    return cropNum(formulation);
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Calculates change in intensity in the y-direction
 *
 * @param[in,out] img - image structure
 * @param[in] i - current row position
 * @param[in] j - current column position
 * 
 * @returns change in intensity in the y-direction
 *
 *****************************************************************************/
int sobelY(image& img, int i, int j)
{
    int formulation = 0;

    formulation += (img.redgray[i - 1][j - 1] + 2 * img.redgray[i - 1][j]
        + img.redgray[i - 1][j + 1]);
    formulation -= (img.redgray[i + 1][j - 1] + 2 * img.redgray[i + 1][j]
        + img.redgray[i + 1][j + 1]);

    return cropNum(formulation);
}