#include "Events.h"

//allegro 5's events. contains ALLEGRO_EVENT etc
#include "events.h"

KeyboardEvent::KeyboardEvent(const ALLEGRO_EVENT& what)
    :type(what.type), source(what.keyboard.source), timestamp(what.any.timestamp), display(what.keyboard.display),
        keycode(what.keyboard.keycode), unichar(what.keyboard.unichar), modifiers(what.keyboard.modifiers), repeat(what.keyboard.repeat)
{

}


MouseEvent::MouseEvent(const ALLEGRO_EVENT& what)
    :type(what.type), source(what.mouse.source), timestamp(what.any.timestamp), display(what.mouse.display),
        x(what.mouse.x), y(what.mouse.y), z(what.mouse.z), w(what.mouse.w), dx(what.mouse.dx), dy(what.mouse.dy),
        dz(what.mouse.dz), dw(what.mouse.dw), button(what.mouse.button), pressure(what.mouse.pressure)
{

}

TouchEvent::TouchEvent(const ALLEGRO_EVENT& what)
    :type(what.type), source(what.touch.source), timestamp(what.any.timestamp), display(what.touch.display),
        id(what.touch.id), x(what.touch.x), y(what.touch.y), dx(what.touch.dx), dy(what.touch.dy), primary(what.touch.primary)
{

}

