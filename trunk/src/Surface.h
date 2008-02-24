/*
 *  Surface.h
 *  Crab Battle
 *
 *  Created by Ross Light on 2/23/08.
 *  $Id$
 */

#include "SDL.h"

#include "Rect.h"

#ifndef _CRAB_BATTLE_SURFACE_H_
#define _CRAB_BATTLE_SURFACE_H_

namespace CrabBattle
{
    class Surface
    {
    private:
        SDL_Surface *surface;
    public:
        Surface(unsigned int, unsigned int);    // Create from (w, h)
        Surface(const char *);                  // Load from file
        Surface(Uint32, unsigned int, unsigned int, unsigned int); // flags, w, h, bitsPerPixel
        Surface(SDL_Surface *);
        SDL_Surface *GetSurface(void);
        unsigned int GetWidth(void);
        unsigned int GetHeight(void);
        Rect GetRect(void);
        void Fill(Rect, unsigned int, unsigned int, unsigned int);
        void Update(Rect);
        ~Surface(void);
    };
    
    Surface *getVideoSurface(void);
}

#endif