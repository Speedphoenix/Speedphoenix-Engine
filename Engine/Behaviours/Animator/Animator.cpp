#include "Animator.h"

#include "TransformBase.h"
#include "GameObject.h"
#include "Camera.h"
#include "Frame.h"

#include "allegroImplem.h"
#include "debugNerrors.h"
#include "colors.h"

#include "basic_ops.h"

using namespace std;

Animator::Animator(GameObject* attachTo, double lapse, GeneralState startState, double startDirection)
	:Behaviour(attachTo), Drawable(), m_currFrame(0), m_currState(startState, Anim::Idle, false), m_askedState(startState, Anim::Idle), m_askedDir(startDirection)
{
	m_timer = al_create_timer(lapse);

	m_queue = al_create_event_queue();

	//THE TIMER IS NOT STARTED YET HERE
	al_register_event_source(m_queue, al_get_timer_event_source(m_timer));
}

Animator::~Animator()
{
	al_destroy_timer(m_timer);
	al_destroy_event_queue(m_queue);
	for (const auto& elem : m_animations)
		delete elem.second;
}

//Animator::Animator(const Animator& other)
//{
//	  //copy ctor
//}
//
//Animator& Animator::operator=(const Animator& rhs)
//{
//	  if (this == &rhs) return *this; // handle self assignment
//
//
//	  //assignment operator
//	  return *this;
//}

void Animator::setNewLapse()
{
	double newLapse = m_animations.at(m_currState)->lapse();
	//set the right lapse for the new animation
	//this comparison of floating point is safe since it was only set
	//from a definite value, no operations were made on it.
	if (al_get_timer_speed(m_timer) != newLapse)
		al_set_timer_speed(m_timer, newLapse);
}

//change these two functions if you really want to add a transition between Active and Idle
void Animator::makeActive(bool playOnce)
{
	//if it has to change
	if (m_currState.to.animType!=Anim::Active)
	{
		//change the asked state
		m_askedState.animType = Anim::Active;

		State inter(getBestState(m_animations, Anim::Active, m_askedState).genState, Anim::Active);

		m_currState.setState(inter);
		m_currFrame = 0;

		setNewLapse();
	}
	m_currState.playOnce = playOnce;
}

void Animator::makeIdle()
{
	//if it changed
	if (m_currState.to.animType!=Anim::Idle)
	{
		//change the asked state
		m_askedState.animType = Anim::Idle;

		m_currState.setType(Anim::Idle, false);
		m_currFrame = 0;

		//there might be an Idle, but not an Active, or the other way 'round
		State inter = getBestState(m_animations, Anim::Idle, m_askedState);
		m_currState.from = inter;
		m_currState.to = inter;

		setNewLapse();
		m_animations.at(m_currState)->setDirection(m_askedDir);
	}
}

void Animator::setState(State what, bool shouldChangeDirec)
{
	if (what==m_askedState)
		return;

	//this will be the from state
	m_currState.setState(m_askedState);

	m_askedState = what;
	m_askedState.blockTransitionType(); //to make sure it doesn't have transision as animType

	//we're starting a transition. The from State should be the old state (even if it was a transition itself)
	m_currState.setChange(getBestState(m_animations, m_askedState.animType, m_askedState), false);

	//if the transition animation doesn't exist
	if (!m_animations.count(m_currState))
	{
		m_currState.finishTransition();

		m_currState.animType = Anim::Idle;
	}

	m_currFrame = 0;

	if (shouldChangeDirec)
		m_animations.at(m_currState)->setDirection(m_askedDir);
	setNewLapse();
}

void Animator::setState(State what, double direction)
{
	setState(what, false);
	setDirection(direction);
}

void Animator::setState(State what, const TransformBase& direction)
{
	setState(what, false);
	setDirection(direction);
}

void Animator::setDirection(double direction)
{
	direction = mod2PI(direction);
	if (sameAngle(direction, m_askedDir))
		return ;
	
	m_askedDir = direction;

	m_animations.at(m_currState)->setDirection(m_askedDir);
}

