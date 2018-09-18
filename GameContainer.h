#ifndef GAMECONTAINER_H
#define GAMECONTAINER_H

#include <list>

class Drawable;
class GameObject;
class GlobalObject;
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

        static GlobalObject * getGlobalObject() { return m_instance->m_globalObject; }

        ///the time elapsed since the last game loop. Use this as a factor to move...
        static double deltaTime() { return m_instance->m_deltaTime; }

    //non-static member variables
    private:
        //lists of all Objects and instances of most things
        std::list<GameObject *> m_objects;
        std::list<Behaviour *> m_behaviours;
        std::list<Drawable *> m_drawables;

        //list of things that will be be destroyed at the end of current turn (before draw)
        std::list<std::list<GameObject*>::iterator> m_remObjects;
        std::list<std::list<Behaviour*>::iterator> m_remBehaviours;
        std::list<std::list<Drawable*>::iterator> m_remDrawables;

        ALLEGRO_EVENT_QUEUE *m_eventsDisplay;
        ALLEGRO_EVENT_QUEUE *m_eventsKeyboard;
        ALLEGRO_EVENT_QUEUE *m_eventsMouse;
        ALLEGRO_EVENT_QUEUE *m_eventsTouch;

        double m_deltaTime;

    protected:

        GlobalObject* m_globalObject;

        bool m_finished;


    //non-static methods
    protected:

        virtual void onKeyboardEvent(const KeyboardEvent& event) { }
        virtual void onMouseEvent(const MouseEvent& event) { }
        virtual void onTouchEvent(const TouchEvent& event) { }


        //call every turn
        //the individual updates are called for each object, behaviour...
        void eventCatch();      //!< takes in all events that happened since the last game loop
        void preUpdate();       //!< comes first
        virtual void playerUpdate();    //!< does everything related to player/ia input
        void autoUpdate();      //!< the main update
        void postUpdate();      //!< comes last
        void autoRemove();      //!< remove anything that needs to be removed during this game loop

    public:
        GameContainer();
        virtual ~GameContainer();

        //no copy ctor or assignment
        GameContainer(const GameContainer&) = delete;
        GameContainer& operator=(const GameContainer&) = delete;

        ///called at the start of the game
        virtual void start();

        ///called at every game loop, calls every other update function and draw()
        virtual void update(double factor);

        ///draws the drawables
        virtual void draw();

        ///returns if the game should stop (is finished) - might wanna rename this one
        virtual bool shouldStop() const { return m_finished; }


        //the border of the map...
        virtual double maximumX() { return 0.0; }
        virtual double maximumY() { return 0.0; }


        //these will be called by their respective constructors
        std::list<GameObject*>::iterator addObject(GameObject* what);
        std::list<Behaviour*>::iterator addBehaviour(Behaviour* what);
        std::list<Drawable*>::iterator addDrawable(Drawable* what);

        //these will set the iterator to be removed at the end of the turn
        void removeObject(std::list<GameObject*>::iterator what);
        void removeBehaviour(std::list<Behaviour*>::iterator what);
        void removeDrawable(std::list<Drawable*>::iterator what);
};


#endif // GAMECONTAINER_H
