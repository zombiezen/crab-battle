/*
 *  MenuState.h
 *  Crab Battle
 *
 *  Created by Ephraim Ruprecht on 5/21/08.
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
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
#include "Rect.h"
#include "Player.h"
#include "State.h"
#include <iostream>
#include <sstream>
using namespace std;

#ifndef _CRAB_BATTLE_MENUSTATE_H_
#define _CRAB_BATTLE_MENUSTATE_H_

namespace CrabBattle
{
    class MenuState : public State
        {
        private:
            TTF_Font *font;
            SDL_Surface *messPc1, *messPc2;
            Rect startRect, quitRect , choiceRect;
            Surface *background, *choice;
            unsigned short action;
        public:
            MenuState(void);
            virtual void HandleEvent(SDL_Event);
            virtual State *Update(void);
            virtual void Display(Surface *);
            virtual ~MenuState(void);
        };
}

#endif
