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
using CrabBattle::Rect;

static Surface *_gVideoSurface = NULL;

Surface *getVideoSurface(void)
{
    if (_gVideoSurface == NULL)
        _gVideoSurface = new Surface(SDL_GetVideoSurface());
    return _gVideoSurface;
}

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

Surface::Surface(SDL_Surface *surf)
{
    surface = surf;
    surface->refcount++; // We don't own the surface, so we don't want to delete it on object deletion
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

Rect Surface::GetRect(void)
{
    return Rect(0, 0, GetWidth(), GetHeight());
}

void Surface::Fill(Rect dest, unsigned int r, unsigned int g, unsigned int b)
{
    Uint32 color = SDL_MapRGB(surface->format, r, g, b);
    SDL_Rect actualRect = dest.ConvertToSDLRect();
    SDL_FillRect(surface, &actualRect, color);
    // TODO: If result of SDL_FillRect is -1, raise an error
}

void Surface::Update(Rect region)
{
    SDL_UpdateRect(surface, region.GetX(), region.GetY(), region.GetWidth(), region.GetHeight());
}

Surface::~Surface(void)
{
    SDL_FreeSurface(surface);
}