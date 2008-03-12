/*
 *  BaseObject.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 3/12/08.
 *  $Id$
 */

#include <iostream>
#include "BaseObject.h"

using CrabBattle::BaseObject;

BaseObject::BaseObject(void)
{
    using std::cout;
    using std::endl;
    _refCount = 1;
    cout << "BaseObject::BaseObject()" << endl;
}

void BaseObject::AddRef(void)
{
    _refCount++;
}

void BaseObject::DelRef(void)
{
    _refCount--;
    if (_refCount == 0)
        delete this;
}

BaseObject::~BaseObject(void)
{
}
