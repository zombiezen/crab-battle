/*
 *  Player.h
 *  Crab Battle
 *
 *  Created by Ephraim Ruprecht on 4/25/08.
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
 
#include <ode/ode.h>
#include "SDL.h"
#include "Sprite.h"

#ifndef _CRAB_BATTLE_PLAYER_H_
#define _CRAB_BATTLE_PLAYER_H_

namespace CrabBattle
{
    class Player : public Sprite
    {
        private:
            Surface *lSurf, *rSurf;
            int hp;
            unsigned short lives;
            dLMotorJoint *motor;
            short jumpCount, jumpTicks;
            bool jumpTouchedOff;
            short direction;
        public:    
            Player(Surface *, Surface *);
            Player(Surface *, Surface *, Rect);
            int GetHp(void);
            void ModHp(int);
            void SetHp(int);
            unsigned short GetLives(void);
            void SetLives(unsigned short);
            void CreateMotor(dWorld *);
            virtual void Update(void);
            void GoLeft(void);
            void StopLeft(void);
            void GoRight(void);
            void StopRight(void);
            void Jump(void);
            void TurnLeft(void);
            void TurnRight(void);
            void Punch(void);
            virtual ~Player(void);
    };
}

#endif
