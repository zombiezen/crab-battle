/*
 *  GameState.h
 *  Crab Battle
 *
 *  Created by Ross Light on 3/15/08.
 *  $Id$
 */

#include <iostream>
#include <sstream>
#if (defined(__WIN32__) || defined(WINDOWS)) || defined(MAC_OS_X)
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
#include <ode/ode.h>

#include "Rect.h"
#include "Player.h"
#include "State.h"

using namespace std;

#ifndef _CRAB_BATTLE_GAMESTATE_H_
#define _CRAB_BATTLE_GAMESTATE_H_

namespace CrabBattle
{
    class GameState : public State
    {
        private:
            TTF_Font *font;
            Player *player1, *player2;
            SDL_Surface *messPc1, *messPc2, *wins1, *wins2;
            Rect hpRect1, hpRect2 , hptext1, hptext2, winsRect1, winsRect2;
            Surface *background, *healthbar1;
            dWorld *physicsWorld;
            dSpace *physicsSpace;
            dJointGroup *allContacts;
            string sOutput;
            ostringstream outs;
            bool shouldPause;
            friend void _game_state_collide(void *, dGeomID, dGeomID);
        protected:
            void AddContact(dContactGeom, dGeomID, dGeomID);
        public:
            GameState(void);
            SDL_Surface* render(double dh);
            virtual void HandleEvent(SDL_Event);
            virtual State *Update(void);
            virtual void Display(Surface *);
            virtual ~GameState(void);
    };
}

#endif
