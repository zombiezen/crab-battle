/*
 *  Sprite.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 2/23/08.
 *  $Id$
 */

#include "Sprite.h"
#include "constants.h"

using CrabBattle::BaseObject;
using CrabBattle::Sprite;
using CrabBattle::Rect;
using CrabBattle::Surface;

Sprite::Sprite(Surface *surf)
{
    x = y = 0.0;
    surface = surf;
    surface->AddRef();
    body = NULL;
    geometry = NULL;
}

Sprite::Sprite(Surface *surf, Rect pos)
{
    x = pos.GetX();
    y = pos.GetY();
    surface = surf;
    surface->AddRef();
    body = NULL;
    geometry = NULL;
}

Rect Sprite::GetPosition(void)
{
    Rect posRect = Rect(surface->GetWidth(), surface->GetHeight());
    const dReal *pos;
    if (body == NULL)
    {
        posRect.SetX(x);
        posRect.SetY(y);
    }
    else
    {
        pos = body->getPosition();
        posRect.SetX(pos[0] * kPhysicsScreenScale - posRect.GetWidth() / 2);
        posRect.SetY(pos[1] * kPhysicsScreenScale - posRect.GetHeight() / 2);
    }
    return posRect;
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

dBody *Sprite::GetBody(void)
{
    return body;
}

void Sprite::SetBody(dBody *newBody)
{
    if (body != NULL)
        delete body;
    body = newBody;
}

dGeom *Sprite::GetGeometry(void)
{
    return geometry;
}

void Sprite::SetGeometry(dGeom *newGeom)
{
    if (geometry != NULL)
        delete geometry;
    geometry = newGeom;
}

void Sprite::Display(Surface *dest)
{
    dest->Blit(surface, GetPosition());
}

Sprite::~Sprite(void)
{
    SetSurface(NULL);
    SetBody(NULL);
    SetGeometry(NULL);
}
