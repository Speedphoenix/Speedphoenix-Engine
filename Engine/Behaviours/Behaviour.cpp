#include "Behaviour.h"
#include "GameContainer.h"
#include "GameObject.h"

Behaviour::Behaviour(GameObject* attachTo)
    :m_attachedObject(attachTo), m_toRemove(false)
{
    GameContainer* instance = GameContainer::instance();

    if (!instance)
        throw "No instance of GameContainer";

    m_containerIterator = instance->addBehaviour(this);
}

Behaviour::~Behaviour()
{
    GameContainer* instance = GameContainer::instance();

    if (instance)
    {
        instance->removeBehaviour(m_containerIterator);
    }
}


void Behaviour::setToRemove()
{
    if (m_toRemove)
        return;

    if (m_attachedObject->detachBehaviour(this))
    {
        m_toRemove = true;
        m_attachedObject = nullptr;
    }
}

