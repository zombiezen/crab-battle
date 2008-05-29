/*
 *  SoundEffect.h
 *  Crab Battle
 *
 *  Created by Ross Light on 5/28/08.
 *  $Id$
 */

#include "SDL.h"
#if (defined(__WIN32__) || defined(WINDOWS)) || defined(MAC_OS_X)
#include <SDL_mixer/SDL_mixer.h>
#else
#include <SDL/SDL_mixer.h>
#endif
#include <string>

#include "BaseObject.h"

#ifndef _CRAB_BATTLE_SOUNDEFFECT_H_
#define _CRAB_BATTLE_SOUNDEFFECT_H_

namespace CrabBattle
{
    class SoundEffect : public BaseObject
    {
    private:
        Mix_Chunk *sound;
    public:
        /*** CONSTRUCTORS ***/
        // Surface(filename)
        SoundEffect(const char *);
        // Surface(filename)
        SoundEffect(std::string);
        /*** ACTIONS ***/
        // Play(loops=0)
        void Play(int=0);
        /*** DESTRUCTOR ***/
        ~SoundEffect(void);
    };
}

#endif
