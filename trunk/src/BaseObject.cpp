/*
 *  BaseObject.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 3/12/08.
 *  $Id$
 */

#ifdef DEBUG_BASEOBJECT_REFCOUNT
#include <iostream>
#endif
#include "BaseObject.h"

using CrabBattle::BaseObject;

BaseObject::BaseObject(void)
{
    _refCount = 1;
    #ifdef DEBUG_BASEOBJECT_REFCOUNT
    std::cout << "OBJECT: CREATED" << std::endl;
    #endif
}

void BaseObject::AddRef(void)
{
    _refCount++;
    #ifdef DEBUG_BASEOBJECT_REFCOUNT
    std::cout << "OBJECT: RETAINED" << std::endl;
    #endif
}

void BaseObject::DelRef(void)
{
    _refCount--;
    #ifdef DEBUG_BASEOBJECT_REFCOUNT
    std::cout << "OBJECT: RELEASED" << std::endl;
    #endif
    if (_refCount == 0)
    {
        #ifdef DEBUG_BASEOBJECT_REFCOUNT
        std::cout << "OBJECT: DEALLOCATED" << std::endl;
        #endif
        delete this;
    }
}

BaseObject::~BaseObject(void)
{
}
