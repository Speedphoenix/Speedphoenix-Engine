#include "allegroImplem.h"
#include "colors.h"
#include "debugNerrors.h"
#include "basic_ops.h"

ALLEGRO_DISPLAY *currentDisplay;

void initAlleg(int flags, int w, int h, const char* window_name)
{
    srand(time(nullptr));

    if (!al_init())
        throw "Could not initialize Allegro 5";
    if (!al_init_image_addon())
        throw "Image addon init error";
    if (!al_init_primitives_addon())
        throw "Primitives init error";
    if (!al_install_keyboard())
        throw "Keyboard init error";
    if (!al_install_mouse())
        throw "Mouse init error";

    //to have many default colors...
    col::initColors();

    if (!flags)
        flags = defaultDispFlags;

    al_set_new_display_flags(flags); //ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE, or ALLEGRO_FULLSCREEN_WINDOW
    currentDisplay = al_create_display(w, h); //800, 600 by default?
    if (!currentDisplay)
        throw "Could not create display";

    al_set_window_title(currentDisplay, window_name);
}

void closeAlleg()
{
    al_destroy_display(currentDisplay);
}


void toggleFullscreen(ALLEGRO_EVENT_QUEUE* displayEvents)
{
    bool prevFullScrn = false;

    bool worked = false;

    int newFlags;

    int width = al_get_display_width(currentDisplay);
    int height = al_get_display_height(currentDisplay);

    //if the display already had the fullscreen window flag
    if (al_get_display_flags(currentDisplay) & ALLEGRO_FULLSCREEN_WINDOW)
    {
        prevFullScrn = true;
    }

    worked = al_set_display_flag(currentDisplay, ALLEGRO_FULLSCREEN_WINDOW, !prevFullScrn);

    newFlags = al_get_display_flags(currentDisplay);

    //if it worked we still check it did toggle it (never know)
    if (worked)
    {
        worked = XOR(prevFullScrn, newFlags & ALLEGRO_FULLSCREEN_WINDOW);
    }

    if (!worked)
    {
        ES("Changing display flags did not work")

        if (displayEvents)
        {
            al_unregister_event_source(displayEvents, al_get_display_event_source(currentDisplay));
        }

        al_destroy_display(currentDisplay);

        if (prevFullScrn)
        {
            al_set_new_display_flags(defaultDispFlags);

            width = defaultDispWidth;
            height = defaultDispHeight;
        }
        else
        {
            al_set_new_display_flags(defaultDispFlags | ALLEGRO_FULLSCREEN_WINDOW);

            //keep the same width/height (so that it's kept when al_set_display_flag is called
        }

        currentDisplay = al_create_display(width, height);

        if (displayEvents)
        {
            al_register_event_source(displayEvents, al_get_display_event_source(currentDisplay));
        }
    }
}



