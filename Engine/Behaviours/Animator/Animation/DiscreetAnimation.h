#ifndef DISCREETANIMATION_H
#define DISCREETANIMATION_H

#include <Animation.h>

#include <map>
#include <vector>

class Shadow;
class Frame;

//to scope the Directions (that have short names) without using an enum class
namespace Direc {

    //make it unsigned to make sure when comparing, or when making an array (of size State::none)
    enum Direction : unsigned{
        E,  // East, to the right
        NE, // North East
        N,  // North, towards the top
        NW, // North West
        W,  // West, to the left
        SW, // South West
        S,  // South, towards the bottom
        SE, // South East

        none //for when none of the directions are available
    };
}

class DiscreetAnimation : public Animation
{
    ///FOR TESTING PURPOSES
    public:
        void maketest(int type = 0);

    protected:
        //all the frames of all animations
        std::map<Direc::Direction, std::vector<Frame*>> m_frames;

        //the corrent direction of the animations
        Direc::Direction m_currDirection;

        ///Returns the available direction closest to the input direction 'depending'
        Direc::Direction getBestDirection(Direc::Direction depending = Direc::E);

    public:
        DiscreetAnimation();
        virtual ~DiscreetAnimation();


        ///the number of frames of the animation for the current direction
        virtual unsigned nbFrames();


        ///the current sprite to render
        virtual Frame* getFrame(unsigned frameNumber);


        virtual Direc::Direction currDirection() const { return m_currDirection; }

        ///set the direction. Will chose the closest available if there are no frames for val direction
        virtual void setDirection(Direc::Direction val);
        virtual void setDirection(double orientation);

//        Shadow* shadow() { return m_shadow; }
//        void setShadow(Shadow* val) { m_shadow = val; }


        //could want to override the lapse() and setlapse() functions
        //make this return the lapse for the current direction if you separate them
        ///the lapse of time to wait between every frame
};

#endif // DISCREETANIMATION_H
