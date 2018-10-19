#include "GameObject.h"

#include "GameContainer.h"
#include "Behaviour.h"

#include "debugNerrors.h"

#include <algorithm>

using namespace std;

GameObject::GameObject(const Transform& source)
	:m_toRemove(false), m_transform(source), m_dependsOnParent(true)
{
	if (source.parent())
	{
		ES("A transform with a parent has been passed for an object's constructor")
	}

	GameContainer* instance = GameContainer::instance();

	if (!instance)
		throw "No instance of GameContainer";

	m_containerIterator = instance->addObject(this);
}


GameObject::GameObject(double _x, double _y, double _w, double _h, double _speed)
	:m_toRemove(false), m_transform(_x, _y, _w, _h, false, _speed), m_dependsOnParent(true)
{
	GameContainer* instance = GameContainer::instance();

	if (!instance)
		throw "No instance of GameContainer";

	m_containerIterator = instance->addObject(this);
}

GameObject::GameObject(GameObject *_parent, bool _dependsOnParent, double _x, double _y, double _w, double _h)
	:m_toRemove(false), m_transform(&_parent->transform(), _x, _y, _w, _h), m_dependsOnParent(_dependsOnParent)
{
	m_parent = _parent;

	GameContainer* instance = GameContainer::instance();

	if (!instance)
		throw "No instance of GameContainer";

	m_containerIterator = instance->addObject(this);
}

GameObject::~GameObject()
{
	//gameObjects aren't set to be removed from the gameContainer in their destructor but in the setToRemove() func

	//the GameObjects are removed first and destroyed.
	//This calls the destructor for all things instide, who will tell the GameContainer to remove them
	for (auto& elem : m_behaviours)
	{
		delete elem;
	}
}


void GameObject::update()
{

}


/**
	Do not call this function explicitly. It is already called inside NameOfParent.addChild(pointerOfChild)
*/
void GameObject::setParent(GameObject *val)
{
	m_parent = val;

	if (val)
		m_transform.setParent(&val->transform());
	else
		m_transform.setParent(nullptr);
}

void GameObject::removeParent()
{
	setParent(nullptr);
	if (m_dependsOnParent)
		setToRemove();
}

void GameObject::addChild(GameObject *child)
{
	if (child)
	{
		m_children.push_back(child);
		child->setParent(this);
	}
}

bool GameObject::removeChild(GameObject *what)
{
	if (what)
	{
		list<GameObject*>::iterator it;
		it = find(m_children.begin(), m_children.end(), what);

		if (it != m_children.end())
		{
			m_children.erase(it);
			what->removeParent();
			return true;
		}
	}
	return false;
}

void GameObject::setToRemove()
{
	if (m_toRemove)
		return;
	m_toRemove = true;

	//remove this from the parent
	if (m_parent)
		m_parent->removeChild(this);

	//remove all the children
	for (auto& elem : m_children)
		elem->removeParent();
	m_children.clear();

	GameContainer* instance = GameContainer::instance();
	if (instance)
	{
		instance->removeObject(m_containerIterator);
	}
}

void GameObject::attachBehaviour(Behaviour * what)
{
	m_behaviours.push_back(what);
}

bool GameObject::detachBehaviour(Behaviour *what)
{
	if (what)
	{
		list<Behaviour*>::iterator it;
		it = find(m_behaviours.begin(), m_behaviours.end(), what);

		if (it != m_behaviours.end())
		{
			m_behaviours.erase(it);
			return true;
		}
	}
	return false;
}

