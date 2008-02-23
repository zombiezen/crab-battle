/*
 *  Rect.h
 *  Crab Battle
 *
 *  Created by Ross Light on 2/23/08.
 *  $Id$
 */

#include "SDL.h"

#ifndef _CRAB_BATTLE_RECT_H_
#define _CRAB_BATTLE_RECT_H_

namespace CrabBattle
{
    /* Rectangle class
     *
     * For simplicity, all rectangles use the top-left for the origin.  Yes, I know
     * that's not mathematically correct, but that's what SDL does.
     */
    class Rect
    {
    private:
        double x, y, w, h;
    public:
        Rect(void);                             // Creates the (0, 0, 0, 0) rect
        Rect(double, double);                   // (0, 0, w, h)
        Rect(double, double, double, double);   // (x, y, w, h)
        double GetX(void);
        double GetY(void);
        double GetWidth(void);
        double GetHeight(void);
        SDL_Rect ConvertToSDLRect(void);
    };
}

#endif