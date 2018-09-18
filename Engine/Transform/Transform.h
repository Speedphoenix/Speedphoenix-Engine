#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <TransformBase.h>

class GameContainer;

class TransformCircle;

///a rectangular transform
class Transform : public TransformBase
{
    //technically not necessary
    friend class TransformBase;

    protected:
        double m_w; //!< width
        double m_h; //!< height

    //methods
    protected:
        //stops from going out-of bounds
        virtual void blockBorder();

    public:
        Transform(double _x = 0, double _y = 0, double _w = 0, double _h = 0, bool _moving = false, double _speed = 0, double _orientation = 0);
        Transform(double _x, double _y, double _w, double _h, double _dx, double _dy, bool _moving = false);
        Transform(TransformBase *_parent, double _x = 0, double _y = 0, double _w = 0, double _h = 0);
        Transform(const Transform& source, TransformBase* newParent = nullptr);

        virtual ~Transform();

        virtual bool isInside(const TransformCircle& container) const { return TransformBase::isInside(*this, container); }
        virtual bool isInside(const Transform& container) const { return TransformBase::isInside(*this, container); }
        virtual bool touches(const TransformCircle& other) const { return TransformBase::touches(*this, other); }
        virtual bool touches(const Transform& other) const { return TransformBase::touches(*this, other); }

        virtual double centerX() const { return m_x + m_w/2; }
        virtual double centerY() const { return m_y + m_h/2; }
        virtual void setCenterX(double val) { m_x = val - m_w/2; }
        virtual void setCenterY(double val) { m_y = val - m_h/2; }

        //bottom right corner of the transform
        virtual double endX() const { return m_x + m_w; }
        virtual double endY() const { return m_y + m_h; }
        virtual void setEndX(double val) { m_x = val - m_w; }
        virtual void setEndY(double val) { m_y = val - m_h; }

        virtual double endAbsX() const { return m_x + m_w + (m_parent?m_parent->centerAbsX():0); }
        virtual double endAbsY() const { return m_y + m_h + (m_parent?m_parent->centerAbsY():0); }
        virtual void setEndAbsX(double val) { setEndAbsX(val - (m_parent?m_parent->centerAbsX():0)); }
        virtual void setEndAbsY(double val) { setEndAbsY(val - (m_parent?m_parent->centerAbsY():0)); }

        double width() const { return m_w; }
        void setWidth(double val) { m_w = val; }
        double height() const { return m_h; }
        void setHeight(double val) { m_h = val; }
        void setDim(double _w, double _h) { m_w = _w; m_h = _h; }
};

#endif // TRANSFORM_H
