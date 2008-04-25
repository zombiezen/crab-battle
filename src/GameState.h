/*
 *  GameState.h
 *  Crab Battle
 *
 *  Created by Ross Light on 3/15/08.
 *  $Id$
 */

#include <SDL_ttf/SDL_ttf.h>
#include "Rect.h"
#include "State.h"
#include <iostream>
#include <sstream>
using namespace std;
//using std::string;

#ifndef _CRAB_BATTLE_GAMESTATE_H_
#define _CRAB_BATTLE_GAMESTATE_H_

namespace CrabBattle
{
    class GameState : public State
        {
        private:
            TTF_Font *font;
            SDL_Surface *message;
            Rect pcRect1, pcRect2, hpRect1, hpRect2 , hptext1, hptext2;
            Surface *background, *player1, *player2, *healthbar1;
            string sOutput;
            ostringstream outs;
            bool shouldPause;
        public:
            GameState(void);
            virtual void HandleEvent(SDL_Event);
            virtual State *Update(void);
            virtual void Display(Surface *);
            virtual ~GameState(void);
        };
}

#endif
