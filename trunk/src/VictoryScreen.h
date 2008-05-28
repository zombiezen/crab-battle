/*
 *  VictoryScreen.h
 *  Crab Battle
 *
 *  Created by Ross Light on 5/28/08.
 *  $Id$
 */

#include "SDL.h"
#include "Surface.h"
#include "State.h"

#ifndef _CRAB_BATTLE_VICTORYSCREEN_H_
#define _CRAB_BATTLE_VICTORYSCREEN_H_

namespace CrabBattle
{
    class VictoryScreen : public State
    {
    private:
        Surface *background;
        bool done;
    public:
        VictoryScreen(unsigned short);
        virtual void HandleEvent(SDL_Event);
        virtual State *Update(void);
        virtual void Display(Surface *);
        virtual ~VictoryScreen(void);
    };
}

#endif
