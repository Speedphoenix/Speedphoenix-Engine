#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

/**
	This file contains
	constants and others stuff to configure the game
*/

//from allegro5
#include "allegro5/keycodes.h"
#include "allegro5/events.h"

/********************************************************************
						CONFIGURABLE CONSTANTS
********************************************************************/

const double negligibleDistance = 0.25; //in pixels


/********************************************************************
								ALLEG
********************************************************************/

const int defaultDispWidth = 1200;
const int defaultDispHeight = 800;


/********************************************************************
								CAMERA
********************************************************************/

const double maxCameraZoom = 2.0; //for the moment
const double minCameraZoom = 0.5;


/********************************************************************
								IMAGES
********************************************************************/

#ifndef RES_DIR
//might want to put this one as a game-specific config
# define RES_DIR "res/"
#endif // RES_DIR

#endif // CONFIG_H_INCLUDED

