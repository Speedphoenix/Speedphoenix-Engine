#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED

/**
    This file contains
    Color "constants" to be used anywhere
    Make sure to call initColors() after initializing the liballeg
*/

#include <allegro5/allegro_color.h>

namespace col
{

extern ALLEGRO_COLOR white;     //!< #FFFFFF
extern ALLEGRO_COLOR black;     //!< #000000
extern ALLEGRO_COLOR red;       //!< #FF0000
extern ALLEGRO_COLOR green;     //!< #00FF00
extern ALLEGRO_COLOR blue;      //!< #0000FF
extern ALLEGRO_COLOR mag;       //!< #FF00FF


///colors used for the original Stiek Bellum. Most were used in the minimap
namespace olds
{
    extern ALLEGRO_COLOR UI_FOND;     //!< #01579B
    extern ALLEGRO_COLOR UI_ACC;      //!< #4FC3F7
    extern ALLEGRO_COLOR SAND;        //!< #C28450
    extern ALLEGRO_COLOR BRIDGE;      //!< #7A3D00
    extern ALLEGRO_COLOR GRASS;       //!< #6E8233
    extern ALLEGRO_COLOR WATER;       //!< #308CBB
    extern ALLEGRO_COLOR MOUNTAIN;    //!< #535353
    extern ALLEGRO_COLOR ROCK;        //!< #808080
    extern ALLEGRO_COLOR TREEL;       //!< #4E9165
    extern ALLEGRO_COLOR TREEP;       //!< #3A633A
    extern ALLEGRO_COLOR PEASANT;     //!< #225DFF

    void initOlds();
}

//gives a value to all the colors.
//this function has to be called after the main initialization of alleg
void initColors();

}


#endif // COLORS_H_INCLUDED


