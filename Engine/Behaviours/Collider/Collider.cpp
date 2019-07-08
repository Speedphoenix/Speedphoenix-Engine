#include "Collider.h"
#include "ColliderContainer.h"
#include "GameContainer.h"
#include "GameObject.h"

#include "debugNerrors.h"

#include <algorithm>

class GameObject;

using namespace std;

Collider::Collider(GameObject* attachTo, const Transform& _box, bool keepRelativeCoords)
	:Behaviour(attachTo), m_box(_box, &attachTo->transform()), m_previousX(-1),
	m_previousY(-1), m_moved(true)
{
	if (!keepRelativeCoords)
		m_box.setPos(0, 0);
	if (!ColliderContainer::instance())
	{
		GameContainer::getGlobalObject()->attachBehaviour(new ColliderContainer());
	}

	ColliderContainer::instance()->addCollider(this);
}

Collider::~Collider()
{
	ColliderContainer *instance = ColliderContainer::instance();

	if (instance)
	{
		ColliderContainer::instance()->removeCollider(this);
	}
}

Collider::Collider(const Collider& other, GameObject* attachTo)
	:Collider(attachTo, other.getBox())
{

}


//Collider& Collider::operator=(const Collider& rhs)
//{
//	  if (this == &rhs) return *this; // handle self assignment
//
//
//
//	  //assignment operator
//	  return *this;
//}

void Collider::start()
{
	m_previousX = -1; //these are meant to be always different to the real values
	m_previousY = -1; //so that all colliders, even one that doesn't move, will check for collisions the first time
}

void Collider::update()
{
	// depending on how we plan to change the colliders later this could be 
	// moved somewhere else
	for (const auto& coll : m_collidesWith)
	{
		for (const auto& onColl: m_subscribed)
		{
			(onColl.m_what->*onColl.m_func)(coll);
		}
	}
}

void Collider::resetTurn()
{
	m_collidesWith.clear();

	if (m_previousX != m_box.absX() || m_previousY != m_box.absY())
		m_moved = true;
	else
		m_moved = false;

	m_previousX = m_box.absX();
	m_previousY = m_box.absY();
}


bool Collider::collidesWith(const Collider& other) const
{
	return (m_box.touches(other.getBox()));
}

bool Collider::checkAndAddCollision(Collider* other)
{
	this->m_collidesWith.push_back(other);
	other->m_collidesWith.push_back(this);

	return (true);
}

void Collider::subscribe(const OnCollide& what)
{
	m_subscribed.push_back(what);
}

void Collider::unSubscribe(const OnCollide& what)
{
	list<OnCollide>::iterator it;
	it = find(m_subscribed.begin(), m_subscribed.end(), what);
	if (it != m_subscribed.end())
		m_subscribed.erase(it);
}

