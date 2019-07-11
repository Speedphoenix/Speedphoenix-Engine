#include "GameContainer.h"

#include "GameObject.h"
#include "Behaviour.h"
#include "Drawable.h"
#include "Events.h"
#include "Camera.h"

#include "allegroImplem.h"
#include "colors.h"

#include "debugNerrors.h"


using namespace std;

GameContainer * GameContainer::m_instance = nullptr;


GameContainer::GameContainer()
	:m_deltaTime(0), m_finished(false)
{
	if (m_instance!=nullptr)
		throw "A game container already exists";

	m_instance = this;

	//putting this outside the initialization list because it needs the instance
	m_globalObject = new GameObject();

	m_eventsDisplay = al_create_event_queue();
	al_register_event_source(m_eventsDisplay, al_get_display_event_source(currentDisplay));

	m_eventsKeyboard = al_create_event_queue();
	al_register_event_source(m_eventsKeyboard, al_get_keyboard_event_source());

	m_eventsMouse = al_create_event_queue();
	al_register_event_source(m_eventsMouse, al_get_mouse_event_source());

	m_eventsTouch = al_create_event_queue();
	if (al_is_touch_input_installed())
	{
		al_register_event_source(m_eventsTouch, al_get_touch_input_event_source());
	}
}

GameContainer::~GameContainer()
{
	al_destroy_event_queue(m_eventsDisplay);
	al_destroy_event_queue(m_eventsKeyboard);
	al_destroy_event_queue(m_eventsMouse);
	al_destroy_event_queue(m_eventsTouch);

	for (auto& elem : m_objects)
		elem->setToRemove();
	autoRemove();
	m_instance = nullptr;
}

void GameContainer::initAll()
{
	// can't use range-based for here as
	// the start functions might add in more objects
	list<GameObject*>::iterator it1;
	list<Behaviour*>::iterator it2;
	list<Drawable*>::iterator it3;

	// PUT THIS IN A LOOP TO PROPERLY GET THE OBJECTS CREATED IN THE BEHAVIOUR'S START
	// MAYBE HAVE TWO LISTS FOR EACH, TO BUFFERIZE IT WELL?
	for (it1 = m_newObjects.begin();it1 != m_newObjects.end();it1++)
	{
		(*it1)->start();
		m_objects.insert(*it1);
	}
	m_newObjects.clear();

	for (it2 = m_newBehaviours.begin();it2 != m_newBehaviours.end();it2++)
	{
		(*it2)->start();
		m_behaviours.insert(*it2);
	}
	m_newBehaviours.clear();

	for (it3 = m_newDrawables.begin();it3 != m_newDrawables.end();it3++)
	{
		m_drawables.insert(*it3);
	}
	m_newDrawables.clear();
}

void GameContainer::start()
{
	this->init();
	initAll();
}


///MAKE A STRUCT/CLASS FOR ACTIONS (DIFFERENT EVENTS CAN TRIGGER THE SAME ACTION), AND USE THAT.
///to make it easier to eventually have multiple players (online? AI? split screen?)
//for events:
//https://allegro.developpez.com/5/livre/?page=page_6
void GameContainer::eventCatch()
{
	ALLEGRO_EVENT event = {0};

	//not directly using al_get_next event in case we need to just peek?
	while (!al_is_event_queue_empty(m_eventsDisplay))
	{
		al_get_next_event(m_eventsDisplay, &event);
		switch (event.type)
		{
			case ALLEGRO_EVENT_DISPLAY_EXPOSE:
			case ALLEGRO_EVENT_DISPLAY_RESIZE:
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
			case ALLEGRO_EVENT_DISPLAY_LOST:
			case ALLEGRO_EVENT_DISPLAY_FOUND:
			case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
			case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
			case ALLEGRO_EVENT_DISPLAY_ORIENTATION:

		break;

			default:
		break;
		}
	}

	while (!al_is_event_queue_empty(m_eventsKeyboard))
	{
		al_get_next_event(m_eventsKeyboard, &event);
		switch (event.type)
		{
			case ALLEGRO_EVENT_KEY_DOWN:
			case ALLEGRO_EVENT_KEY_CHAR:
			case ALLEGRO_EVENT_KEY_UP:

			onKeyboardEvent(event);

		break;

			default:
		break;
		}
	}

	while (!al_is_event_queue_empty(m_eventsMouse))
	{
		al_get_next_event(m_eventsMouse, &event);
		switch (event.type)
		{
			case ALLEGRO_EVENT_MOUSE_AXES:
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
			case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
			case ALLEGRO_EVENT_MOUSE_WARPED:

			onMouseEvent(event);

		break;

			default:
		break;
		}
	}

	while (!al_is_event_queue_empty(m_eventsTouch))
	{
		al_get_next_event(m_eventsTouch, &event);
		switch (event.type)
		{
			case ALLEGRO_EVENT_TOUCH_BEGIN:
			case ALLEGRO_EVENT_TOUCH_END:
			case ALLEGRO_EVENT_TOUCH_MOVE:
			case ALLEGRO_EVENT_TOUCH_CANCEL:

			onTouchEvent(event);

		break;

			default:
		break;
		}
	}
}


