#include "Drawable.h"

#include "GameContainer.h"
#include "TransformBase.h"
#include "Transform.h"
#include "Animator.h"
#include "Camera.h"

#include "debugNerrors.h"

Drawable::Drawable()
{
	GameContainer* instance = GameContainer::instance();

	if (!instance)
		throw "No instance of GameContainer";

	m_containerIterator = instance->addDrawable(this);
}

Drawable::~Drawable()
{
	GameContainer* instance = GameContainer::instance();

	if (instance)
	{
		instance->removeDrawable(m_containerIterator);
	}
}

void Drawable::draw(Animator& what, const TransformBase& where)
{
	const Transform& camera = Camera::getCurrentView();

	if (where.touches(camera))
	{
		double relx = 0, rely = 0;
		where.getRelativeCoords(camera, relx, rely);
		what.draw(relx, rely);
	}
}

