#include "Drawable.h"

#include "GameContainer.h"

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


