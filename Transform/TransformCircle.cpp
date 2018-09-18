#include "TransformCircle.h"

#include "Transform.h"

#include "GameContainer.h"

TransformCircle::TransformCircle(double _x, double _y, double _radius, bool _moving, double _speed, double _orientation)
    :TransformBase(_x, _y, _speed, _orientation, _moving), m_radius(_radius)
{
    // calcCompos() is called in the parent (TransformBase) class
}

TransformCircle::TransformCircle(double _x, double _y, double _radius, double _dx, double _dy, bool _moving)
    :TransformBase(_x, _y, _dx, _dy, _moving), m_radius(_radius)
{
    // calcOrientation() is called in the parent (TransformBase) class
}


TransformCircle::TransformCircle(TransformBase *_parent, double _x, double _y, double _radius)
    :TransformBase(_parent, _x, _y), m_radius(_radius)
{

}

TransformCircle::TransformCircle(const TransformCircle& source, TransformBase* newParent)
    :TransformBase(source, newParent), m_radius(source.radius())
{

}

TransformCircle::~TransformCircle()
{

}
Transform TransformCircle::getBox()
{
    return Transform(m_x, m_y, 2*m_radius, 2*m_radius);
}

void TransformCircle::blockBorder()
{
    GameContainer& container = *GameContainer::instance();

    if (absX() < 0)
        setAbsX(0);
    else if ((absX() + 2*m_radius) > container.maximumX())
        setAbsX(container.maximumX() - 2*m_radius);

    if (absY() < 0)
        setAbsY(0);
    else if ((absY() + 2*m_radius) > container.maximumY())
        setAbsY(container.maximumY() - 2*m_radius);
}

