/*
 *  Surface.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 2/23/08.
 *  $Id$
 */

#include "Surface.h"
#include <SDL_image/SDL_image.h>

using CrabBattle::Surface;

Surface::Surface(unsigned int w, unsigned int h)
{
    surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 24, 0, 0, 0, 0);
}

Surface::Surface(const char *fname)
{
    surface = IMG_Load(fname);
    // TODO: If surface is NULL, raise an error
}

Surface::Surface(Uint32 flags, unsigned int w, unsigned int h, unsigned int bps)
{
    surface = SDL_CreateRGBSurface(flags, w, h, bps, 0, 0, 0, 0);
}

SDL_Surface *Surface::GetSurface(void)
{
    return surface;
}

unsigned int Surface::GetWidth(void)
{
    return surface->w;
}

unsigned int Surface::GetHeight(void)
{
    return surface->h;
}

Surface::~Surface(void)
{
    SDL_FreeSurface(surface);
    delete surface;
}