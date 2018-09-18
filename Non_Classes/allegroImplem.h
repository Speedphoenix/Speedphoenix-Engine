#ifndef ALLEGROIMPLEM_H_INCLUDED
#define ALLEGROIMPLEM_H_INCLUDED

/**
    This file contains
    most Allegro library related operations
 */


#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "config.h"


const int defaultDispFlags = ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE;


extern ALLEGRO_DISPLAY *currentDisplay;


///initializes and installs allegro related add-ons n' others
///also creates the display
void initAlleg(int flags = 0, int w = 800, int h = 600, const char* window_name = "");

///closes allegro and destroys necessary stuff
void closeAlleg();

//if an event queue is passed as a param, it will register the new display if one is created
///will properly and cleanly toggle fullscreen mode on the current display
void toggleFullscreen(ALLEGRO_EVENT_QUEUE* displayEvents = nullptr);

#endif //ALLEGROIMPLEM_H_INCLUDED

