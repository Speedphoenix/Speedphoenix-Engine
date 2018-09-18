#ifndef DEBUGNERRORS_H_INCLUDED
#define DEBUGNERRORS_H_INCLUDED

/**
    This file contains
    Macros and others about debuging and errors...

    Also contains constants n' stuff for testing purposes
*/

#include "config.h"
#include <exception>

#define TEST_SPRITESHEET RES_DIR "monsterv2.png"
#define TEST_SHEETNAME "monsterv2"


#include <iostream>

#define E(x) {std::cerr << std::endl << #x ": " << (x) << std::endl;}
#define ES(x) {std::cerr << std::endl << (x) << std::endl;}


#endif //DEBUGNERRORS_H_INCLUDED

