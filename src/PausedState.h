/*
 *  PausedState.h
 *  Crab Battle
 *
 *  Created by Ross Light on 3/18/08.
 *  $Id$
 */

#include "SDL.h"
#include "Surface.h"
#include "State.h"
#include "GameState.h"
#include "MenuState.h"

#ifndef _CRAB_BATTLE_PAUSEDSTATE_H_
#define _CRAB_BATTLE_PAUSEDSTATE_H_

namespace CrabBattle
{
    class PausedState : public State
    {
    private:
        GameState *previous; // The state we're pausing from
        MenuState *previous1;
        Surface *background;
        bool done;
    public:
        PausedState(GameState *);
        PausedState(MenuState *);
        virtual void HandleEvent(SDL_Event);
        virtual State *Update(void);
        virtual void Display(Surface *);
        virtual ~PausedState(void);
    };
}

#endif
