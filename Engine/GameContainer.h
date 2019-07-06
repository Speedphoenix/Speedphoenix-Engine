#ifndef GAMECONTAINER_H
#define GAMECONTAINER_H

#include <list>
#include <set>

class Drawable;
class GameObject;
class Behaviour;
struct ALLEGRO_EVENT_QUEUE;

struct KeyboardEvent;
struct MouseEvent;
struct TouchEvent;

class GameContainer
{
	//statics
	protected:
		static GameContainer * m_instance;
	public:
		static GameContainer * instance() { return m_instance; }

		static GameObject * getGlobalObject() { return m_instance->m_globalObject; }

		///the time elapsed since the last game loop. Use this as a factor to move...
		static double deltaTime() { return m_instance->m_deltaTime; }

	//non-static member variables
	private:
		//lists of all Objects and instances of most things
		std::set<GameObject *> m_objects;
		std::set<Behaviour *> m_behaviours;
		std::set<Drawable *> m_drawables;

		//lists of things that still need their start() function to be called
		std::list<GameObject *> m_newObjects;
		std::list<Behaviour *> m_newBehaviours;
		std::list<Drawable *> m_newDrawables;

		//list of things that will be be destroyed at the end of current turn (before draw)
		std::list<GameObject *> m_remObjects;
		std::list<Behaviour *> m_remBehaviours;
		std::list<Drawable *> m_remDrawables;

		//when manualy asking to remove a behaviour
		std::list<Behaviour *> m_remManBehaviours;

		ALLEGRO_EVENT_QUEUE *m_eventsDisplay;
		ALLEGRO_EVENT_QUEUE *m_eventsKeyboard;
		ALLEGRO_EVENT_QUEUE *m_eventsMouse;
		ALLEGRO_EVENT_QUEUE *m_eventsTouch;

		double m_deltaTime;
		// make a new_list for the drawables, make all the addition of everything
		// to their respective lists in the initAll(), use iterators in the autoRemove

	protected:

		GameObject* m_globalObject;

		bool m_finished;


	//non-static methods
	protected:

		virtual void onKeyboardEvent(const KeyboardEvent& event) { }
		virtual void onMouseEvent(const MouseEvent& event) { }
		virtual void onTouchEvent(const TouchEvent& event) { }


		//call every turn

		//calls the start function for new objects
		void initAll();

		//the individual updates are called for each object, behaviour...
		void eventCatch();		//!< takes in all events that happened since the last game loop
		void preUpdate();		//!< comes first
		virtual void playerUpdate();	//!< does everything related to player/ia input
		void autoUpdate();		//!< the main update
		void postUpdate();		//!< comes last
		void autoRemove();		//!< remove anything that needs to be removed during this game loop

		virtual void init() { }

	public:
		GameContainer();
		virtual ~GameContainer();

		//no copy ctor or assignment
		GameContainer(const GameContainer&) = delete;
		GameContainer& operator=(const GameContainer&) = delete;

		///called at the start of the game
		void start();

		///called at every game loop, calls every other update function and draw()
		virtual void update(double factor);

		///draws the drawables
		virtual void draw();

		///returns if the game should stop (is finished) - might wanna rename this one
		virtual bool shouldStop() const { return m_finished; }

		virtual void setFinished(bool val) { m_finished = val; }

		//the border of the map...
		virtual double maximumX() { return 0.0; }
		virtual double maximumY() { return 0.0; }


		//these will be called by their respective constructors
		void addObject(GameObject* what);
		void addBehaviour(Behaviour* what);
		void addDrawable(Drawable* what);

		//these will set the instance to be removed at the end of the turn
		void removeObject(GameObject *what);
		void removeBehaviour(Behaviour *what);
		void removeDrawable(Drawable *what);

		void manualRemoveBehaviour(Behaviour *what);
};


#endif // GAMECONTAINER_H
