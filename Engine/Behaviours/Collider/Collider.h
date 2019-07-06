#ifndef COLLIDER_H
#define COLLIDER_H

#include <Behaviour.h>

#include "Transform.h"

#include <list>

class GameObject;
class ColliderContainer;
class Collider;

// use static_cast when using a member function of a child class of Behaviour
struct OnCollide
{
	Behaviour *m_what;
	void (Behaviour::*m_func)(Collider *);
	OnCollide(Behaviour *_what, void (Behaviour::*_func)(Collider *))
		:m_what(_what), m_func(_func)
	{ }
	bool operator==(const OnCollide& other)
	{
		return (m_what == other.m_what
			&& m_func == other.m_func);
	}
};

class Collider : public Behaviour
{
	friend ColliderContainer;

	protected:
		Transform m_box;

		// when checking for collisions, you can choose between checking each
		// collider in the list individually (in the update() function of your
		// behaviour) or by adding an onCollide function
		std::list<Collider*> m_collidesWith;
		std::list<OnCollide> m_subscribed;

		double m_previousX, m_previousY;

		bool m_moved;

	protected:
		//called by the ColliderContainer if the boxes collide.
		//in the parent class (this one) the box is what gives the collisions so no need to check
		virtual bool checkAndAddCollision(Collider* other);

	public:
		Collider(GameObject* attachTo, const Transform& _box, bool keepRelativeCoords = false);
		Collider(const Collider& other, GameObject* attachTo);
		virtual ~Collider();

		//don't allow to have twice the same collider on the same object
		Collider(const Collider& other) = delete;

//		  Collider& operator=(const Collider& rhs);

		//resets the collisions. Need to make it keep old collisions for entering/exiting n'stuff
		virtual void resetTurn();

		virtual void start();
		virtual void update();

		bool collidesWith(const Collider& other) const;

		const std::list<Collider*>& getCollidingList() const { return m_collidesWith; }

		const Transform& getBox() const { return m_box; }

		double boxAbsX() const { return m_box.absX(); }
		double boxAbsY() const { return m_box.absY(); }
		double boxEndAbsX() const { return m_box.endAbsX(); }
		double boxEndAbsY() const { return m_box.endAbsY(); }

		bool moved() const { return m_moved; }

		void subscribe(const OnCollide& what);
		void unSubscribe(const OnCollide& what);
};

#endif // COLLIDER_H
