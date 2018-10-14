#ifndef DEBUGNERRORS_H_INCLUDED
#define DEBUGNERRORS_H_INCLUDED

/**
	This file contains Macros and others about debuging and errors...

	Also contains constants n' stuff for testing purposes

	Compile with the macro RELEASE_COMPILE defined if you don't want the test
	macros to have any effect
*/

#include "config.h"
#include <exception>

#ifdef _NO_TEST_

# define E(x) ;

# define EINF ;

# define ES(x) ;

#else

# include <iostream>

# define E(x) { EINF std::cerr << ": " << #x ": " << (x) << std::endl; }

# define EINF { std::cerr << __FILE__ ": " << "l" << __LINE__ << std::endl; }

# define ES(x) { std::cerr << std::endl << (x) << std::endl; }

#endif

#endif //DEBUGNERRORS_H_INCLUDED

