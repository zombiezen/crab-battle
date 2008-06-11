/*
 *  Rect.cpp
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

#include "Rect.h"

using CrabBattle::BaseObject;
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

double Rect::GetX(void) const
{
    return x;
}

void Rect::SetX(double nx)
{
    x = nx;
}

double Rect::GetY(void) const
{
    return y;
}

void Rect::SetY(double ny)
{
    y = ny;
}

void Rect::SetXY(double dx, double dy)
{
    x = dx;
    y = dy;   
}

void Rect::Move(double dx, double dy)
{
    x += dx;
    y += dy;
}

double Rect::GetWidth(void) const
{
    return w;
}

void Rect::SetWidth(double nw)
{
    w = nw;
}

double Rect::GetHeight(void) const
{
    return h;
}

void Rect::SetHeight(double nh)
{
    h = nh;
}

Rect::operator SDL_Rect(void) const
{
    return (SDL_Rect){(Sint16)x, (Sint16)y, (Uint16)w, (Uint16)h};
}

double Rect::GetTop(void) const
{
    return y;
}

void Rect::SetTop(double top)
{
    y = top;
}

double Rect::GetBottom(void) const
{
    return y + h;
}

void Rect::SetBottom(double bottom)
{
    y = bottom - h;
}

double Rect::GetLeft(void) const
{
    return x;
}

void Rect::SetLeft(double left)
{
    x = left;
}

double Rect::GetRight(void) const
{
    return x + w;
}

void Rect::SetRight(double right)
{
    x = right - w;
}

double Rect::GetHorizontalCenter(void) const
{
    return x + w / 2.0;
}

void Rect::SetHorizontalCenter(double newCenter)
{
    x = newCenter - w / 2.0;
}

double Rect::GetVerticalCenter(void) const
{
    return y + h / 2.0;
}

void Rect::SetVerticalCenter(double newCenter)
{
    y = newCenter - h / 2.0;
}
