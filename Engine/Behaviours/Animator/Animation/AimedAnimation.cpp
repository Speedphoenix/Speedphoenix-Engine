#include "AimedAnimation.h"
#include "Frame.h"

#include "basic_ops.h"

AimedAnimation::AimedAnimation()
	:Animation(), m_currDirection(0.0)
{
	//ctor
}

AimedAnimation::AimedAnimation(ALLEGRO_BITMAP* sheet,
								int x, int y, int w, int h, int nb)
	:Animation(), m_currDirection(0.0)
{
	createFromSheet(sheet, y, x, w, h, nb);
}

AimedAnimation::~AimedAnimation()
{
	clearFrames();
}

void AimedAnimation::createFromSheet(ALLEGRO_BITMAP *sheet,
								int x, int y, int w, int h, int nb)
{
	if (nb <= 0)
		return ;
	clearFrames();

	for (int i = 0;i < nb;i++)
		m_frames.push_back(new Frame(sheet, x + (i * w), y, w, h));
}

void AimedAnimation::addFrames(ALLEGRO_BITMAP *sheet,
								int x, int y, int w, int h, int nb)
{
	for (int i = 0;i < nb;i++)
		m_frames.push_back(new Frame(sheet, x + (i * w), y, w, h));
}

void AimedAnimation::clearFrames()
{
	for (const auto& elem : m_frames)
		delete elem;
	m_frames.clear();
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

void AimedAnimation::draw(double destx, double desty, unsigned frameNumber)
{
	this->getFrame(frameNumber)->draw(destx, desty, m_currDirection);
}

///set the direction. Will chose the closest available if there are no frames for val direction
void AimedAnimation::setDirection(double orientation)
{
	m_currDirection = mod2PI(orientation);
}

