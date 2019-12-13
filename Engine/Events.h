#ifndef EVENTS_H_INCLUDED //does not conflict with allegro's events.h
# define EVENTS_H_INCLUDED

# include <set>

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

template <typename T>
class BehaviourCallback
{
	protected:
		Behaviour *m_catcher;
		void (Behaviour::*m_func)(const T&);

	public:
		BehaviourCallback1(Behaviour *_catcher,
				void (Behaviour::*_func)(const T&)
			:m_catcher(_catcher), m_func(_func)
		{ }
		virtual ~BehaviourCallback1() { }

		virtual void call(const T& event)
		{
			(m_catcher->*m_func)(event);
		}
}

/*
		// lists of all things to call when events arise
		// std::set<BehaviourDisplayqCallback *> m_callbacksDisp;
		std::set<BehaviourKeyboardCallback *> m_callbacksKeyboard;
		std::set<BehaviourMouseCallback *> m_callbacksMouse;
		std::set<BehaviourTouchCallback *> m_callbacksTouch;

		//these will be called by their respective constructors
		void addObject(GameObject* what);
		void addBehaviour(Behaviour* what);
		void addDrawable(Drawable* what);

		//these will set the instance to be removed at the end of the turn
		void removeObject(GameObject *what);
		void removeBehaviour(Behaviour *what);
		void removeDrawable(Drawable *what);


		// used to subscribe to certain events make sure you keep the returned
		// value to unsubscribe later
		virtual const BehaviourKeyboardCallback *addKeyboardCallback(
					Behaviour *catcher, KeyboardEventCallback toCall) final;
		virtual const BehaviourMouseCallback *addMouseCallback(
					Behaviour *catcher, MouseEventCallback toCall) final;
		virtual const BehaviourTouchCallback *addTouchCallback(
					Behaviour *catcher, TouchEventCallback toCall) final;

		// used to unsubscribe to events
		virtual void removeKeyboardCallback(BehaviourKeyboardCallback *what) final;
		virtual void removeMouseCallback(BehaviourMouseCallback *what) final;
		virtual void removeTouchCallback(BehaviourTouchCallback *what) final;
*/

// TODO
template <typename T>
class BehaviourCallbackList
{
	protected:
		std::set<BehaviourCallback<T> *> m_callbacks;

	public:
		BehaviourCallbackList() { }
		virtual ~BehaviourCallbackList();

		virtual void call(const T& event)
		{
			for (auto& elem : m_callbacks)
				elem->call(event);
		}

		virtual const BehaviourCallback<T> *addCallBack(Behaviour *catcher,
					T toCall)
}

// The classes that will call the event listeners along with the right object
class BehaviourCallback1
{
	protected:
		Behaviour *m_catcher;

	public:
		BehaviourCallback1(Behaviour *_catcher);
		virtual ~BehaviourCallback1();
};

class BehaviourKeyboardCallback : public BehaviourCallback1
{
	protected:
		KeyboardEventCallback m_func;

	public:
		BehaviourKeyboardCallback(Behaviour *_catcher, KeyboardEventCallback fn);
		virtual ~BehaviourKeyboardCallback();

		virtual void call(const KeyboardEvent& event);
};

class BehaviourMouseCallback : public BehaviourCallback1
{
	protected:
		MouseEventCallback m_func;

	public:
		BehaviourMouseCallback(Behaviour *_catcher, MouseEventCallback fn);
		virtual ~BehaviourMouseCallback();

		virtual void call(const MouseEvent& event);
};

class BehaviourTouchCallback : public BehaviourCallback1
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
