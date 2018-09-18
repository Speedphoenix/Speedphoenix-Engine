#include "DiscreetAnimation.h"

#include "SpritesContainer.h"

#include "config.h"
#include "colors.h"
#include "allegroImplem.h"
#include "debugNerrors.h"

#include "basic_ops.h"

#include "Frame.h"

using namespace std;

///FOR TESTING PURPOSES
void DiscreetAnimation::maketest(int type)
{
    SpritesContainer* sprites = SpritesContainer::instance();

    ALLEGRO_BITMAP* btm;
    ALLEGRO_BITMAP* parent = sprites->at(TEST_SHEETNAME);

    vector<Frame*>& inDirec = m_frames[Direc::E];

    switch (type)
    {
        case 0: //idle
        {
            inDirec.push_back(new Frame(parent, 0, 0, 75, 75));
//            inDirec.push_back(new Frame(parent, 4*75, 0, 75, 75));
//            inDirec.push_back(new Frame(parent, 0, 0, 75, 75));
            inDirec.push_back(new Frame(parent, 5*75, 75, 75, 75));
            m_lapse = defaultIdleLapse;
        }
    break;

        case 1: //active
        {
            for (int i=0;i<6;i++)
            {
                inDirec.push_back(new Frame(parent, i*75, 0, 75, 75));
            }
            m_lapse = defaultActiveLapse;
        }
    break;

        case 2: //attack idle
        {
            inDirec.push_back(new Frame(parent, 75, 75, 5*75, 75));
            m_lapse = defaultIdleLapse;
        }
    break;

        case 3: //attack active
        {
            for (int i=0;i<6;i++)
            {
                inDirec.push_back(new Frame(parent, i*75, 75, 75, 75));
            }
            m_lapse = defaultActiveLapse;
        }
    break;

        default:
        //the default flag, never know
        al_set_new_bitmap_flags(ALLEGRO_CONVERT_BITMAP);

        btm = al_create_bitmap(75, 75);

        al_set_target_bitmap(btm);
        al_clear_to_color(col::olds::GRASS);
        al_draw_filled_rectangle(20, 20, 55, 55, col::olds::UI_ACC);

        inDirec.push_back(new Frame(btm));
    break;
    }

    m_currDirection = Direc::E;
}


//only default, will need to use a real one later
DiscreetAnimation::DiscreetAnimation()
    :Animation(), m_currDirection(Direc::E)
{
    //ctor
}

DiscreetAnimation::~DiscreetAnimation()
{
    //dtor
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
        return inter.at(inter.size() - 1);  //replace this by inter.at(0); to take the first frame instead
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
#define CHECKORDER(_1, _2, _3, _4, _5, _6, _7)  \
CHECK(_1)                                       \
else CHECK(_2)                                  \
else CHECK(_3)                                  \
else CHECK(_4)                                  \
else CHECK(_5)                                  \
else CHECK(_6)                                  \
else CHECK(_7)                                  \
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

