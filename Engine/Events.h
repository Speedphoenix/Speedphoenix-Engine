#ifndef EVENTS_H_INCLUDED //does not conflict with allegro's events.h
# define EVENTS_H_INCLUDED

union ALLEGRO_EVENT;

struct Event;
struct KeyboardEvent;
struct MouseEvent;
struct TouchEvent;
class Behaviour;

// TODO: make display events

// the different types of callbacks
typedef void (Behaviour::*EventCallback)(const Event&);
typedef void (Behaviour::*KeyboardEventCallback)(const KeyboardEvent&);
typedef void (Behaviour::*MouseEventCallback)(const MouseEvent&);
typedef void (Behaviour::*TouchEventCallback)(const TouchEvent&);

// The classes that will call the event listeners along with the right object
class BehaviourCallback
{
	protected:
		Behaviour *m_catcher;

	public:
		BehaviourCallback(Behaviour *_catcher);
		virtual ~BehaviourCallback();
};

class BehaviourKeyboardCallback : public BehaviourCallback
{
	protected:
		KeyboardEventCallback m_func;

	public:
		BehaviourKeyboardCallback(Behaviour *_catcher, KeyboardEventCallback fn);
		virtual ~BehaviourKeyboardCallback();

		virtual void call(const KeyboardEvent& event);
};

class BehaviourMouseCallback : public BehaviourCallback
{
	protected:
		MouseEventCallback m_func;

	public:
		BehaviourMouseCallback(Behaviour *_catcher, MouseEventCallback fn);
		virtual ~BehaviourMouseCallback();

		virtual void call(const MouseEvent& event);
};

class BehaviourTouchCallback : public BehaviourCallback
{
	protected:
		TouchEventCallback m_func;

	public:
		BehaviourTouchCallback(Behaviour *_catcher, TouchEventCallback fn);
		virtual ~BehaviourTouchCallback();

		virtual void call(const TouchEvent& event);
};

inline void EventNoop(const Event& event)
{
	(void)event;
}

inline void KeyboardEventNoop(const KeyboardEvent& event)
{
	(void)event;
}

inline void MouseEventNoop(const MouseEvent& event)
{
	(void)event;
}

inline void TouchEventNoop(const TouchEvent& event)
{
	(void)event;
}

struct Event
{
	unsigned int type;
	double timestamp;

	Event(const ALLEGRO_EVENT& what);
};

struct KeyboardEvent : public Event
{
	struct ALLEGRO_KEYBOARD *source;

	struct ALLEGRO_DISPLAY *display;
	int keycode;
	int unichar;
	unsigned int modifiers;
	bool repeat;

	KeyboardEvent(const ALLEGRO_EVENT& what);
};

struct MouseEvent : public Event
{
	struct ALLEGRO_MOUSE *source;

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

struct TouchEvent : public Event
{
	struct ALLEGRO_TOUCH_INPUT *source;

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
