/*
 *  Surface.h
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

#include "SDL.h"
#include <string>

#include "BaseObject.h"
#include "Rect.h"

#ifndef _CRAB_BATTLE_SURFACE_H_
#define _CRAB_BATTLE_SURFACE_H_

namespace CrabBattle
{
    /* A wrapper class for SDL_Surface.
     *
     * A surface is, in layman's terms, an image.  This image can be blitted,
     * which means drawn on the screen, or directly modified pixel-by-pixel.
     */
    class Surface : public BaseObject
    {
    private:
        SDL_Surface *surface;
    public:
        // screen = Surface::GetVideoSurface()
        // Retrieves the screen that we're actually drawing to
        static Surface *GetVideoSurface(void);
        /*** CONSTRUCTORS ***/
        // Surface(width, height)
        Surface(unsigned int, unsigned int);
        #ifndef NO_SDL_IMAGE
        // Surface(filename)
        Surface(const char *);
        // Surface(filename)
        Surface(std::string);
        #endif
        // Surface(flags, width, height, bitsPerPixel)
        // Creates a surface with roughly the same arguments as SDL_CreateRGBSurface
        Surface(Uint32, unsigned int, unsigned int, unsigned int);
        // Surface(surface)
        // Creates a surface object that points to an existing SDL_Surface
        Surface(SDL_Surface *);
        // Surface(surface_object)
        Surface(Surface *);
        /*** ACCESSORS ***/
        // surface.GetSurface()
        // Retrieves the underlying SDL_Surface
        SDL_Surface *GetSurface(void);
        // surface.GetWidth()
        unsigned int GetWidth(void);
        // surface.GetHeight()
        unsigned int GetHeight(void);
        // surface.GetRect()
        // Returns a rectangle with the width and height, and origin (0, 0)
        Rect GetRect(void);
        /*** ACTIONS ***/
        // surface.Fill(region, red, green, blue)
        // Fills a rectangle with the given color
        void Fill(Rect, unsigned int, unsigned int, unsigned int);
        //destination.Blit(source);
        //blits the entire screen
        void Blit(SDL_Surface *);
        // destination.Blit(source, locationRect)
        // destination.Blit(source, x, y)
        // Blends source onto destination at rectangle location.
        void Blit(SDL_Surface *, Rect);
        void Blit(Surface *, Rect);
        void Blit(SDL_Surface *, int, int);
        void Blit(Surface *, int, int);
        // destination.Blit(source, location, srcArea)
        // Blends source onto destination at rectangle location, only copying
        // the portion of the image at srcArea.
        void Blit(Surface *, Rect, Rect);
        //for use with the healthbar
        //double changes value of bar
        void Blit(Surface *, Rect, double);
        // screen.Update(region)
        // Updates region on the screen.  This really only makes sense for
        // the surface given by Surface::GetVideoSurface()
        void Update(Rect);
        // screen.Flip()
        // Flips the second buffer onto the screen.  This really only makes
        // sense for the surface given by Surface::GetVideoSurface()
        void Flip(void);
        /*** OPERATORS ***/
        operator SDL_Surface*(void);
        Surface &operator=(const Surface &);
        Surface &operator=(SDL_Surface *);
        /*** DESTRUCTOR ***/
        ~Surface(void);
    };
}

#endif
