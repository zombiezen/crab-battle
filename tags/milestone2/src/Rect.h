/*
 *  Rect.h
 *  Crab Battle
 *
 *  Created by Ross Light on 2/23/08.
 *  $Id$
 */

#include "SDL.h"
#include "BaseObject.h"

#ifndef _CRAB_BATTLE_RECT_H_
#define _CRAB_BATTLE_RECT_H_

namespace CrabBattle
{
    /* Rectangle class
     *
     * For simplicity, all rectangles use the top-left for the origin.  Yes, I
     * know that's not mathematically correct, but that's what SDL does.
     */
    class Rect : public BaseObject
    {
    private:
        double x, y, w, h;
    public:
        /*** CONSTRUCTORS ***/
        // Rect()
        // Creates a rectangle (0, 0, 0, 0)
        Rect(void);
        // Rect(width, height)
        // Creates a rectangle (0, 0, width, height)
        Rect(double, double);
        // Rect(x, y, width, height)
        Rect(double, double, double, double);
        /*** ACCESSORS ***/
        // rect.GetX()
        double GetX(void) const;
        // rect.SetX(x)
        void SetX(double);
        // rect.GetY()
        double GetY(void) const;
        // rect.SetY(y)
        void SetY(double);
        // rect.SetXY(x, y)
        void SetXY(double, double);
        // rect.Move(deltaX, deltaY)
        // Moves a rectangle to x + deltaX, y + deltaY
        void Move(double, double);
        // rect.GetWidth()
        double GetWidth(void) const;
        // rect.SetWidth(width)
        void SetWidth(double);
        // rect.GetHeight()
        double GetHeight(void) const;
        // rect.SetHeight(height)
        void SetHeight(double);
        // (SDL_Rect)rect
        // Converts the rectangle data to an SDL_Rect.  As long as you use the
        // classes, you shouldn't need to use this very often.
        operator SDL_Rect(void) const;
        /*** CONVENIENT ACCESSORS ***/
        /* All of these accessors move their respective side, but maintain the width and height. */
        double GetTop(void) const;
        void SetTop(double);
        double GetBottom(void) const;
        void SetBottom(double);
        double GetLeft(void) const;
        void SetLeft(double);
        double GetRight(void) const;
        void SetRight(double);
        ~Rect() {};
    };
}

#endif
