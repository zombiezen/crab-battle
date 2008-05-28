/*
 *  constants.h
 *  Crab Battle
 *
 *  Created by Ross Light on 3/15/08.
 *  $Id$
 */

#include <sys/param.h> // for MAXPATHLEN

#ifndef _CRAB_BATTLE_CONSTANTS_H_
#define _CRAB_BATTLE_CONSTANTS_H_

const unsigned short kUpdateRate = 33; // in ms
const int kScreenWidth = 640; // in pixels
const int kScreenHeight = 480; // in pixels
const double kPhysicsScreenScale = 32.0; // pixels over meters
const SDL_Color textColor = { 255, 255, 255 };

#ifndef MAXPATHLEN
#define MAXPATHLEN 512 // a reasonable assumption, I hope :D
#endif

#endif