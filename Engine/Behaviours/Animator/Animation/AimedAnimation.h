#ifndef AIMEDANIMATION_H
#define AIMEDANIMATION_H

#include <Animation.h>

#include <vector>

class Frame;

class AimedAnimation : public Animation
{
    protected:
        double m_currDirection;

        std::vector<Frame*> m_frames;

    public:
        AimedAnimation();
        virtual ~AimedAnimation();


        ///the number of frames of the animation for the current direction
        virtual unsigned nbFrames();

        ///the current sprite to render
        virtual Frame* getFrame(unsigned frameNumber);

        virtual double currDirection() const { return m_currDirection; }

        ///set the direction. Will chose the closest available if there are no frames for val direction
        virtual void setDirection(double orientation);
};

#endif // AIMEDANIMATION_H
