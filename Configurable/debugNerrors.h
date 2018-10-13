#ifndef DEBUGNERRORS_H_INCLUDED
#define DEBUGNERRORS_H_INCLUDED

/**
	This file contains
	Macros and others about debuging and errors...

	Also contains constants n' stuff for testing purposes
*/

#include "config.h"
#include <exception>

#include <iostream>

#define E(x) { EINF std::cerr << ": " << #x ": " << (x) << std::endl; }

#define EINF { std::cerr << __FILE__ ": " << "l" << __LINE__ << std::endl; }

#define ES(x) { std::cerr << std::endl << (x) << std::endl; }


#endif //DEBUGNERRORS_H_INCLUDED

