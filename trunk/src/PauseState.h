/*
 *  PauseState.h
 *  Crab Battle
 *
 *  Created by Ephraim Ruprecht on 3/19/08.
 *  $Id: PauseState.h 115 2008-03-20 00:08:09Z v1g1lantenine $
 */

#include "Rect.h"
#include "State.h"

#ifndef _CRAB_BATTLE_PauseState_H_
#define _CRAB_BATTLE_PauseState_H_

namespace CrabBattle
{
    class PauseState : public State
        {
        private:
            Rect pcRect1, pcRect2;
            Surface *background, *player1, *player2;
        public:
            PauseState(void);
            virtual void HandleEvent(SDL_Event);
            virtual State *Update(void);
            virtual void Display(Surface *);
            ~PauseState(void);
        };
}

#endif
