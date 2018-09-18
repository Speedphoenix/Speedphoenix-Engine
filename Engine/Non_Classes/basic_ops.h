#ifndef BASIC_OPS_H_INCLUDED
#define BASIC_OPS_H_INCLUDED


/********************************************************************
                            BASIC OPERATORS
********************************************************************/

#include <math.h>

#define XOR(a, b) ( (a) ? !(b) : (b) )
#define ABS(a) ( ((a) < 0) ? -1 * (a) : (a) )
#define MIN(a, b) ( ((a) < (b)) ? (a) : (b) )
#define MAX(a, b) ( ((a) > (b)) ? (a) : (b) )

inline double mod2PI(double orientation)
{
    if (orientation > (2 * M_PI))
        return orientation - (2 * M_PI) * ((int)(orientation * M_PI_2));
    else if (orientation < 0)
        return orientation - (2 * M_PI) * (-1 + (int)(orientation * M_PI_2));
    else
        return orientation;
}


#endif // BASIC_OPS_H_INCLUDED

