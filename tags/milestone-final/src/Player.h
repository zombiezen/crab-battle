/*
 *  Player.h
 *  Crab Battle
 *
 *  Created by Ephraim Ruprecht on 4/25/08.
 *  $Id$
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
