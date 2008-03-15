/*
 *  State.h
 *  Crab Battle
 *
 *  Created by Ross Light on 3/15/08.
 *  $Id$
 */

#include "BaseObject.h"
#include "Surface.h"

#ifndef _CRAB_BATTLE_STATE_H_
#define _CRAB_BATTLE_STATE_H_

namespace CrabBattle
{
    class State : public BaseObject
    {
    public:
        virtual void HandleEvent(SDL_Event) = 0;
        virtual State *Update(void) = 0;
        virtual void Display(Surface *) = 0;
        virtual ~State(void) {};
    };
}

#endif
