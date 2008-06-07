/*
 *  Surface.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 2/23/08.
 *  $Id$
 *
 *  Copyright (C) 2008 Ross Light, TJ Ferrell, and Ephraim Ruprecht.
 *
 *  This file is part of Crab Battle.
 *
 *  Crab Battle is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Crab Battle is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Crab Battle.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Surface.h"
#include "exceptions.h"
#ifndef NO_SDL_IMAGE
#  ifdef MAC_OS_X
#include <SDL_image/SDL_image.h>
#  else
#include <SDL_image.h>
#  endif // MAC_OS_X
#endif // NO_SDL_IMAGE

using CrabBattle::Surface;
using CrabBattle::Rect;

Surface *Surface::GetVideoSurface(void)
{
    static Surface *screen = NULL;
    if (screen == NULL)
        screen = new Surface(SDL_GetVideoSurface());
    return screen;
}

Surface::Surface(unsigned int w, unsigned int h)
{
    surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 24, 0, 0, 0, 0);
}

#ifndef NO_SDL_IMAGE
Surface::Surface(const char *fname)
{
    surface = IMG_Load(fname);
    if (surface == NULL)
        throw FileNotFoundError(fname);
}

Surface::Surface(std::string fname)
{
    surface = IMG_Load(fname.c_str());
    if (surface == NULL)
        throw FileNotFoundError(fname.c_str());
}
#endif

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
    SDL_Rect actualRect = dest;
    SDL_FillRect(surface, &actualRect, color);
    // TODO: If result of SDL_FillRect is -1, raise an error
}

void Surface::Blit(SDL_Surface *src) //SDL_Surface
{
  SDL_BlitSurface(src, NULL, surface, NULL); //blits the entire screen
  //SDL_BlitSurface(src, NULL, screen, &dest);

}

void Surface::Blit(Surface *src, Rect dest)
{
    SDL_Rect r = dest;
    SDL_BlitSurface(src->GetSurface(), NULL, surface, &r);
    // TODO: Raise an error if SDL_BlitSurface doesn't return 0
}

void Surface::Blit(SDL_Surface *src, Rect dest) //SDL_Surface
{
    SDL_Rect r = dest;
    SDL_BlitSurface(src, NULL, surface, &r);
    // TODO: Raise an error if SDL_BlitSurface doesn't return 0
}

void Surface::Blit(Surface *src, int x, int y)
{
    SDL_Rect r = {x, y, GetHeight(), GetWidth()};
    SDL_BlitSurface(src->GetSurface(), NULL, surface, &r);
    // TODO: Raise an error if SDL_BlitSurface doesn't return 0
}

void Surface::Blit(SDL_Surface *src, int x, int y)
{
    SDL_Rect r = {x, y, GetHeight(), GetWidth()};
    SDL_BlitSurface(src, NULL, surface, &r);
    // TODO: Raise an error if SDL_BlitSurface doesn't return 0
}

void Surface::Blit(Surface *src, Rect dest, Rect srcRegion)
{
    SDL_Rect r_dest = dest;
    SDL_Rect r_src = srcRegion;
    SDL_BlitSurface(src->GetSurface(), &r_src, surface, &r_dest);
    // TODO: Raise an error if SDL_BlitSurface doesn't return 0
}

void Surface::Blit(Surface *src, Rect dest, double dhp)
{
    SDL_Rect r_dest = dest;
    Rect srcRegion = Rect(dhp , 30);//size of image
    SDL_Rect r_src = srcRegion;
    SDL_BlitSurface(src->GetSurface(), &r_src, surface, &r_dest);
}

void Surface::Update(Rect region)
{
    SDL_UpdateRect(surface,
                   (Sint32)region.GetX(),
                   (Sint32)region.GetY(),
                   (Uint32)region.GetWidth(),
                   (Uint32)region.GetHeight());
}

void Surface::Flip(void)
{
    SDL_Flip(surface);
}

Surface::operator SDL_Surface*(void)
{
    return surface;
}

Surface &Surface::operator=(const Surface &newSurf)
{
    surface = newSurf.surface;
    surface->refcount++;
    return *this;
}

Surface &Surface::operator=(SDL_Surface *newSurf)
{
    surface = newSurf;
    surface->refcount++;
    return *this;
}

Surface::~Surface(void)
{
    SDL_FreeSurface(surface);
}
