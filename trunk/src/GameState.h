/*
 *  GameState.h
 *  Crab Battle
 *
 *  Created by Ross Light on 3/15/08.
 *  $Id$
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

using namespace std;

#ifndef _CRAB_BATTLE_GAMESTATE_H_
#define _CRAB_BATTLE_GAMESTATE_H_

namespace CrabBattle
{
    class GameState : public State
    {
        private:
            Mix_Music *music;
            TTF_Font *font;
            Player *player1, *player2;
            vector<Sprite *> envsprites;
            SDL_Surface *messPc1, *messPc2, *lives1, *lives2;
            Rect hpRect1, hpRect2 , hptext1, hptext2, winsRect1, winsRect2;
            Surface *background, *healthbar1;
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
            GameState(void);
            virtual void HandleEvent(SDL_Event);
            virtual State *Update(void);
            virtual void Display(Surface *);
            virtual ~GameState(void);
    };
}

#endif
