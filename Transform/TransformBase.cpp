#include "TransformBase.h"
#include "Transform.h"
#include "TransformCircle.h"

#include "GameContainer.h"

#include "config.h"
#include "basic_ops.h"
#include "debugNerrors.h"

#include <cmath>

using namespace std;


TransformBase::TransformBase(double _x, double _y, bool _moving, double _speed, double _orientation)
    :m_x(_x), m_y(_y), m_speed(_speed), m_orientation(_orientation), m_moving(_moving)
{
    //dx and dy are calculated in here based on the orientation and the speed
    calcCompos();
}

TransformBase::TransformBase(double _x, double _y, double _dx, double _dy, bool _moving)
    :m_x(_x), m_y(_y), m_dx(_dx), m_dy(_dy), m_moving(_moving)
{
    //the orientation and the speed are calculated in here based on dx and dy
    calcOrientation();
}


TransformBase::TransformBase(TransformBase *_parent, double _x, double _y)
    :TransformBase(_x, _y, false)
{
    m_parent = _parent;
}


TransformBase::TransformBase(const TransformBase& source, TransformBase* newParent)
    :m_x(source.x()), m_y(source.y()), m_speed(source.m_speed), m_orientation(source.m_orientation),
        m_dx(source.m_dx), m_dy(source.m_dy), m_moving(source.m_moving), m_parent(newParent)
{

}


TransformBase::~TransformBase()
{
    //dtor
}

bool TransformBase::hasSamePos(const TransformBase& other)
{
    return ((ABS(this->centerAbsX() - other.centerAbsX()) < negligibleDistance) &&
            (ABS(this->centerAbsY() - other.centerAbsY()) < negligibleDistance) );
}


void TransformBase::getRelativeCoords(const TransformBase& baseOrigin, double& relX, double& relY)
{
    relX = this->absX() - baseOrigin.absX();
    relY = this->absY() - baseOrigin.absY();
}


void TransformBase::translate(double factor)
{
    if (!m_moving)
        return;

    m_x += m_dx*factor;
    m_y += m_dy*factor;

    blockBorder();
}

void TransformBase::headTowards(const TransformBase& where, double speedLimit)
{
    headTowards(where.centerAbsX(), where.centerAbsY(), speedLimit);
}

//make this work if translate() receives a factor > 1 too
void TransformBase::headTowards(double _x, double _y, double speedLimit)
{
    double newdx = _x - centerAbsX();
    double newdy = _y - centerAbsY();

    bool needRecalc = false;

    //no use calculating anything
    if ((ABS(newdx) < negligibleDistance) && (ABS(newdy) < negligibleDistance))
    {
        m_dx = 0.0;
        m_dy = 0.0;

        m_speed = 0;

        m_moving = false;

        return;
    }

    //to see if the orientation is different
    if (XOR(newdx == 0, m_dx == 0))
    {
        needRecalc = true;
    }
    else if (XOR(newdy == 0, m_dy == 0))
    {
        needRecalc = true;
    }
    else if ((newdx == 0 && m_dx == 0) || (newdy == 0 && m_dy == 0))
    {
        needRecalc = false;
    }
    else
    {
        if ((newdx / newdy) == (m_dx / m_dy))
            needRecalc = false;
        else
            needRecalc = true;
    }

    if (needRecalc)
    {

        m_dx = newdx;       //could do these lines with setDiff(newdx, newdy);
        m_dy = newdy;       //but left them for clarity

        calcOrientation();

        if (m_speed > speedLimit)
        {
            setSpeed(speedLimit);
        }
    }
    else
    {
        double newSQspeed = (SQ(newdx) + SQ(newdy));

        //if we need to tone down the speed
        if (newSQspeed > SQ(speedLimit) )
        {
            double factor = speedLimit/sqrt(newSQspeed);

            m_dx = newdx * factor;
            m_dy = newdy * factor;

            m_speed = speedLimit;
        }
        else
        {
            m_dx = newdx;
            m_dy = newdy;

            m_speed = sqrt(newSQspeed);
        }
    }
}


void TransformBase::calcCompos()
{
    m_dx = m_speed * cos(m_orientation);
    m_dy = m_speed * sin(m_orientation);
}

void TransformBase::calcOrientation()
{
    m_speed = getDist(m_dx, m_dy, 0, 0);

    m_orientation = acos(m_dx/m_speed);
}


double TransformBase::getSQDist(double x2, double y2) const
{
    return ( SQ(this->centerAbsX() - x2) + SQ(this->centerAbsY() - y2) );
}

double TransformBase::getSQDist(const TransformBase& other) const
{
    return getSQDist(other.centerAbsX(), other.centerAbsY());
}

double TransformBase::getSQDist(const TransformBase& first, const TransformBase& second)
{
    return first.getSQDist(second);
}

double TransformBase::getSQDist(double x1, double y1, double x2, double y2)
{
    return ( SQ(x1 - x2) + SQ(y1 - y2) );
}


double TransformBase::getDist(double x2, double y2) const
{
    return sqrt(getSQDist(x2, y2));
}

