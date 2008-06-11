/*
 *  GameState.h
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

#include <iostream>
#if (defined(__WIN32__) || defined(WINDOWS)) || defined(MAC_OS_X)
#include <SDL_ttf/SDL_ttf.h>
#include <SDL_mixer/SDL_mixer.h>
#else
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#endif
#include <ode/ode.h>
#include <vector>

#include "Rect.h"
#include "Player.h"
#include "State.h"
#include "SoundEffect.h"

using namespace std;

#ifndef _CRAB_BATTLE_GAMESTATE_H_
#define _CRAB_BATTLE_GAMESTATE_H_

namespace CrabBattle
{
    class GameState : public State
    {
        private:
            Mix_Music *music;
            SoundEffect *punchSfx, *boingSfx;
            TTF_Font *font;
            Player *player1, *player2;
            vector<Sprite *> envsprites;
            SDL_Surface *messPc1, *messPc2;
            Rect hpRect1, hpRect2 , hptext1, hptext2;
            Surface *background, *healthbar1, *heart;
            dWorld *physicsWorld;
            dSpace *physicsSpace;
            dJointGroup *allContacts;
            string sOutput;
            bool shouldPause, shouldQuit;
            unsigned int countdownTimer;
            int lastHP1, lastHP2;
            Surface *countdownSurface;
            
            friend void _game_state_collide(void *, dGeomID, dGeomID);
            
            void LoadStage(void);
            SDL_Surface* render(int dh);
        protected:
            void AddContact(dContactGeom, dGeomID, dGeomID);
        public:
            GameState(unsigned short, unsigned short);
            virtual void HandleEvent(SDL_Event);
            virtual State *Update(void);
            virtual void Display(Surface *);
            virtual ~GameState(void);
    };
}

#endif
