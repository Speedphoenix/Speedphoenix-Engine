#include "Events.h"

//allegro 5's events. contains ALLEGRO_EVENT etc
#include "allegro5/events.h"

// BehaviourCallback
BehaviourCallback::BehaviourCallback(Behaviour *_catcher)
	:m_catcher(_catcher)
{

}

BehaviourCallback::~BehaviourCallback()
{

}

// BehaviourKeyboardCallback
BehaviourKeyboardCallback::BehaviourKeyboardCallback(Behaviour *_catcher,
		KeyboardEventCallback fn)
	:BehaviourCallback(_catcher), m_func(fn)
{

}

BehaviourKeyboardCallback::~BehaviourKeyboardCallback()
{

}

void BehaviourKeyboardCallback::call(const KeyboardEvent& event)
{
	(m_catcher->*m_func)(event);
}

// BehaviourMouseCallback
BehaviourMouseCallback::BehaviourMouseCallback(Behaviour *_catcher,
		MouseEventCallback fn)
	:BehaviourCallback(_catcher), m_func(fn)
{

}

BehaviourMouseCallback::~BehaviourMouseCallback()
{

}

void BehaviourMouseCallback::call(const MouseEvent& event)
{
	(m_catcher->*m_func)(event);
}

// BehaviourTouchCallback
BehaviourTouchCallback::BehaviourTouchCallback(Behaviour *_catcher,
		TouchEventCallback fn)
	:BehaviourCallback(_catcher), m_func(fn)
{

}

BehaviourTouchCallback::~BehaviourTouchCallback()
{

}

void BehaviourTouchCallback::call(const TouchEvent& event)
{
	(m_catcher->*m_func)(event);
}

// The base event structs (without any function calls)
Event::Event(const ALLEGRO_EVENT& what)
	:type(what.type), timestamp(what.any.timestamp)
{

}

KeyboardEvent::KeyboardEvent(const ALLEGRO_EVENT& what)
	:Event(what), source(what.keyboard.source), display(what.keyboard.display),
		keycode(what.keyboard.keycode), unichar(what.keyboard.unichar), modifiers(what.keyboard.modifiers),
		repeat(what.keyboard.repeat)
{

}


MouseEvent::MouseEvent(const ALLEGRO_EVENT& what)
	:Event(what), source(what.mouse.source), display(what.mouse.display),
		x(what.mouse.x), y(what.mouse.y), z(what.mouse.z), w(what.mouse.w), dx(what.mouse.dx), dy(what.mouse.dy),
		dz(what.mouse.dz), dw(what.mouse.dw), button(what.mouse.button), pressure(what.mouse.pressure)
{

}

TouchEvent::TouchEvent(const ALLEGRO_EVENT& what)
	:Event(what), source(what.touch.source), display(what.touch.display),
		id(what.touch.id), x(what.touch.x), y(what.touch.y), dx(what.touch.dx), dy(what.touch.dy), primary(what.touch.primary)
{

}
