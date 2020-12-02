/** **************************************************************************
 * @file
 * 
 * @brief The source code for any function that does any dynamic memory 
 * allocation or freeing up the allocated memory
 ****************************************************************************/

#include "netPBM.h"

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Dynamically allocates a 2D pixel array
 *
 * @param[in] rows - number of rows in the image
 * @param[in] cols - number of columns in the image
 *
 * @returns returns the pointer to the 2D array
 *
 *****************************************************************************/
pixel** alloc2D(int rows, int cols)
{
    pixel** pptr = nullptr;
    int i;

    pptr = new (nothrow) pixel * [rows];
    if (pptr == nullptr)
    {
        cout << "Not enough memory to run program." << endl;
        free2D(pptr, rows);
        exit(1);
    }

    for (i = 0; i < rows; i++)
    {
        pptr[i] = new (nothrow) pixel[cols];
        if (pptr[i] == nullptr)
        {
            cout << "Not enough memory to run program" << endl;
            free2D(pptr, rows);
            exit(1);
        }
    }

    return pptr;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Frees memory from a dynamically allocated 2D pixel array
 *
 * @param[in] ptr - pointer to the 2D array
 * @param[in] rows - number rows in the image
 *
 *****************************************************************************/
void free2D(pixel**& ptr, int rows)
{
    int i;

    if (ptr == nullptr) return;

    for (i = 0; i < rows; i++)
    {
        delete[] ptr[i];
    }

    delete[] ptr;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Copies the values from one array into another
 *
 * @param[in] src - pointer to the source 2D array
 * @param[out] dest - pointer to the destination 2D array
 * @param[in] rows - rows in the array
 * @param[in] cols - columns in the array
 *
 *****************************************************************************/
void copy2D(pixel**& src, pixel**& dest, int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Dynamically allocates a 2D boolean array
 *
 * @param[in] rows - number of rows in the array
 * @param[in] cols - number of columns in the array
 *
 * @returns returns the pointer to the 2D array
 *
 *****************************************************************************/
bool** alloc2DBool(int rows, int cols)
{
    bool** iptr = nullptr;
    int i;

    iptr = new (nothrow) bool* [rows];
    if (iptr == nullptr)
    {
        cout << "Not enough memory to run program." << endl;
        free2DBool(iptr, rows);
        exit(1);
    }

    for (i = 0; i < rows; i++)
    {
        iptr[i] = new (nothrow) bool[cols];
        if (iptr[i] == nullptr)
        {
            cout << "Not enough memory to run program" << endl;
            free2DBool(iptr, rows);
            exit(1);
        }
    }

    return iptr;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Frees memory from a dynamically allocated 2D boolean array
 *
 * @param[in] ptr - pointer to the 2D array
 * @param[in] rows - number rows in the array
 *
 *****************************************************************************/
void free2DBool(bool**& ptr, int rows)
{
    int i;

    if (ptr == nullptr) return;

    for (i = 0; i < rows; i++)
    {
        delete[] ptr[i];
    }

    delete[] ptr;
}