#include "Behaviour.h"
#include "GameContainer.h"
#include "GameObject.h"

#include "debugNerrors.h"

Behaviour::Behaviour(GameObject* attachTo)
	:m_attachedObject(attachTo), m_toRemove(false)
{
	GameContainer* instance = GameContainer::instance();

	if (!instance)
		throw "No instance of GameContainer";

	instance->addBehaviour(this);
}

Behaviour::~Behaviour()
{
	GameContainer* instance = GameContainer::instance();

	if (instance)
	{
		instance->removeBehaviour(this);
	}
}


void Behaviour::setToRemove()
{
	if (m_toRemove)
		return;

	m_attachedObject->detachBehaviour(this);
	m_toRemove = true;
	m_attachedObject = nullptr;

	GameContainer::instance()->manualRemoveBehaviour(this);
}

