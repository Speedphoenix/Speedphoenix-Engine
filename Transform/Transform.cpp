#include "Transform.h"

#include "GameContainer.h"

using namespace std;


Transform::Transform(double _x, double _y, double _w, double _h, bool _moving, double _speed, double _orientation)
    :TransformBase(_x, _y, _speed, _orientation, _moving), m_w(_w), m_h(_h)
{
    // calcCompos() is called in the parent (TransformBase) class
}

Transform::Transform(double _x, double _y, double _w, double _h, double _dx, double _dy, bool _moving)
    :TransformBase(_x, _y, _dx, _dy, _moving), m_w(_w), m_h(_h)
{
    // calcOrientation() is called in the parent (TransformBase) class
}


Transform::Transform(TransformBase *_parent, double _x, double _y, double _w, double _h)
    :TransformBase(_parent, _x, _y), m_w(_w), m_h(_h)
{

}

Transform::Transform(const Transform& source, TransformBase* newParent)
    :TransformBase(source), m_w(source.width()), m_h(source.height())
{
    this->setParent(newParent);
}

Transform::~Transform()
{
    //dtor
}



void Transform::blockBorder()
{
    GameContainer& container = *GameContainer::instance();

    if (absX() < 0)
        setAbsX(0);
    else if (endAbsX() > container.maximumX())
        setAbsX(container.maximumX() - m_w);

    if (absY() < 0)
        setAbsY(0);
    else if (endAbsY() > container.maximumY())
        setAbsY(container.maximumY() - m_h);
}

