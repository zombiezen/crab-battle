/*
 *  Player.h
 *  Crab Battle
 *
 *  Created by Ephraim Ruprecht on 4/25/08.
 *  $Id$
 */
 
#include "SDL.h"
#include "Sprite.h"

#ifndef _CRAB_BATTLE_PLAYER_H_
#define _CRAB_BATTLE_PLAYER_H_

namespace CrabBattle
{
    class Player : public Sprite
    {
        private:
            double hp, wins;
        public:    
            Player(Surface *);
            Player(Surface *, Rect);
            double GetHp(void);
            void ModHp(double);
            void SetHp(double);
            double GetWins(void);
            void AddWins(double);
            virtual ~Player(void) {};
    };
}

#endif
