/*
 *  PlayerSelect.h
 *  Crab Battle
 *
 *  Created by TJ Ferrell on 5/27/08.
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

#if (defined(__WIN32__) || defined(WINDOWS)) || defined(MAC_OS_X)
#include <SDL_mixer/SDL_mixer.h>
#else
#include <SDL/SDL_mixer.h>
#endif
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
        Mix_Music *music;
        Surface *background, *choice, *ready;
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
