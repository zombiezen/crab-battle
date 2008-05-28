/*
 *  PlayerSelect.h
 *  Crab Battle
 *
 *  Created by TJ Ferrell on 5/27/08.
 *  Copyright 2008 AOC. All rights reserved.
 *
 */

#include "SDL.h"
#include "Surface.h"
#include "State.h"

#ifndef _CRAB_BATTLE_PLAYERSELECTION_H_
#define _CRAB_BATTLE_PLAYERSELECTION_H_

namespace CrabBattle
{
    class PlayerSelect : public State
        {
        private:
            Surface *background, *chuckNorris, *mudkips, *zim;
            bool done;
        public:
            PlayerSelect(void);
            virtual void HandleEvent(SDL_Event);
            virtual State *Update(void);
            virtual void Display(Surface *);
            virtual ~PlayerSelect(void);
        };
}

#endif