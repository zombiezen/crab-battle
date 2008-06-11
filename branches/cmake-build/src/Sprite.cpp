/*
 *  Sprite.cpp
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

#include "Sprite.h"
#include <cmath>
#include "constants.h"

using CrabBattle::BaseObject;
using CrabBattle::Sprite;
using CrabBattle::InvisibleSprite;
using CrabBattle::Rect;
using CrabBattle::Surface;

const double kRotationTolerance = 2.0;

// Wonderfully absent from SDL, so lovingly stolen from Pygame
static void rotate (SDL_Surface *src, SDL_Surface *dst, Uint32 bgcolor, double sangle, double cangle)
{
    using namespace std;
    int x, y, dx, dy;
    
    Uint8 *srcpix = (Uint8*) src->pixels;
    Uint8 *dstrow = (Uint8*) dst->pixels;
    int srcpitch = src->pitch;
    int dstpitch = dst->pitch;
    
    int cy = dst->h / 2;
    int xd = ((src->w - dst->w) << 15);
    int yd = ((src->h - dst->h) << 15);
    
    int isin = (int)(sangle * 65536);
    int icos = (int)(cangle * 65536);
    
    int ax = ((dst->w) << 15) - (int)(cangle * ((dst->w - 1) << 15));
    int ay = ((dst->h) << 15) - (int)(sangle * ((dst->w - 1) << 15));
    
    int xmaxval = ((src->w) << 16) - 1;
    int ymaxval = ((src->h) << 16) - 1;
    
    switch (src->format->BytesPerPixel)
    {
    case 1:
        for (y = 0; y < dst->h; y++)
        {
            Uint8 *dstpos = (Uint8*)dstrow;
            dx = (ax + (isin * (cy - y))) + xd;
            dy = (ay - (icos * (cy - y))) + yd;
            for (x = 0; x < dst->w; x++)
            {
                if(dx < 0 || dy < 0 || dx > xmaxval || dy > ymaxval)
                    *dstpos++ = bgcolor;
                else
                    *dstpos++ = *(Uint8*)
                        (srcpix + ((dy >> 16) * srcpitch) + (dx >> 16));
                dx += icos;
                dy += isin;
            }
            dstrow += dstpitch;
        }
        break;
    case 2:
        for (y = 0; y < dst->h; y++)
        {
            Uint16 *dstpos = (Uint16*)dstrow;
            dx = (ax + (isin * (cy - y))) + xd;
            dy = (ay - (icos * (cy - y))) + yd;
            for (x = 0; x < dst->w; x++)
            {
                if (dx < 0 || dy < 0 || dx > xmaxval || dy > ymaxval)
                    *dstpos++ = bgcolor;
                else
                    *dstpos++ = *(Uint16*)
                        (srcpix + ((dy >> 16) * srcpitch) + (dx >> 16 << 1));
                dx += icos;
                dy += isin;
            }
            dstrow += dstpitch;
        }
        break;
    case 4:
        for (y = 0; y < dst->h; y++)
        {
            Uint32 *dstpos = (Uint32*)dstrow;
            dx = (ax + (isin * (cy - y))) + xd;
            dy = (ay - (icos * (cy - y))) + yd;
            for (x = 0; x < dst->w; x++)
            {
                if (dx < 0 || dy < 0 || dx > xmaxval || dy > ymaxval)
                    *dstpos++ = bgcolor;
                else
                    *dstpos++ = *(Uint32*)
                        (srcpix + ((dy >> 16) * srcpitch) + (dx >> 16 << 2));
                dx += icos;
                dy += isin;
            }
            dstrow += dstpitch;
        }
        break;
    default: /*case 3:*/
        for (y = 0; y < dst->h; y++)
        {
            Uint8 *dstpos = (Uint8*)dstrow;
            dx = (ax + (isin * (cy - y))) + xd;
            dy = (ay - (icos * (cy - y))) + yd;
            for (x = 0; x < dst->w; x++)
            {
                if (dx < 0 || dy < 0 || dx > xmaxval || dy > ymaxval)
                {
                    dstpos[0] = ((Uint8*) &bgcolor)[0];
                    dstpos[1] = ((Uint8*) &bgcolor)[1];
                    dstpos[2] = ((Uint8*) &bgcolor)[2];
                    dstpos += 3;
                }
                else
                {
                    Uint8* srcpos = (Uint8*)
                        (srcpix + ((dy >> 16) * srcpitch) + ((dx >> 16) * 3));
                    dstpos[0] = srcpos[0];
                    dstpos[1] = srcpos[1];
                    dstpos[2] = srcpos[2];
                    dstpos += 3;
                }
                dx += icos; dy += isin;
            }
            dstrow += dstpitch;
        }
        break;
    }
}

