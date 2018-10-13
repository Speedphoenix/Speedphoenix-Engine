#include "DiscreetAnimation.h"

#include "Frame.h"
#include "debugNerrors.h"

#include "basic_ops.h"


using namespace std;

//only default, will need to use a real one later
DiscreetAnimation::DiscreetAnimation()
	:Animation(), m_currDirection(Direc::E)
{
	//ctor
}

DiscreetAnimation::~DiscreetAnimation()
{
	for (const auto& dir : m_frames)
	{
		for (const auto& elem : dir.second)
			delete elem;
	}
}

unsigned DiscreetAnimation::nbFrames()
{
	if (m_frames.count(m_currDirection))
		return m_frames.at(m_currDirection).size();
	else
		return 0;
}

Frame* DiscreetAnimation::getFrame(unsigned frameNumber)
{
	vector<Frame*>& inter = m_frames.at(m_currDirection);

	if (frameNumber < inter.size())
		return inter.at(frameNumber);
	else if (inter.size()!=0)
		return inter.at(inter.size() - 1);	//replace this by inter.at(0); to take the first frame instead
	else
		return nullptr;
}

void DiscreetAnimation::setDirection(Direc::Direction val)
{
	m_currDirection = getBestDirection(val);
}

void DiscreetAnimation::setDirection(double orientation)
{
	orientation = mod2PI(orientation);

	//M_2_PI is 2/PI, defined in math.h
	//offset the orientation by 1/2 to have good intervals
	int lookAt = (int) ((orientation * 2 * M_2_PI) + 1/2); // (orientation * 8 / (2*PI)) + 1/2

	//the interval 8-8.5 belongs in 0
	//also to take care of bugs...
	if (lookAt >= 8 || lookAt < 0)
		lookAt = 0;

	setDirection((Direc::Direction) lookAt); // cast into the enum
}


//below this is to choose a direction depending on the available ones

///TO BE RE-DONE

using namespace Direc;

//to not rewrite it everytime....
#define CHECK(x) if (m_frames.count(x)) return x;

//check dans l'ordre
#define CHECKORDER(_1, _2, _3, _4, _5, _6, _7)	\
CHECK(_1)										\
else CHECK(_2)									\
else CHECK(_3)									\
else CHECK(_4)									\
else CHECK(_5)									\
else CHECK(_6)									\
else CHECK(_7)									\
else return none;

//returns the best direction
Direction DiscreetAnimation::getBestDirection(Direction depending)
{
	if (m_frames.empty())
		return none;

	CHECK(depending) //usually stops here

	switch (depending)
	{
		case N:
		CHECKORDER(NE, NW, E, W, S, SE, SW)
	break;

		case S:
		CHECKORDER(SE, SW, E, W, NE, NW, N)
	break;

		case E:
		CHECKORDER(SE, NE, S, N, SW, NW, W)
	break;

		case W:
		CHECKORDER(SW, NW, N, S, NE, SE, E)
	break;

		case NE:
		CHECKORDER(E, SE, N, S, NW, W, SW)
	break;

		case NW:
		CHECKORDER(W, SW, N, S, NE, E, SE)
	break;

		case SE:
		CHECKORDER(E, NE, S, N, SW, W, NW)
	break;

		case SW:
		CHECKORDER(W, NW, S, N, SE, E, NE)
	break;

		default:
		case none:
		CHECK(E)
		else CHECKORDER(W, S, N, SE, SW, NE, NW)
	break;
	}
}

#undef CHECK
#undef CHECKORDER

