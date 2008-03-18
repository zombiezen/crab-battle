/*
 *  MainMenu.h
 *  Crab Battle
 *
 *  Created by Ross Light on 3/18/08.
 *  $Id$
 */

#include "State.h"

#ifndef _CRAB_BATTLE_MAINMENU_H_
#define _CRAB_BATTLE_MAINMENU_H_

namespace CrabBattle
{
    class MainMenu : public State
    {
    public:
        MainMenu(void);
        virtual void HandleEvent(SDL_Event);
        virtual State *Update(void);
        virtual void Display(Surface *);
        ~MainMenu(void);
    };
}

#endif
