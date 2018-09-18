#include "State.h"

#include "debugNerrors.h"

void Transition::finishTransition()
{
    //just in case
    to.blockTransitionType();

    from = to;

    animType = to.animType;

    playOnce = toPlayOnce;
}

void Transition::setState(State dest, bool _playOnce)
{
    if (dest.animType==Anim::Transition)
    {
        dest.animType = Anim::Idle;
        setChange(dest, _playOnce);
    }
    else
    {
        to = dest;
        from = dest;
        animType = dest.animType;
        playOnce = _playOnce;
        toPlayOnce = _playOnce;
    }
}

void Transition::setChange(State dest, bool destPlayOnce)
{
    from = to;
    to = dest;
    to.blockTransitionType();

    animType = Anim::Transition;
    playOnce = true;
    toPlayOnce = destPlayOnce;
}

void Transition::setType(Anim::AnimType dest, bool _playOnce)
{
    animType = dest;

    toPlayOnce = _playOnce;

    if (dest!=Anim::Transition)
    {
        to.animType = dest;

        from = to;

        playOnce = _playOnce;
    }
    else
    {
        playOnce = true;
    }
}

