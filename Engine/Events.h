#ifndef EVENTS_H_INCLUDED //does not conflict with allegro's events.h
#define EVENTS_H_INCLUDED

union ALLEGRO_EVENT;

struct KeyboardEvent {
    unsigned int type;
    struct ALLEGRO_KEYBOARD *source;
    double timestamp;

    struct ALLEGRO_DISPLAY *display;
    int keycode;
    int unichar;
    unsigned int modifiers;
    bool repeat;

    KeyboardEvent(const ALLEGRO_EVENT& what);
};

struct MouseEvent {
    unsigned int type;
    struct ALLEGRO_MOUSE *source;
    double timestamp;

    /* (display) Window the event originate from
     * (x, y) Primary mouse position
     * (z) Mouse wheel position (1D 'wheel'), or,
     * (w, z) Mouse wheel position (2D 'ball')
     * (pressure) The pressure applied, for stylus (0 or 1 for normal mouse)
     */
    struct ALLEGRO_DISPLAY *display;
    int x, y;
    int z, w;
    int dx, dy, dz, dw;
    unsigned int button;
    float pressure;

    MouseEvent(const ALLEGRO_EVENT& what);
};

struct TouchEvent {
    unsigned int type;
    struct ALLEGRO_TOUCH_INPUT *source;
    double timestamp;

    struct ALLEGRO_DISPLAY *display;
    /* (id) Identifier of the event, always positive number.
     * (x, y) Touch position on the screen in 1:1 resolution.
     * (dx, dy) Relative touch position.
     * (primary) True, if touch is a primary one (usually first one).
     */
    int id;
    float x, y;
    float dx, dy;
    bool primary;

    TouchEvent(const ALLEGRO_EVENT& what);
};

#endif // EVENTS_H_INCLUDED
