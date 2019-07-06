#include "Drawable.h"

#include "GameContainer.h"

#include "debugNerrors.h"

Drawable::Drawable()
	:m_ready(false)
{
	GameContainer* instance = GameContainer::instance();

	if (!instance)
		throw "No instance of GameContainer";

	instance->addDrawable(this);
}

Drawable::~Drawable()
{
	GameContainer* instance = GameContainer::instance();

	if (instance)
	{
		instance->removeDrawable(this);
	}
}

