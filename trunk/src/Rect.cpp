/*
 *  Rect.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 2/23/08.
 *  $Id$
 */

#include "Rect.h"

using CrabBattle::Rect;

Rect::Rect(void)
{
    x = y = w = h = 0.0;
}

Rect::Rect(double width, double height)
{
    x = y = 0.0;
    w = width;
    h = height;
}

Rect::Rect(double ix, double iy, double width, double height)
{
    x = ix;
    y = iy;
    w = width;
    h = height;
}

double Rect::GetX(void)
{
    return x;
}

double Rect::GetY(void)
{
    return y;
}

double Rect::GetWidth(void)
{
    return w;
}

double Rect::GetHeight(void)
{
    return h;
}

SDL_Rect Rect::ConvertToSDLRect(void)
{
    return (SDL_Rect){(Sint16)x, (Sint16)y, (Uint16)w, (Uint16)h};
}