/*
 *  Rect.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 2/23/08.
 *  $Id$
 */

#include "Rect.h"

using CrabBattle::Rect;
using CrabBattle::BaseObject;

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

void Rect::SetX(double nx)
{
    x = nx;
}

double Rect::GetY(void)
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

double Rect::GetWidth(void)
{
    return w;
}

void Rect::SetWidth(double nw)
{
    w = nw;
}

double Rect::GetHeight(void)
{
    return h;
}

void Rect::SetHeight(double nh)
{
    h = nh;
}

Rect::operator SDL_Rect(void)
{
    return (SDL_Rect){(Sint16)x, (Sint16)y, (Uint16)w, (Uint16)h};
}

double Rect::GetTop(void)
{
    return y;
}

void Rect::SetTop(double top)
{
    y = top;
}

double Rect::GetBottom(void)
{
    return y + h;
}

void Rect::SetBottom(double bottom)
{
    y = bottom - h;
}

double Rect::GetLeft(void)
{
    return x;
}

void Rect::SetLeft(double left)
{
    x = left;
}

double Rect::GetRight(void)
{
    return x + w;
}

void Rect::SetRight(double right)
{
    x = right - w;
}

Rect::~Rect(void)
{
}
