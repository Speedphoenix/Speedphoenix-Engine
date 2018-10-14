#ifndef BASIC_OPS_H_INCLUDED
#define BASIC_OPS_H_INCLUDED


/********************************************************************
							BASIC OPERATORS
********************************************************************/

#include <math.h>

const double negligibleAngle = 0.001;

template<typename T>
inline T ABS(T a)
{
	return ((a < 0) ? -1 * a : a);
}

template<typename T>
inline T MIN(T a, T b)
{
	return ((a < b) ? a : b);
}

template<typename T>
inline T MAX(T a, T b)
{ 
	return ((a > b) ? a : b);
}

inline bool XOR(bool a, bool b)
{
	return (a ? !b : b);
}

inline bool sameAngle(double a, double b)
{
	return (ABS(a - b) < negligibleAngle);
}

inline double mod2PI(double orientation)
{
	if (orientation >= (2 * M_PI))
		return (orientation - (2 * M_PI) * (((int)(orientation * M_1_PI)) / 2));
	else if (orientation < 0)
		return (orientation - (2 * M_PI) * (-1 + (((int)(orientation * M_1_PI)) / 2)));
	else
		return (orientation);
}


#endif // BASIC_OPS_H_INCLUDED

