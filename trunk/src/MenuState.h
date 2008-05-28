/*
 *  MenuState.h
 *  Crab Battle
 *
 *  Created by Ephraim Ruprecht on 5/21/08.
 *  $Id$
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