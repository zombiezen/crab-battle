/*
 *  PlayerSelect.h
 *  Crab Battle
 *
 *  Created by TJ Ferrell on 5/27/08.
 *  $Id$
 */

#include "SDL.h"
#include "Surface.h"
#include "State.h"
#include <vector>

#ifndef _CRAB_BATTLE_PLAYERSELECT_H_
#define _CRAB_BATTLE_PLAYERSELECT_H_

namespace CrabBattle
{
    class PlayerSelect : public State
    {
    private:
        Surface *background;
        std::vector<Surface *> players;
        unsigned short p1Choice, p2Choice;
        bool goBack, p1Done, p2Done;
    public:
        PlayerSelect(void);
        virtual void HandleEvent(SDL_Event);
        virtual State *Update(void);
        virtual void Display(Surface *);
        virtual ~PlayerSelect(void);
    };
}

#endif
