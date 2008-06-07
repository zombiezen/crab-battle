/*
 *  constants.h
 *  Crab Battle
 *
 *  Created by Ross Light on 3/15/08.
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

#include <sys/param.h> // for MAXPATHLEN
#include <cmath>

#ifndef _CRAB_BATTLE_CONSTANTS_H_
#define _CRAB_BATTLE_CONSTANTS_H_

#define deg2rad(deg) ((deg) / 180.0 * M_PI)
#define rad2deg(rad) ((rad) / M_PI * 180.0)

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

const unsigned short kUpdateRate = 33; // in ms
const int kScreenWidth = 640; // in pixels
const int kScreenHeight = 480; // in pixels
const double kPhysicsScreenScale = 32.0; // pixels over meters
const SDL_Color textColor = { 255, 255, 255 };
const double kPhysicsFloor = 439.0;

const double kDamageHeightTolerance = 0.25; // in meters

#ifndef MAXPATHLEN
#define MAXPATHLEN 512 // a reasonable assumption, I hope :D
#endif

#endif
