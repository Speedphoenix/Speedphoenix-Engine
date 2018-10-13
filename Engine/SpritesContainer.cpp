#include "SpritesContainer.h"

#include "allegroImplem.h"

SpritesContainer * SpritesContainer::m_instance = nullptr;

SpritesContainer::SpritesContainer()
{
	if (!m_instance)
		m_instance = this;
}

SpritesContainer::~SpritesContainer()
{
	for (const auto& elem : m_sprites)
		al_destroy_bitmap(elem.second);
	if (m_instance == this)
		m_instance = nullptr;
}

