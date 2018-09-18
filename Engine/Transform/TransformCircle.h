#ifndef TRANSFORMCIRCLE_H
#define TRANSFORMCIRCLE_H

#include <TransformBase.h>

class GameContainer;
class Transform;

///a circular transform
class TransformCircle : public TransformBase
{
    friend class TransformBase;

    protected:
        double m_radius;

    //funcs
    protected:
        //stops from going out-of bounds
        virtual void blockBorder();

    public:
        TransformCircle(double _x = 0, double _y = 0, double _radius = 0, bool _moving = false, double _speed = 0, double _orientation = 0);
        TransformCircle(double _x, double _y, double _radius, double _dx, double _dy, bool _moving = false);
        TransformCircle(TransformBase *_parent, double _x = 0, double _y = 0, double _radius = 0);
        TransformCircle(const TransformCircle& source, TransformBase* newParent = nullptr);

        virtual ~TransformCircle();

        virtual Transform getBox();

        virtual bool isInside(const TransformCircle& container) const { return TransformBase::isInside(*this, container); }
        virtual bool isInside(const Transform& container) const { return TransformBase::isInside(*this, container); }
        virtual bool touches(const TransformCircle& other) const { return TransformBase::touches(*this, other); }
        virtual bool touches(const Transform& other) const { return TransformBase::touches(*this, other); }

        //always use these functions for the circle (instead of m_x and m_y)
        virtual double centerX() const { return m_x + m_radius; }
        virtual double centerY() const { return m_y + m_radius; }
        virtual void setCenterX(double val) { m_x = val - m_radius; }
        virtual void setCenterY(double val) { m_y = val - m_radius; }

        double radius() const { return m_radius; }
        void SetRadius(double val) { m_radius = val; }
};

#endif // TRANSFORMCIRCLE_H
