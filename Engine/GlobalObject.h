#ifndef GLOBALOBJECT_H
#define GLOBALOBJECT_H

#include <GameObject.h>

class Behaviour;

//this is a gameObject that is contained in the GameContainer, usefull for
class GlobalObject : public GameObject
{
    protected:
        std::vector<Behaviour*> m_uniques;

    public:
        GlobalObject();
        virtual ~GlobalObject();

        //override the update function, we don't need it here
        virtual void update() { }

        void attachBehaviour(Behaviour* what) { m_uniques.push_back(what); }
};

#endif // GLOBALOBJECT_H
