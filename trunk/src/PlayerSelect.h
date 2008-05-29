/*
 *  PlayerSelect.h
 *  Crab Battle
 *
 *  Created by TJ Ferrell on 5/27/08.
 *  $Id$
 */

#if (defined(__WIN32__) || defined(WINDOWS)) || defined(MAC_OS_X)
#include <SDL_mixer/SDL_mixer.h>
#else
#include <SDL/SDL_mixer.h>
#endif
#include "SDL.h"
#include "Surface.h"
#include "State.h"
#include "SoundEffect.h"
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