double TransformBase::getDist(const TransformBase& other) const
{
    return sqrt(getSQDist(other));
}

double TransformBase::getDist(const TransformBase& first, const TransformBase& second)
{
    return first.getDist(second);
}

double TransformBase::getDist(double x1, double y1, double x2, double y2)
{
    return sqrt(getSQDist(x1, y1, x2, y2));
}

void TransformBase::setParent(TransformBase *val)
{
    double _x = absX();
    double _y = absY();

    m_parent = val;

    setAbsX(_x);
    setAbsY(_y);
}

void TransformBase::blockBorder()
{
    GameContainer& container = *GameContainer::instance();

    if (absX() < 0)
        setAbsX(0);
    else if (absX() > container.maximumX())
        setAbsX(container.maximumX());

    if (absY() < 0)
        setAbsY(0);
    else if (absY() > container.maximumY())
        setAbsY(container.maximumY());
}


//two rectangles
bool TransformBase::isInside(const Transform& contained, const Transform& container)
{
    if (contained.absX() >= container.absX() &&
        contained.endAbsX() <= container.endAbsX() &&
        contained.absY() >= container.absY() &&
        contained.endAbsY() <= container.endAbsY())
    {
        return true;
    }
    else
    {
        return false;
    }
}

//two circles
bool TransformBase::isInside(const TransformCircle& contained, const TransformCircle& container)
{
    double SQDist = getSQDist(contained, container);

    // if we're way out of range we can stop right here (without using a sqrt)
    if (SQDist > SQ(container.radius()))
        return false;

    return ((sqrt(SQDist) + contained.radius()) <= container.radius());
}

//circle in rect
bool TransformBase::isInside(const TransformCircle& contained, const Transform& container)
{
    double distX = ABS(contained.centerAbsX() - container.centerAbsX());
    double distY = ABS(contained.centerAbsY() - container.centerAbsY());

    return ( (distX + contained.radius()) < (container.width()/2) ) &&
           ( (distY + contained.radius()) < (container.height()/2) );
}

//rect in circle
bool TransformBase::isInside(const Transform& contained, const TransformCircle& container)
{
    //check that every corner of the rect is inside the circle
    if (getSQDist(contained.absX(), contained.absY(), container.centerAbsX(), container.centerAbsY()) < SQ(container.radius()) &&
        getSQDist(contained.endAbsX(), contained.absY(), container.centerAbsX(), container.centerAbsY()) < SQ(container.radius()) &&
        getSQDist(contained.absX(), contained.endAbsY(), container.centerAbsX(), container.centerAbsY()) < SQ(container.radius()) &&
        getSQDist(contained.endAbsX(), contained.endAbsY(), container.centerAbsX(), container.centerAbsY()) < SQ(container.radius()) )
    {
        return true;
    }

    return false;
}

bool TransformBase::touches(const Transform& first, const Transform& second)
{
    if ( ( (first.absX() > second.absX() && first.absX() < second.endAbsX())    ||
            (first.endAbsX() > second.absX() && first.endAbsX() < second.endAbsX()) ) &&
        ( (first.absY() > second.absY() && first.absY() < second.endAbsY())     ||
            (first.endAbsY() > second.absY() && first.endAbsY() < second.endAbsY()) ) )
    {
        return true;
    }
    else
        return second.isInside(first);
}


//two circles
bool TransformBase::touches(const TransformCircle& first, const TransformCircle& second)
{
    return ( getSQDist(first, second) <= SQ(first.radius() + second.radius()) );
}

//one rect and one circle
//thanks to https://stackoverflow.com/a/402010/7207370
bool TransformBase::touches(const Transform& first, const TransformCircle& second)
{
    double distX = ABS(first.centerAbsX() - second.centerAbsX());
    double distY = ABS(first.centerAbsY() - second.centerAbsY());

    if (distX > (second.radius() + first.width()/2))
        return false;
    if (distY > (second.radius() + first.height()/2))
        return false;

    if (distX <= first.width()/2)
        return true;
    if (distY <= first.height()/2)
        return true;

    double SQCornerDist (SQ(distX - first.width()/2) + SQ(distY - first.height()/2));

    return SQCornerDist <= SQ(second.radius());
}


bool TransformBase::isInside(const Transform& container)
{
    return (absX() >= container.absX() && absX() <= container.endAbsX() &&
            absY() >= container.absY() && absY() <= container.endAbsY() );
}

bool TransformBase::isInside(const TransformCircle& container)
{
    return (getSQDist(container) <= SQ(container.radius()));
}

bool TransformBase::touches(const Transform& other)
{
    //since it's just a point
    return isInside(other);
}

bool TransformBase::touches(const TransformCircle& other)
{
    //since it's just a point
    return isInside(other);
}


void TransformBase::setSpeed(double val)
{
    double oldSpeed = m_speed;

    m_speed = val;

    if (oldSpeed == 0)
    {
        calcCompos();
    }
    else //no need to redo sin() and cos() calls
    {
        double factor = val/oldSpeed;

        m_dx *= factor;
        m_dy *= factor;
    }
}


