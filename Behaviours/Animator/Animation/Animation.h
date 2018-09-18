#ifndef ANIMATION_H
#define ANIMATION_H

#include <istream>

class Shadow;
class Frame;

class Animation
{
    friend class Shadow;

    protected:

        //pointer to the shadow of this animation, if there is one
//        Shadow* m_shadow;

        //the lapse of time to wait between each frame
        //might wanna make this unique to each direction...
        double m_lapse;

    public:
        Animation();
        virtual ~Animation();

        ///loads every frame of the anymation & others from the stream
        virtual std::istream& getFromStream(std::istream& theStream);

        ///the number of frames of the animation (for the current direction)
        virtual unsigned nbFrames() = 0;

        //just draws at x, y on the current target bitmap
        virtual void draw(double destx, double desty, unsigned frameNumber);

        ///the current sprite to render
        virtual Frame* getFrame(unsigned frameNumber) = 0;

        ///set the direction. Will chose the closest available if there are no frames for val direction
        virtual void setDirection(double orientation) { }

//        Shadow* shadow() { return m_shadow; }
//        void setShadow(Shadow* val) { m_shadow = val; }


        //make this return the lapse for the current direction if you separate them
        ///the lapse of time to wait between every frame
        virtual double lapse() const { return m_lapse; }
        virtual void setLapse(double val) { if (val>0) m_lapse = val;}
};

inline std::istream& operator>>(std::istream& theStream, Animation& recept)
{
    return recept.getFromStream(theStream);
}

#endif // ANIMATION_H
