#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

/**
    This file contains
    constants and others stuff to configure the game

    Things and constants for testing purposes are in debugNerrors.h
*/




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
                                MAP
********************************************************************/

const double maxCameraZoom = 2.0; //for the moment
const double minCameraZoom = 0.5;

///the side of a (square) tile
const int tileSide = 75;

///converts coordinates in number of tiles
inline int tileCoord(int pixels)
{
    return ((int) (pixels / tileSide));
}


/********************************************************************
                                IMAGES
********************************************************************/

#define RES_DIR "res/"



/********************************************************************
                                UNITS
********************************************************************/

const double defaultUnitSpeed = 50;

const double defaultIdleLapse = 0.3; //seconds
const double defaultActiveLapse = 0.1; //seconds


#endif // CONFIG_H_INCLUDED

