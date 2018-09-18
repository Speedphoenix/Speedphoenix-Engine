#include "Behaviour.h"
#include "GameContainer.h"
#include "GameObject.h"

Behaviour::Behaviour(GameObject* attachTo)
    :m_attachedObject(attachTo)
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

