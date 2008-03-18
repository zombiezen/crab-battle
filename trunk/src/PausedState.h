/*
 *  PausedState.h
 *  Crab Battle
 *
 *  Created by Ross Light on 3/18/08.
 *  $Id$
 */

#include "State.h"
#include "GameState.h"

#ifndef _CRAB_BATTLE_PAUSEDSTATE_H_
#define _CRAB_BATTLE_PAUSEDSTATE_H_

namespace CrabBattle
{
    class PausedState : public State
    {
    private:
        GameState *previous; // The state we're pausing from
    public:
        PausedState(GameState *);
        virtual void HandleEvent(SDL_Event);
        virtual State *Update(void);
        virtual void Display(Surface *);
        ~PausedState(void);
    };
}

#endif
