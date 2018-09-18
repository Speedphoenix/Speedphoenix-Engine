#include "GameObject.h"

#include "GameContainer.h"

#include "debugNerrors.h"

#include <algorithm>

using namespace std;

GameObject::GameObject(const Transform& source)
    :m_toRemove(false), m_transform(source)
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
    :m_toRemove(false), m_transform(_x, _y, _w, _h, false, _speed)
{
    GameContainer* instance = GameContainer::instance();

    if (!instance)
        throw "No instance of GameContainer";

    m_containerIterator = instance->addObject(this);
}

GameObject::GameObject(GameObject *_parent, double _x, double _y, double _w, double _h)
    :m_toRemove(false), m_transform(&_parent->getTransform(), _x, _y, _w, _h)
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
    //That calls the destructor for all things instide, who will tell the GameContainer to remove them
}


void GameObject::update()
{

}


/**
    Do not use this function explicitly. It is already called inside NameOfParent.addChild(pointerOfChild)
*/
void GameObject::setParent(GameObject *val)
{
    m_parent = val;

    if (val)
        m_transform.setParent(&val->getTransform());
    else
        m_transform.setParent(nullptr);
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
        vector<GameObject*>::iterator it;
        it = find(m_children.begin(), m_children.end(), what);

        if (it!=m_children.end())
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

    if (m_parent)
        m_parent->removeChild(this);

    ///make remove all the childs

    GameContainer* instance = GameContainer::instance();
    if (instance)
    {
        instance->removeObject(m_containerIterator);
    }
}


