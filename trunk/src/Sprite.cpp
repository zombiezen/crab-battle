/*
 *  Sprite.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 2/23/08.
 *  $Id$
 */

#include "Sprite.h"

using CrabBattle::BaseObject;
using CrabBattle::Sprite;
using CrabBattle::Rect;
using CrabBattle::Surface;

Sprite::Sprite(Surface *surf)
{
    x = y = 0.0;
    surface = surf;
    surface->AddRef();
}

Sprite::Sprite(Surface *surf, Rect pos)
{
    x = pos.GetX();
    y = pos.GetY();
    surface = surf;
    surface->AddRef();
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
    if (surface != NULL)
        surface->DelRef();
    surface = surf;
    if (surface != NULL)
        surface->AddRef();
}

void Sprite::Display(Surface *dest)
{
    dest->Blit(surface, GetPosition());
}

Sprite::~Sprite(void)
{
    SetSurface(NULL);
}
