/*
 *  SoundEffect.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 5/28/08.
 *  $Id$
 */

#include "SoundEffect.h"
#include "exceptions.h"

using CrabBattle::SoundEffect;

SoundEffect::SoundEffect(const char *fname)
{
    // Contrary to popular belief (and intuition), this loads anything
    sound = Mix_LoadWAV(fname);
    if (sound == NULL)
        throw FileNotFoundError(fname);
}

SoundEffect::SoundEffect(std::string fname)
{
    // Contrary to popular belief (and intuition), this loads anything
    sound = Mix_LoadWAV(fname.c_str());
    if (sound == NULL)
        throw FileNotFoundError(fname.c_str());
}

void SoundEffect::Play(int loops)
{
    Mix_PlayChannel(-1, sound, loops);
}

SoundEffect::~SoundEffect(void)
{
    Mix_FreeChunk(sound);
}