Sprite::Sprite(void)
{
    x = y = rot = 0.0;
    surface = NULL;
    body = NULL;
    geometry = NULL;
    env = false;
}

Sprite::Sprite(Surface *surf)
{
    x = y = rot = 0.0;
    surface = surf;
    surface->AddRef();
    body = NULL;
    geometry = NULL;
    env = false;
}

Sprite::Sprite(Surface *surf, Rect pos)
{
    x = pos.GetX();
    y = pos.GetY();
    rot = 0.0;
    surface = surf;
    surface->AddRef();
    body = NULL;
    geometry = NULL;
    env = false;
}

Rect Sprite::GetPosition(void)
{
    Rect posRect = Rect(surface->GetWidth(), surface->GetHeight());
    const dReal *pos;
    if (body != NULL)
    {
        pos = body->getPosition();
        posRect.SetX(pos[0] * kPhysicsScreenScale - posRect.GetWidth() / 2);
        posRect.SetY(pos[1] * kPhysicsScreenScale - posRect.GetHeight() / 2);
    }
    else if (geometry != NULL)
    {
        pos = geometry->getPosition();
        posRect.SetX(pos[0] * kPhysicsScreenScale - posRect.GetWidth() / 2);
        posRect.SetY(pos[1] * kPhysicsScreenScale - posRect.GetHeight() / 2);
    }
    else
    {
        posRect.SetX(x);
        posRect.SetY(y);
    }
    return posRect;
}

void Sprite::SetPosition(Rect pos)
{
    x = pos.GetX();
    y = pos.GetY();
}

double Sprite::GetRotation(void)
{
    using std::atan;
    const dReal *quat;
    double result;
    if (body == NULL)
    {
        result = rot;
    }
    else
    {
        quat = body->getQuaternion();
        result = atan((2 * (quat[0] * quat[3] + quat[1] * quat[2])) /
                      (1 - 2 * (quat[2] * quat[2] + quat[3] * quat[3])));
    }
    while (result >= 360.0)
        result -= 360.0;
    while (result < 0.0)
        result += 360.0;
    return result;
}

void Sprite::SetRotation(double theta)
{
    rot = theta;
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
    double w, h;
    if (body != NULL)
        delete body;
    body = newBody;
    if (body != NULL)
    {
        body->setData((void *)this);
        w = GetPosition().GetWidth();
        h = GetPosition().GetHeight();
        body->setPosition((x + (w / 2.0)) / kPhysicsScreenScale,
                          (y + (h / 2.0)) / kPhysicsScreenScale,
                          0.0);
    }
}

dGeom *Sprite::GetGeometry(void)
{
    return geometry;
}

void Sprite::SetGeometry(dGeom *newGeom)
{
    double w, h;
    if (geometry != NULL)
        delete geometry;
    geometry = newGeom;
    if (geometry != NULL)
    {
        geometry->setData((void *)this);
        w = GetPosition().GetWidth();
        h = GetPosition().GetHeight();
        if (!geometry->getBody())
        {
            geometry->setPosition((x + (w / 2.0)) / kPhysicsScreenScale,
                                  (y + (h / 2.0)) / kPhysicsScreenScale,
                                  0.0);
        }
    }
}

bool Sprite::GetIsEnv(void)
{
    return env;
}

void Sprite::SetIsEnv(bool flag)
{
    env = flag;
}

void Sprite::FixPhysics(void)
{
    const dReal *rot;
    const dReal *quat_ptr;
    dReal quat[4], quat_len;
    if (body == NULL)
        return;
    // Fix rotation
    rot = body->getAngularVel();
    quat_ptr = body->getQuaternion();
    quat[0] = quat_ptr[0];
    quat[1] = 0.0;
    quat[2] = 0.0;
    quat[3] = quat_ptr[3];
    quat_len = sqrt(quat[0] * quat[0] + quat[3] * quat[3]);
    quat[0] /= quat_len;
    quat[3] /= quat_len;
    body->setQuaternion(quat);
    body->setAngularVel(0.0, 0.0, rot[2]);
    // Fix position
//    pos = body->getPosition();
//    lvel = body->getLinearVel();
//    body->setPosition(pos[0], pos[1], 0.0);
//    body->setLinearVel(lvel[0], lvel[1], 0.0);
}

