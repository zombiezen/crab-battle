/*
 *  GameState.h
 *  Crab Battle
 *
 *  Created by Ross Light on 3/15/08.
 *  $Id$
 */

#include "Rect.h"
#include "State.h"

#ifndef _CRAB_BATTLE_GAMESTATE_H_
#define _CRAB_BATTLE_GAMESTATE_H_

namespace CrabBattle
{
    class GameState : public State
        {
        private:
            Rect pcRect1, pcRect2;
            Surface *background, *player1, *player2;
        public:
            GameState(void);
            virtual void HandleEvent(SDL_Event);
            virtual State *Update(void);
            virtual void Display(Surface *);
            ~GameState(void);
        };
}

#endif
