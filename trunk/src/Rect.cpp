/*
 *  Rect.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 2/23/08.
 *  $Id$
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
    hp = 200;
    wins = 0;
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

double Rect::GetHp(void)
{
    return hp;
}
void Rect::ModHp(double dh)
{
    hp += dh;
}
void Rect::SetHp(double dh)
{
    hp = dh;
}

double Rect::GetWins(void)
{
    return wins;
}

void Rect::AddWins(double dw)
{
    wins += dw;
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