void Animator::setDirection(const TransformBase& direction)
{
	setDirection(direction.orientation());
}

void Animator::draw()
{
	const TransformBase& where = this->attachedObject()->transform();
	const Transform& camera = Camera::getCurrentView();

	if (where.touches(camera))
	{
		double relx = 0, rely = 0;
		where.getRelativeCoords(camera, relx, rely);
		m_animations.at(m_currState)->draw(relx, rely, m_currFrame);
	}
}

void Animator::start()
{
	this->launch();
}

void Animator::launch()
{
	setNewLapse();
	al_start_timer(m_timer);
	m_ready = true;
}

void Animator::stop()
{
	al_stop_timer(m_timer);
	m_ready = false;
}

void Animator::update()
{
	ALLEGRO_EVENT retEvent;

	while (al_get_next_event(m_queue, &retEvent))
	{
		m_currFrame++;

		if (m_currFrame >= m_animations.at(m_currState)->nbFrames())
		{
			m_currFrame = 0;

			//if we finished a playOnce animation
			if (m_currState.playOnce)
			{
				if (m_currState.animType == Anim::Transition)
				{
					m_currState.finishTransition();
				}
				else
				{
					if (m_askedState.animType == Anim::Idle)
					{
						///return here to the backToState....
						m_currState.playOnce = false;
						m_currState.toPlayOnce = false;
					}
					else
					{
						State inter = m_askedState;
						inter.animType = Anim::Idle;

						setState(inter);
					}
				}
			}
		}
	}
}

void Animator::postUpdate()
{
	if (m_animations.at(m_currState)->aimedDirection() != m_askedDir)
		m_animations.at(m_currState)->setDirection(m_askedDir);
}

ALLEGRO_BITMAP* Animator::getImg()
{
	return m_animations.at(m_currState)->getFrame(m_currFrame)->sprite();
}

void Animator::setCurrFrame(unsigned val)
{
	if (val >= m_animations.at(m_currState)->nbFrames())
		m_currFrame = 0;
	else
		m_currFrame = val;
}



//below this is to choose the right state depending on available ones


//to not rewrite it everytime....
#define CHECK(x)					\
keyIdx.from = State(x, animType);	\
keyIdx.to = State(x, animType);		\
if (theMap.count(keyIdx)) return x;

//check dans l'ordre
#define CHECKORDER(_1, _2, _3, _4, _5, _6)	\
CHECK(_1)									\
else CHECK(_2)								\
else CHECK(_3)								\
else CHECK(_4)								\
else CHECK(_5)								\
else CHECK(_6)								\
else return none;

//returns the best direction
State Animator::getBestState(const std::map<Transition, Animation*>& theMap, Anim::AnimType animType, State depending)
{
	if (theMap.empty())
		return none;

	Transition keyIdx;
	keyIdx.animType = animType;

	CHECK(depending.genState) //should usually stop here

	switch (depending.genState)
	{
		case Walking:
		CHECKORDER(Crouching, TipToes, Attacking, Burning, Dying, Swimming)
	break;

		case Crouching:
		CHECKORDER(Walking, TipToes, Attacking, Burning, Dying, Swimming)
	break;

		case TipToes:
		CHECKORDER(Walking, Crouching, Attacking, Burning, Dying, Swimming)
	break;

		case Attacking:
		CHECKORDER(Burning, Walking, Crouching, TipToes, Dying, Swimming)
	break;

		case Swimming:
		CHECKORDER(Crouching, Attacking, Walking, TipToes, Dying, Burning)
	break;

		case Dying:
		CHECKORDER(Burning, Crouching, Swimming, Walking, TipToes, Attacking)
	break;

		case Burning:
		CHECKORDER(Dying, Crouching, Walking, Attacking, TipToes, Swimming)
	break;

		default:
		case none:
		return getBestState(theMap, animType, Walking);
	break;
	}
}

#undef CHECK
#undef CHECKORDER

