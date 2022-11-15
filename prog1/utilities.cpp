/** **************************************************************************
 * @file
 * 
 * @brief The source code for miscellaneous helper functions
 ****************************************************************************/

#include "netPBM.h"

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Crops a number to be between 0 and 255 inclusive
 *
 * @param[in] num - number to be cropped
 *
 * @returns returns the cropped number
 *
 *****************************************************************************/
int cropNum(int num)
{
    if (num < 0) return 0;
    if (num > 255) return 255;
    return num;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Maps a number from one range to another
 *
 * @param[in] num - number to be mapped
 * @param[in] lower1 - lower end of the first range
 * @param[in] upper1 - upper end of the first range
 * @param[in] lower2 - lower end of the second range
 * @param[in] upper2 - upper end of the second range
 * 
 * @returns returns mapped number
 *
 *****************************************************************************/
int mapNum(int num, double lower1, double upper1, double lower2, double upper2)
{
    return (int)round(lower2 + (upper2 - lower2)
        * ((num - lower1) / (upper1 - lower1)));
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Rounds an angle to align with 4 main directions or diagonals.
 *
 * @param[in] angle - number to be rounded in [-90, 90]
 *
 * @returns returns rounded angle in positive degrees, [0, 360]
 *
 *****************************************************************************/
int roundAngle(double angle)
{
    if (inBetween(angle, 67.5, 90) || inBetween(angle, -90, -67.5))
    {
        return 90;
    }
    else if (inBetween(angle, 22.5, 67.5))
    {
        return 45;
    }
    else if (inBetween(angle, -22.5, 22.5))
    {
        return 0;
    }
    else if (inBetween(angle, -67.5, -22.5))
    {
        return 135;
    }
    else {
        return 0;
    }
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Determines if an angle is between two other angles
 *
 * @param[in] num - angle to check if in between
 * @param[in] lower - smaller angle
 * @param[in] upper - larger angle
 *
 * @returns returns true if num is in (lower, upper], false otherwise
 *
 *****************************************************************************/
bool inBetween(double num, double lower, double upper)
{
    return num <= upper && num > lower;
}