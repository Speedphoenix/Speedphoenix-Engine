#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

enum GeneralState : unsigned{
    Walking,
    Crouching,
    TipToes,
    Attacking,
    Swimming,
    Dying,
    Burning,

    none
};

namespace Anim {
    ///The type of an animation
    enum AnimType : int{
        Idle,
        Active,
        Transition  // these will be played once during the transition from one state to another
                    // (only if the transition animation is available)
    };
}

struct State {
    GeneralState genState;
    Anim::AnimType animType;

    State(GeneralState _genState, Anim::AnimType _animType = Anim::Idle)
        :genState(_genState), animType(_animType)
    {
        if (animType==Anim::Transition)
            animType = Anim::Idle;
    }

    void blockTransitionType()
    {
        if (animType==Anim::Transition)
            animType = Anim::Idle;
    }

    bool operator==(GeneralState what) const {
        return this->genState == what;
    }

    bool operator==(const State& other) const {
        return (this->genState==other.genState && this->animType==other.animType);
    }

    bool operator<(const State& other) const {
        if (this->animType < other.animType)
            return true;
        else if (this->animType > other.animType)
            return false;
        else if (this->genState < other.genState)
            return true;
        else if (this->genState > other.genState)
            return false;
        else
            return false;
    }

    bool operator>(const State& other) const {
        return (!(*this < other) && !(*this == other));
    }
};

//might wanna rename this struct...
struct Transition {
    State from;

    State to;
    bool toPlayOnce;

    //idle, transition, active. might wanna make this unique to from state and to state...
    Anim::AnimType animType;

    bool playOnce;

    Transition()
        :from(Walking), to(Walking), toPlayOnce(false), animType(Anim::Idle), playOnce(false) { }

    Transition(GeneralState _state, Anim::AnimType _animType = Anim::Idle, bool _playOnce = false)
        :from(_state, _animType), to(_state, _animType), toPlayOnce(false), animType(_animType), playOnce(_playOnce) { }

    //not really necessary
    bool operator==(const Transition& other) const {
        return (other.from == this->from && other.to == this->to && this->animType==other.animType);
    }

    //to be used as a key in a map
    bool operator<(const Transition& other) const {
        if (this->animType < other.animType)
            return true;
        else if (this->animType > other.animType)
            return false;
        else if (this->from < other.from)   //check from state
            return true;
        else if (this->from > other.from)
            return false;
        else if (this->to < other.to)       //check to state
            return true;
        else if (this->to > other.to)
            return false;
        else                            //this means the two transitions are the same
            return false;
    }

    void finishTransition();

    void setState(State dest, bool _playOnce = false);
    void setChange(State dest, bool destPlayOnce = false);
    void setType(Anim::AnimType dest, bool _playOnce = false);
};

#endif // STATE_H_INCLUDED

