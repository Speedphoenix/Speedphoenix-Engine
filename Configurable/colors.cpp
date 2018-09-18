#include "colors.h"

namespace col
{

ALLEGRO_COLOR white;
ALLEGRO_COLOR black;
ALLEGRO_COLOR red;
ALLEGRO_COLOR green;
ALLEGRO_COLOR blue;
ALLEGRO_COLOR mag;


///colors used for the original Stiek Bellum. Most were used in the minimap
namespace olds
{
    ALLEGRO_COLOR UI_FOND;
    ALLEGRO_COLOR UI_ACC;
    ALLEGRO_COLOR SAND;
    ALLEGRO_COLOR BRIDGE;
    ALLEGRO_COLOR GRASS;
    ALLEGRO_COLOR WATER;
    ALLEGRO_COLOR MOUNTAIN;
    ALLEGRO_COLOR ROCK;
    ALLEGRO_COLOR TREEL;
    ALLEGRO_COLOR TREEP;
    ALLEGRO_COLOR PEASANT;

    void initOlds()
    {
        UI_FOND     = al_map_rgb(1,87,155);     //!< #01579B
        UI_ACC      = al_map_rgb(79,195,247);   //!< #4FC3F7
        SAND        = al_map_rgb(194,132,80);   //!< #C28450
        BRIDGE      = al_map_rgb(122,61,0);     //!< #7A3D00
        GRASS       = al_map_rgb(110,130,51);   //!< #6E8233
        WATER       = al_map_rgb(48,140,187);   //!< #308CBB
        MOUNTAIN    = al_map_rgb(83,83,83);     //!< #535353
        ROCK        = al_map_rgb(128,128,128);  //!< #808080
        TREEL       = al_map_rgb(78,145,101);   //!< #4E9165
        TREEP       = al_map_rgb(58,99,58);     //!< #3A633A
        PEASANT     = al_map_rgb(34,93,255);    //!< #225DFF
    }
}

//it is necessary to do this after the liballegro is initialized, otherwise al_map doesn't work
void initColors()
{
    white   = al_map_rgb(255,255,255);  //!< #FFFFFF
    black   = al_map_rgb(0,0,0);        //!< #000000
    red     = al_map_rgb(255,0,0);      //!< #FF0000
    green   = al_map_rgb(0,255,0);      //!< #00FF00
    blue    = al_map_rgb(0,0,255);      //!< #0000FF
    mag     = al_map_rgb(255,0,255);    //!< #FF00FF

    olds::initOlds();
}

}

