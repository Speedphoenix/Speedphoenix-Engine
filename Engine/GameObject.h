#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Transform.h"

#include <list>

class Behaviour;

class GameObject
{
    private:
        std::list<GameObject *>::iterator m_containerIterator;
        std::list<Behaviour *> m_behaviours;

    protected:
        //is set indicatively only. The removal from the GameContainer goes differently
        bool m_toRemove;

        Transform m_transform;

        GameObject *m_parent = nullptr;
        std::list<GameObject *> m_children;

    public:
        GameObject(const Transform& source);
        GameObject(double _x = 0, double _y = 0, double _w = 0, double _h = 0, double _speed = 0);
        GameObject(GameObject *_parent, double _x = 0, double _y = 0, double _w = 0, double _h = 0);
        virtual ~GameObject();

        //important functions
        virtual void start() { }        //!< called at the start of the game (when all the gameobjects N' stuff are already instantiated)
        virtual void preUpdate() { }    //!< called at the start of each game loop
        virtual void update();          //!< called during each game loop
        virtual void postUpdate() { }   //!< called after update in each loop, before drawing

        virtual GameObject *parent() { return m_parent; }

        /// Do not call this function explicitly. It is already called inside NameOfParent.addChild(pointerOfChild)
        virtual void setParent(GameObject *val);
        virtual void removeParent() { setParent(nullptr); } ///if the object cannot live without the parent kill it inside here

        virtual void addChild(GameObject *child);
        virtual bool removeChild(GameObject *what);

        virtual Transform& getTransform() { return m_transform; }
        virtual void setTransform(const Transform& val) { m_transform = val; }

        virtual void setToRemove();
        virtual bool toRemove() { return m_toRemove; }

        void attachBehaviour(Behaviour *what);
        bool deleteBehaviour(Behaviour *what);
};

#endif // GAMEOBJECT_H
