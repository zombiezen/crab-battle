/*
 *  GameState.h
 *  Crab Battle
 *
 *  Created by Ross Light on 3/15/08.
 *  $Id$
 */

#if (defined(__WIN32__) || defined(WINDOWS)) || defined(MAC_OS_X)
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
#include <iostream>
#include <sstream>

#include "Rect.h"
#include "Player.h"
#include "State.h"

using namespace std;

#ifndef _CRAB_BATTLE_GAMESTATE_H_
#define _CRAB_BATTLE_GAMESTATE_H_

namespace CrabBattle
{
    class GameState : public State
    {
        private:
            TTF_Font *font;
            Player *player1, *player2;
            SDL_Surface *messPc1, *messPc2, *wins1, *wins2;
            Rect hpRect1, hpRect2 , hptext1, hptext2, winsRect1, winsRect2;
            Surface *background, *healthbar1;
            string sOutput;
            ostringstream outs;
            bool shouldPause;
        public:
            GameState(void);
            SDL_Surface* render(double dh);
            virtual void HandleEvent(SDL_Event);
            virtual State *Update(void);
            virtual void Display(Surface *);
            virtual ~GameState(void);
    };
}

#endif
