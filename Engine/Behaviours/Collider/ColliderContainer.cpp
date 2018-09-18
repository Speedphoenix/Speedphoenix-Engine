#include "ColliderContainer.h"
ColliderContainer* ColliderContainer::m_instance = nullptr;

#include "GameContainer.h"
#include "GlobalObject.h"
#include "Collider.h"
#include "Transform.h"

#include "debugNerrors.h"

#include <algorithm>

using namespace std;

//this acts as first < second
bool XComparator::operator() (Collider* first, Collider* second)
{
    //same pointer
    if (first==second)
        return false;
    else if (first->boxAbsX() < second->boxAbsX())
        return true;
    else
        return false;
}


//statics

void ColliderContainer::addCollider(Collider* what)
{
    //will sort the whole thing at once later, no need to do it now
    if (m_waitToSort)
    {
        m_XOrdered.push_front(what);
    }
    else    // insert the new collider at the right places
    {
        list<Collider*>::iterator iter = m_XOrdered.begin();

        while (iter != m_XOrdered.end() && m_xCompare(*iter, what))
        {
            iter++;
        }

        m_XOrdered.insert(iter, what);

    }
}

void ColliderContainer::removeCollider(Collider* what)
{
    m_instance->m_XOrdered.remove(what);
}


//non-statics

ColliderContainer::ColliderContainer()
    :Behaviour(GameContainer::getGlobalObject()), m_waitToSort(true), m_xCompare(), m_firstTurn(true)
{
    if (!m_instance)
        m_instance = this;
    else
        throw "A collider container already exists";
    //ctor
}

ColliderContainer::~ColliderContainer()
{
    //dtor

}

void ColliderContainer::sortList()
{
    m_XOrdered.sort(m_xCompare);    //ascending order
}

void ColliderContainer::start()
{
    sortList();

    m_waitToSort = false;

    m_firstTurn = true;
}

void ColliderContainer::preUpdate()
{
    list<Collider*>::iterator currIter, checkIter;
    Collider* currCollider;
    Collider* checkCollider;

    sortList();

    //reset every collider (override previous collisions)
    for (currIter = m_XOrdered.begin() ; currIter != m_XOrdered.end() ; currIter++)
    {
        (*currIter)->resetTurn();
    }

    for (currIter = m_XOrdered.begin() ; currIter != m_XOrdered.end() ; currIter++)
    {
        currCollider = *currIter;
        checkIter = currIter;

        //every colider that comes after currIter in the list has an AbsX equal or higher than currIter
        std::advance(checkIter, 1); //same as checkIter++

        //if the second part of the collider comes after the beginning of a collider that we know has a later beginning they could collide
        while ( (checkIter != m_XOrdered.end()) && (currCollider->boxEndAbsX() >= (*checkIter)->boxAbsX()) )
        {
            checkCollider = *checkIter;
            std::advance(checkIter, 1);

//            //if both things did not move there is no need to check anything
//            if (!m_firstTurn && !currCollider->moved() && !checkCollider->moved())
//                continue; //skip this collision test

            //if the boxes collide on the y axis too
            if ((currCollider->boxAbsY() > checkCollider->boxAbsY() && currCollider->boxAbsY() < checkCollider->boxEndAbsY())       ||
                (currCollider->boxEndAbsY() > checkCollider->boxAbsY() && currCollider->boxEndAbsY() < checkCollider->boxEndAbsY()) ||
                (checkCollider->boxAbsY() > currCollider->boxAbsY() && checkCollider->boxAbsY() < currCollider->boxEndAbsY()))
            {
                currCollider->checkAndAddCollision(checkCollider);
            }
        }
    }
}

void ColliderContainer::update()
{

}

void ColliderContainer::postUpdate()
{
    m_firstTurn = false;
}

