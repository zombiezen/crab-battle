/*
 *  MenuState.h
 *  Crab Battle
 *
 *  Created by Ross Light on 3/15/08.
 *  $Id$
 */

#include <SDL_ttf/SDL_ttf.h>
#include "Rect.h"
#include "Player.h"
#include "State.h"
#include <iostream>
#include <sstream>
using namespace std;

#ifndef _CRAB_BATTLE_MenuState_H_
#define _CRAB_BATTLE_MenuState_H_

namespace CrabBattle
{
    class MenuState : public State
        {
        private:
            TTF_Font *font;
            SDL_Surface *messPc1, *messPc2, *debugtext;
            Rect startRect, quitRect , debugRect, choiceRect;
            Surface *background, *choice;
            string sOutput;
            ostringstream outs;
            bool shouldPause;
        public:
            MenuState(void);
            SDL_Surface* render(double dh);
            SDL_Surface* render(char * dh);
            virtual void HandleEvent(SDL_Event);
            virtual State *Update(void);
            virtual void Display(Surface *);
            virtual ~MenuState(void);
        };
}

#endif
