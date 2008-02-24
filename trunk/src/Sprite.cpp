/*
 *  Sprite.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 2/23/08.
 *  $Id$
 */

#include "Sprite.h"

using CrabBattle::Sprite;
using CrabBattle::Rect;
using CrabBattle::Surface;

Sprite::Sprite(void)
{
    x = y = 0.0;
    surface = new Surface(32, 32);
    created_surface = true;
}

Sprite::Sprite(Surface *surf)
{
    x = y = 0.0;
    surface = surf;
    created_surface = false;
}

Sprite::Sprite(Surface *surf, Rect pos)
{
    x = pos.GetX();
    y = pos.GetY();
    surface = surf;
    created_surface = false;
}

Rect Sprite::GetPosition(void)
{
    return Rect(x, y, surface->GetWidth(), surface->GetHeight());
}

void Sprite::SetPosition(Rect pos)
{
    x = pos.GetX();
    y = pos.GetY();
}

Surface *Sprite::GetSurface(void)
{
    return surface;
}

void Sprite::SetSurface(Surface *surf)
{
    if (created_surface)
        delete surface;
    surface = surf;
    created_surface = false;
}

void Sprite::Display(Surface *dest)
{
    dest->Blit(surface, GetPosition());
}

Sprite::~Sprite(void)
{
    SetSurface(NULL);
}