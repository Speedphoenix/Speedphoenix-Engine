#include "GlobalObject.h"

#include "Behaviour.h"

GlobalObject::GlobalObject()
    :GameObject()
{
    //ctor
}

GlobalObject::~GlobalObject()
{
    for (unsigned i=0;i<m_uniques.size();i++)
        delete m_uniques.at(i);
}

