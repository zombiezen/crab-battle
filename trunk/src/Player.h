/*
 *  Player.h
 *  Crab Battle
 *
 *  Created by Ephraim Ruprecht on 4/25/08.
 *  $Id:
 */
 
#include "SDL.h"
#include "BaseObject.h"
#include "Rect.h"

#ifndef _Player_H_
#define _Player_H_

namespace CrabBattle{
    
class Player : public Rect
{
    private:
        double hp, wins;   
                
    public:    
        Player(void);
        Player(double, double);
        Player(double, double, double, double);
        double GetHp(void);
        void ModHp(double);
        void SetHp(double);
        double GetWins(void);
        void AddWins(double);
        virtual ~Player(void) {};
    
};
      
}

#endif