void GameContainer::update(double factor)
{
	m_deltaTime = factor;

	eventCatch();

	preUpdate();

	playerUpdate();

	autoUpdate();

	postUpdate();

	autoRemove();

	draw();
}


void GameContainer::draw()
{
	al_set_target_backbuffer(currentDisplay);
	al_clear_to_color(col::white);

	for (auto & elem : m_drawables)
	{
		if (elem->isReady())
		{
			elem->draw();
		}
	}

	al_flip_display();
}


void GameContainer::playerUpdate()
{

}

void GameContainer::preUpdate()
{
	initAll();

	for (const auto& it : m_objects)
		it->preUpdate();

	for (auto it : m_behaviours)
		it->preUpdate();
}

void GameContainer::autoUpdate()
{
	for (const auto& it : m_objects)
		it->update();

	for (const auto& it : m_behaviours)
		it->update();

	if (Camera::currentCamera())
		Camera::currentCamera()->update();
}

void GameContainer::postUpdate()
{
	list<Behaviour *> toDelete;

	for (const auto& it : m_objects)
		it->postUpdate();

	for (const auto& it : m_behaviours)
	{
		it->postUpdate();
	}
}

void GameContainer::autoRemove()
{
	list<GameObject*>::iterator it1;
	list<Behaviour*>::iterator it2;

	// removing stuff might set more stuff to be removed
	while (!m_remObjects.empty() || !m_remBehaviours.empty()
		|| !m_remDrawables.empty() || !m_remManBehaviours.empty())
	{
		// ALWAYS start by removing the objects (and delete them)
		// this will also call the destructors to the other stuff
		// and thus add them to the other remove lists
		for (it1 = m_remObjects.begin();it1 != m_remObjects.end();it1++)
		{
			delete (*it1);
			m_objects.erase(m_objects.find(*it1));
		}
		m_remObjects.clear();

		for (it2 = m_remManBehaviours.begin();it2 != m_remManBehaviours.end();it2++)
		{
			delete (*it2);
		}
		m_remManBehaviours.clear();

		for (const auto& it : m_remBehaviours)
		{
			m_behaviours.erase(m_behaviours.find(it));
		}
		m_remBehaviours.clear();

		for (const auto& it : m_remDrawables)
		{
			m_drawables.erase(m_drawables.find(it));
		}
		m_remDrawables.clear();
	}
}

#define FNADDCALLBACK(type)														\
const Behaviour##type##Callback *add##type##Callback(Behaviour *catcher,		\
		type##EventCallback toCall)												\
{																				\
	Behaviour##type##Callback *rep;												\
																				\
	if (catcher && toCall)														\
		rep = new Behaviour##type##Callback(catcher, toCall);					\
	else																		\
		throw "tried adding null callback";										\
	m_callbacks##type##.insert(rep);											\
	return rep;																	\
}

m_objects.insert(*it1);

FNADDCALLBACK(Keyboard)
FNADDCALLBACK(Mouse)
FNADDCALLBACK(Touch)

#undef FNADDCALLBACK

#define FNREMOVECALLBACK(type)													\
void remove##type##Callback(const Behaviour##type##Callback *what)				\
{																				\
	if (what)																	\
	{																			\
		auto a = m_callbacks##type##.find(what);								\
		if (a != m_callbacks##type##.end())										\
		{																		\
			delete *a;															\
			m_callbacks##type##.erase(a);										\
		}																		\
	}																			\
}

FNREMOVECALLBACK(Keyboard)
FNREMOVECALLBACK(Mouse)
FNREMOVECALLBACK(Touch)

#undef FNREMOVECALLBACK


//these will be called by their respective constructors
void GameContainer::addObject(GameObject* what)
{
	if (what)
	{
		m_newObjects.push_back(what);
	}
	else
		throw "tried adding null as an object pointer";
}

void GameContainer::addBehaviour(Behaviour* what)
{
	if (what)
	{
		m_newBehaviours.push_back(what);
	}
	else
		throw "tried adding null as a behaviour pointer";
}

void GameContainer::addDrawable(Drawable* what)
{
	if (what)
	{
		m_newDrawables.push_back(what);
	}
	else
		throw "tried adding null as a drawable pointer";
}



///sets the iterator to be removed at the end of the turn
void GameContainer::removeObject(GameObject *what)
{
	m_remObjects.push_back(what);
}

///sets the iterator to be removed at the end of the turn
void GameContainer::removeBehaviour(Behaviour *what)
{
	m_remBehaviours.push_back(what);
}

///sets the iterator to be removed at the end of the turn
void GameContainer::removeDrawable(Drawable *what)
{
	m_remDrawables.push_back(what);
}

void GameContainer::manualRemoveBehaviour(Behaviour *what)
{
	m_remManBehaviours.push_back(what);
}
