/*
 *  BaseObject.h
 *  Crab Battle
 *
 *  Created by Ross Light on 3/12/08.
 *  $Id$
 */

#include "SDL.h"

#ifndef _CRAB_BATTLE_BASEOBJECT_H_
#define _CRAB_BATTLE_BASEOBJECT_H_

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
