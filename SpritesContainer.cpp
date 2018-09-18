#include "SpritesContainer.h"

#include "allegroImplem.h"

#include "debugNerrors.h"

SpritesContainer * SpritesContainer::m_instance = nullptr;

void SpritesContainer::maketest()
{
    //the default flags, just in case it was changed somewhere
    al_set_new_bitmap_flags(ALLEGRO_CONVERT_BITMAP);

    m_sprites[TEST_SHEETNAME] = al_load_bitmap(TEST_SPRITESHEET);
}

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


