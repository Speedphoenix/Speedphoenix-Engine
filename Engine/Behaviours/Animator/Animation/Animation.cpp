#include "Animation.h"

#include "SpritesContainer.h"

#include "allegroImplem.h"
#include "debugNerrors.h"

#include "Frame.h"

using namespace std;

//only default, will need to use a real one later
Animation::Animation(double _lapse)
	:m_lapse(_lapse)
{
	//ctor
}

Animation::~Animation()
{
	//dtor
}

std::istream& Animation::getFromStream(std::istream& theStream)
{
	return theStream;
}

//we can later make it so that instead of separate bitmaps, we take part of one bigger bitmap, for performance
void Animation::draw(double destx, double desty, unsigned frameNumber)
{
	this->getFrame(frameNumber)->draw(destx, desty);
}

