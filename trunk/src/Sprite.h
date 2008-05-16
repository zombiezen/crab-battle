/*
 *  Sprite.h
 *  Crab Battle
 *
 *  Created by Ross Light on 2/23/08.
 *  $Id$
 */

#include <ode/ode.h>
#include "BaseObject.h"
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
    class Sprite : public BaseObject
    {
    private:
        double x, y, rot;
        Surface *surface;
        dBody *body;
        dGeom *geometry;
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
        // sprite.GetRotation()
        double GetRotation(void);
        // sprite.SetRotation(theta)
        void SetRotation(double);
        // sprite.GetSurface()
        Surface *GetSurface(void);
        // sprite.SetSurface(surface)
        void SetSurface(Surface *);
        // sprite.GetBody()
        dBody *GetBody(void);
        // sprite.SetBody(body)
        void SetBody(dBody *);
        // sprite.GetBody()
        dGeom *GetGeometry(void);
        // sprite.SetGeometry(geom)
        void SetGeometry(dGeom *);
        /*** ACTIONS ***/
        // sprite.FixPhysics()
        // "Fix" the physics to 2D space
        void FixPhysics();
        // sprite.Display(screen)
        // Blits a sprite onto another surface
        virtual void Display(Surface *);
        /*** DESTRUCTOR ***/
        virtual ~Sprite(void);
    };
}

#endif
