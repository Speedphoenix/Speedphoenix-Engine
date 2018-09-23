#include "SpritesContainer.h"

SpritesContainer * SpritesContainer::m_instance = nullptr;

SpritesContainer::SpritesContainer()
{
    if (!m_instance)
        m_instance = this;
}

SpritesContainer::~SpritesContainer()
{
    if (m_instance == this)
        m_instance = nullptr;
}

