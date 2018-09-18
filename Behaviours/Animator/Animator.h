#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <Behaviour.h>

#include "Animation.h"
#include "State.h"

#include <map>

class GameObject;
class TransformBase;
class Frame;
struct ALLEGRO_BITMAP;
struct ALLEGRO_EVENT_QUEUE;
struct ALLEGRO_TIMER;

class Animator : public Behaviour
{
    ///FOR TESTING PURPOSES
    public:
        void maketest();

    //statics
    public:
        ///REDO THIS (and make it non static? idk)
        static State getBestState(const std::map<Transition, Animation*>& theMap, Anim::AnimType animType, State depending);

    //non-statics
    protected:

        //timer and event queue to increment frame number at the right intervals
        ALLEGRO_TIMER* m_timer;
        ALLEGRO_EVENT_QUEUE* m_queue;

        //current frame number
        unsigned m_currFrame;

        //current state/transition
        //if the animation isn't a transition, to and from states are the same
        Transition m_currState;

        State m_askedState;

        //should replace all of these by one big map<Transition, Animation *>
        std::map<Transition, Animation*> m_animations;

        //the asked direction (because the actual shown dir can be different based on availability
        double m_askedDir;

    //methods
    protected:
        virtual void setNewLapse();

    public:
        Animator(GameObject* attachTo, GeneralState startState = Walking, double startDirection = 0);
        virtual ~Animator();

//        Animator(const Animator& other);
//        Animator& operator=(const Animator& other);


        /// draws at destx, desty on the current target bitmap
        virtual void draw(double destx, double desty);

        /// starts the animation
        virtual void launch();   //can be used to un-pause too
        ///stops thee animation
        virtual void stop();    //can be used to pause too
        ///will update stuff like the frame counter if need be
        virtual void update();

        ///returns the current image. Use the draw function instead
        virtual ALLEGRO_BITMAP* getImg();

        ///direction should be in radians
        virtual void setDirection(double direction);
        virtual void setDirection(const TransformBase& direction);

        virtual void setState(State what, bool shouldChangeDirec = true);
        virtual void setState(State what, double direction);
        virtual void setState(State what, const TransformBase& direction);

        virtual void makeActive(bool playOnce = true);
        virtual void makeIdle();

        unsigned currFrame() const { return m_currFrame; }
        void setCurrFrame(unsigned val);
        State currAnimation() const { return m_currState.to; }
};

#endif // ANIMATOR_H


