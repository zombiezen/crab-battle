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
     *  Base class for anything that moves
     */
    class Sprite
    {
    private:
        double x, y;
        Surface *surface;
        bool created_surface;
    public:
        Sprite(void);
        Sprite(Surface *);
        Sprite(Surface *, Rect);
        Rect GetPosition(void);
        void SetPosition(Rect);
        Surface *GetSurface(void);
        void SetSurface(Surface *);
        void Display(Surface *);
        ~Sprite(void);
    };
}

#endif