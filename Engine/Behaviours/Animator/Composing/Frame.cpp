#include "Frame.h"

#include "allegroImplem.h"

Frame::Frame(ALLEGRO_BITMAP* img, int _takenX, int _takenY, int _width, int _height)
    :m_parentImg(img), m_sprite(al_create_sub_bitmap(img, _takenX, _takenY, _width, _height)),
    m_takenX(_takenX), m_takenY(_takenY), m_width(_width), m_height(_height)
{
    if (!m_sprite)
    {
        throw "could not create a sub bitmap";
    }
}

Frame::Frame(ALLEGRO_BITMAP* img)
    :Frame(img, 0, 0, al_get_bitmap_width(img), al_get_bitmap_height(img))
{

}

Frame::~Frame()
{
    al_destroy_bitmap(m_sprite);
}

bool Frame::operator==(const Frame& cmp) const
{
    return (this->m_parentImg == cmp.parentImg()    &&
            this->takenX() == cmp.takenX()          &&
            this->takenY() == cmp.takenY()          &&
            this->width() == cmp.width()            &&
            this->height() == cmp.height());
}

bool Frame::operator==(ALLEGRO_BITMAP* cmp) const
{
    return (this->m_parentImg == cmp                    &&
            this->takenX() == 0                         &&
            this->takenY() == 0                         &&
            this->width() == al_get_bitmap_width(cmp)   &&
            this->height() == al_get_bitmap_height(cmp));
}

void Frame::draw(double destx, double desty)
{
    al_draw_bitmap(m_sprite, destx, desty, 0);
}


