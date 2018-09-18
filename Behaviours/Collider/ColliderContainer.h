#ifndef COLLIDERCONTAINER_H
#define COLLIDERCONTAINER_H

#include <Behaviour.h>

#include <list>

class Collider;

struct XComparator{
    XComparator() { }

    //this acts as first < second
    bool operator() (Collider* first, Collider* second);
};

class ColliderContainer : public Behaviour
{
    //statics
    private:
        static ColliderContainer * m_instance;
    public:
        static ColliderContainer* instance() { return m_instance; }


    //non statics
    private:
        //in the ordered list we only need to check collisions on the few boxes that come after
        //looking along the x axis because it is usually wider (and therefore sparser) than the y axis
        std::list<Collider*> m_XOrdered;

        bool m_waitToSort;

        XComparator m_xCompare;

        bool m_firstTurn;

    private:
        void sortList();

    public:
        ColliderContainer();
        virtual ~ColliderContainer();

        virtual void start();
        virtual void preUpdate();
        virtual void update();
        virtual void postUpdate();

        void addCollider(Collider* what);
        void removeCollider(Collider* what);
};

#endif // COLLIDERCONTAINER_H
