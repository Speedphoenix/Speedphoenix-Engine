#include "AimedAnimation.h"

#include "basic_ops.h"

AimedAnimation::AimedAnimation()
    :Animation(), m_currDirection(0.0)
{
    //ctor
}

AimedAnimation::~AimedAnimation()
{
    //dtor
}

///the number of frames of the animation for the current direction
unsigned AimedAnimation::nbFrames()
{
    return m_frames.size();
}

///the current sprite to render
Frame* AimedAnimation::getFrame(unsigned frameNumber)
{
    return m_frames.at(frameNumber);
}

///set the direction. Will chose the closest available if there are no frames for val direction
void AimedAnimation::setDirection(double orientation)
{
    m_currDirection = mod2PI(orientation);
}

