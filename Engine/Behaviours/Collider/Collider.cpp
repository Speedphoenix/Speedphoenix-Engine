#include "Collider.h"
#include "ColliderContainer.h"
#include "GameContainer.h"
#include "GlobalObject.h"

#include "debugNerrors.h"

class GameObject;

Collider::Collider(GameObject* attachTo, const Transform& _box)
    :Behaviour(attachTo), m_box(_box, &attachTo->getTransform()), previousX(-1), previousY(-1), m_moved(true)
{
    if (!ColliderContainer::instance())
    {
        GameContainer::getGlobalObject()->attachBehaviour(new ColliderContainer());
    }

    ColliderContainer::instance()->addCollider(this);
}

Collider::~Collider()
{
    ColliderContainer::instance()->removeCollider(this);
}

Collider::Collider(const Collider& other, GameObject* attachTo)
    :Collider(attachTo, other.getBox())
{

}


//Collider& Collider::operator=(const Collider& rhs)
//{
//    if (this == &rhs) return *this; // handle self assignment
//
//
//
//    //assignment operator
//    return *this;
//}

void Collider::start()
{
    previousX = -1; //these are meant to be always different to the real values
    previousY = -1; //so that all colliders, even one that doesn't move, will check for collisions the first time
}

void Collider::resetTurn()
{
    m_collidesWith.clear();

    if (previousX != m_box.absX() || previousY != m_box.absY())
        m_moved = true;
    else
        m_moved = false;

    previousX = m_box.absX();
    previousY = m_box.absY();
}


bool Collider::collidesWith(const Collider& other) const
{
    return m_box.touches(other.getBox());
}

bool Collider::checkAndAddCollision(Collider* other)
{
    this->m_collidesWith.push_back(other);
    other->m_collidesWith.push_back(this);

    return true;
}

