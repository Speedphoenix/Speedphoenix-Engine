#ifndef COLLIDER_H
#define COLLIDER_H

#include <Behaviour.h>

#include "Transform.h"

#include <list>


class GameObject;
class ColliderContainer;

class Collider : public Behaviour
{
    friend ColliderContainer;

    protected:
        Transform m_box;

        std::list<Collider*> m_collidesWith;

        double previousX, previousY;

        bool m_moved;


    protected:
        //called by the ColliderContainer if the boxes collide.
        //in the parent class (this one) the box is what gives the collisions so no need to check
        virtual bool checkAndAddCollision(Collider* other);

    public:
        Collider(GameObject* attachTo, const Transform& _box);
        Collider(const Collider& other, GameObject* attachTo);
        virtual ~Collider();

        //don't allow to have twice the same collider on the same object
        Collider(const Collider& other) = delete;

//        Collider& operator=(const Collider& rhs);

        //resets the collisions. Need to make it keep old collisions for entering/exiting n'stuff
        virtual void resetTurn();

        virtual void start();
        virtual void update() { }

        bool collidesWith(const Collider& other) const;

        const std::list<Collider*>& getCollidingList() const { return m_collidesWith; }

        const Transform& getBox() const { return m_box; }

        double boxAbsX() const { return m_box.absX(); }
        double boxAbsY() const { return m_box.absY(); }
        double boxEndAbsX() const { return m_box.endAbsX(); }
        double boxEndAbsY() const { return m_box.endAbsY(); }

        bool moved() const { return m_moved; }
};

#endif // COLLIDER_H
