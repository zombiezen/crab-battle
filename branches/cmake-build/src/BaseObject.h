/*
 *  BaseObject.h
 *  Crab Battle
 *
 *  Created by Ross Light on 3/12/08.
 *  $Id$
 *
 *  Copyright (C) 2008 Ross Light, TJ Ferrell, and Ephraim Ruprecht.
 *
 *  This file is part of Crab Battle.
 *
 *  Crab Battle is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Crab Battle is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Crab Battle.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SDL.h"

#ifndef _CRAB_BATTLE_BASEOBJECT_H_
#define _CRAB_BATTLE_BASEOBJECT_H_

// Prints refcount debugging information
//#define DEBUG_BASEOBJECT_REFCOUNT

namespace CrabBattle
{
    /* Base object class
     *
     * Provides a base class for all objects in Crab Battle.
     * Currently, this object only provides reference counting.
     */
    
    /* * * REFERENCE COUNTING IN A NUTSHELL * * *
     * Reference counting is a paradigm for effectively managing memory.  The
     * problem with delete is that you have to be absolutely sure that you
     * aren't using the object anywhere else in the program.  By keeping a
     * reference count, you can always know how many places in the program
     * that an object is being used.  If the reference count reaches 0, then
     * the object is deallocated.
     *
     * For further reading, consult:
     * <http://en.wikipedia.org/wiki/Reference_counting>
     * (Because Wikipedia knows everything ;D)
     */
    class BaseObject
    {
    private:
        unsigned int _refCount;
    protected:
        /*** ALLOCATION ***/
        // This is protected, because subclasses may not want a default
        // constructor.  BE SURE YOU CALL THIS!
        BaseObject(void);
    public:
        /*** MEMORY MANAGEMENT ***/
        // obj->AddRef()
        // Tell the object that you have a new reference.
        void AddRef(void);
        // obj->DelRef()
        // Tell the object that you are done with it.
        void DelRef(void);
        // delete obj
        // Deallocates the memory for the object.
        // This should call DelRef on each object pointer
        // that the class has.
        virtual ~BaseObject(void);
    };
}

#endif