void Sprite::Display(Surface *dest)
{
    using std::sin;
    using std::cos;
    using std::fabs;
    Surface *rotsurf;
    SDL_Surface *surf = surface->GetSurface();
    Uint32 bgcolor;
    double angle, radangle, sangle, cangle;
    double cx, cy, sx, sy;
    int newx, newy, bps;
    // Calculate angle
    angle = GetRotation() + 90.0;
    while (angle >= 360.0)
        angle -= 360.0;
    if (angle < kRotationTolerance || angle > 360.0 - kRotationTolerance)
        angle = 0.0;
    else if (angle > 90.0 - kRotationTolerance && angle < 90.0 + kRotationTolerance)
        angle = 90.0;
    else if (angle > 180.0 - kRotationTolerance && angle < 180.0 + kRotationTolerance)
        angle = 180.0;
    else if (angle > 270.0 - kRotationTolerance && angle < 270.0 + kRotationTolerance)
        angle = 270.0;
    if (angle != 90.0)
    {
        radangle = deg2rad(angle);
        sangle = sin(radangle);
        cangle = cos(radangle);
        // Calculate new image size
        cx = cangle * surface->GetWidth();
        cy = cangle * surface->GetHeight();
        sx = sangle * surface->GetWidth();
        sy = sangle * surface->GetHeight();
        newx = (int) (MAX(MAX(MAX(fabs (cx + sy), fabs (cx - sy)),
                                  fabs (-cx + sy)), fabs (-cx - sy)));
        newy = (int) (MAX(MAX(MAX(fabs (sx + cy), fabs (sx - cy)),
                                  fabs (-sx + cy)), fabs (-sx - cy)));
        // Get background color
        bgcolor = SDL_MapRGBA(surf->format, 0, 0, 0, 0);
        bps = surf->format->BitsPerPixel;
        // TODO: Support alpha
        // Rotate it!
        rotsurf = new Surface(surf->flags | SDL_SRCALPHA, newx, newy, bps);
        SDL_LockSurface(rotsurf->GetSurface());
        rotate(surf, rotsurf->GetSurface(), bgcolor, cangle, sangle);
        SDL_UnlockSurface(rotsurf->GetSurface());
        // Display surface on screen
        dest->Blit(rotsurf, GetPosition());
        rotsurf->DelRef();
    }
    else
    {
        dest->Blit(surface, GetPosition());
    }
}

void Sprite::AddCollider(Sprite *collider)
{
    if (collider != NULL)
        collider->AddRef();
    colliders.push_back(collider);
}

void Sprite::ClearColliders(void)
{
    std::vector<Sprite *>::const_iterator i;
    for (i = colliders.begin(); i < colliders.end(); i++)
    {
        if ((*i) != NULL)
            ((Sprite *)*i)->DelRef();
    }
    colliders.erase(colliders.begin(), colliders.end());
}

Sprite::~Sprite(void)
{
    ClearColliders();
    SetSurface(NULL);
    SetBody(NULL);
    SetGeometry(NULL);
}

InvisibleSprite::InvisibleSprite(Rect pos)
{
    SetPosition(pos);
}

Rect InvisibleSprite::GetPosition(void)
{
    Rect posRect = Rect(width, height);
    const dReal *pos;
    if (GetBody() != NULL)
    {
        pos = GetBody()->getPosition();
        posRect.SetX(pos[0] * kPhysicsScreenScale - posRect.GetWidth() / 2);
        posRect.SetY(pos[1] * kPhysicsScreenScale - posRect.GetHeight() / 2);
    }
    else if (GetGeometry() != NULL)
    {
        pos = GetGeometry()->getPosition();
        posRect.SetX(pos[0] * kPhysicsScreenScale - posRect.GetWidth() / 2);
        posRect.SetY(pos[1] * kPhysicsScreenScale - posRect.GetHeight() / 2);
    }
    else
    {
        posRect.SetX(x);
        posRect.SetY(y);
    }
    return posRect;
}

void InvisibleSprite::SetPosition(Rect newRect)
{
    x = newRect.GetX();
    y = newRect.GetY();
    width = newRect.GetWidth();
    height = newRect.GetHeight();
}
