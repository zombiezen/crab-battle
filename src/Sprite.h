/*
 *  Sprite.h
 *  Crab Battle
 *
 *  Created by Ross Light on 2/23/08.
 *  $Id$
 */

#include "Rect.h"
#include "Surface.h"

#ifndef _CRAB_BATTLE_SPRITE_H_
#define _CRAB_BATTLE_SPRITE_H_

namespace CrabBattle
{
    /*  Sprite class
     *
     *  Sprites are a convenience class for encapsulating position and
     *  image data.  A sprite can be described as any object that could possibly
     *  move.
     */
    class Sprite
    {
    private:
        double x, y;
        Surface *surface;
        bool created_surface;
    public:
        /*** CONSTRUCTORS ***/
        // Sprite(surface)
        // Create a sprite from a surface.  The position defaults to (0, 0).
        Sprite(Surface *);
        // Sprite(surface, position)
        // Create a sprite, giving it an initial surface and position
        Sprite(Surface *, Rect);
        /*** ACCESSORS ***/
        // sprite.GetPosition()
        Rect GetPosition(void);
        // sprite.SetPosition(rect)
        void SetPosition(Rect);
        // sprite.GetSurface()
        Surface *GetSurface(void);
        // sprite.SetSurface(surface)
        void SetSurface(Surface *);
        /*** ACTIONS ***/
        // sprite.Display(screen)
        // Blits a sprite onto another surface
        void Display(Surface *);
        /*** DESTRUCTOR ***/
        ~Sprite(void);
    };
}

#endif
