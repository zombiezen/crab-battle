/*
 *  PlayerSelect.cpp
 *  Crab Battle
 *
 *  Created by TJ Ferrell on 5/27/08.
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

#include "PlayerSelect.h"
#include "GameState.h"
#include "constants.h"
#include "util.h"
#include "exceptions.h"
#include <fstream>
#include <iostream>
#include <string>

using CrabBattle::PlayerSelect;
using namespace std;

const int kPlayerTopMargin = 99;
const int kPlayerSideMargin = 64;
const int kPlayerMargin = 32;
const int kElementMargin = 8;

PlayerSelect::PlayerSelect()
{
    vector<string> config;
    vector<string>::const_iterator i;
    
    // Load selection images
    config = LoadConfigFile("pselect-paths.txt");
    background = new Surface(config[0]);
    choice = new Surface(config[1]);
    ready = new Surface(config[2]);
    music = Mix_LoadMUS(config[3].c_str());
    if (music == NULL)
        throw FileNotFoundError(config[3].c_str());
    // Read player file
    config = LoadConfigFile("players.txt");
    // Load images (left side only)
    for (i = config.begin() + 1; i < config.end(); i += 2)
    {
        players.push_back(new Surface(*i));
    }
    // Tell ourselves to be patient
    p1Choice = p2Choice = 0;
    p1Done = p2Done = false;
    goBack = false;
    // Start music
    Mix_PlayMusic(music, -1);
}
    
void PlayerSelect::HandleEvent(SDL_Event evt)
{
    if (evt.type == SDL_KEYDOWN)
    {
        switch (evt.key.keysym.sym)
        {
            case SDLK_SPACE:
                p1Done = !p1Done;
                break;
            case SDLK_RETURN:
                p2Done = !p2Done;
                break;
            case SDLK_w:
                if (p1Choice > 0 && !p1Done)
                    p1Choice--;
                break;
            case SDLK_s:
                if (p1Choice < players.size() - 1 && !p1Done)
                    p1Choice++;
                break;
            case SDLK_UP:
                if (p2Choice > 0 && !p2Done)
                    p2Choice--;
                break;
            case SDLK_DOWN:
                if (p2Choice < players.size() - 1 && !p2Done)
                    p2Choice++;
                break;
            case SDLK_ESCAPE:
                goBack = true;
                break;
            default:
                break;
        }
    }
}
CrabBattle::State *PlayerSelect::Update(void)
{
    if (goBack)
    {
        return NULL;
    }
    else if (p1Done && p2Done)
    {
        return new GameState(p1Choice, p2Choice);
    }
    else
        return this;
}

void PlayerSelect::Display(Surface *screen)
{
    vector<Surface *>::const_iterator i;
    Rect pos, elemPos;
    int currY = kPlayerTopMargin;
    
    screen->Fill(screen->GetRect(), 0, 0, 0); // Clear screen
    screen->Blit(background, screen->GetRect()); // Display background
    for (i = players.begin(); i < players.end(); i++)
    {
        // Blit Side 1
        pos = Rect(kPlayerSideMargin, currY, (*i)->GetWidth(), (*i)->GetHeight());
        if ((i - players.begin()) == p1Choice)
        {
            if (p1Done)
            {
                screen->Blit(ready,
                             pos.GetRight() + kElementMargin,
                             pos.GetVerticalCenter() - ready->GetHeight() / 2.0);
            }
            else
            {
                screen->Blit(choice,
                             pos.GetRight() + kElementMargin,
                             pos.GetVerticalCenter() - choice->GetHeight() / 2.0);
            }
        }
        screen->Blit((*i), pos);
        // Blit Side 2
        pos = Rect(kScreenWidth - kPlayerSideMargin - (*i)->GetWidth(), currY,
                   (*i)->GetWidth(), (*i)->GetHeight());
        if ((i - players.begin()) == p2Choice)
        {
            if (p2Done)
            {
                screen->Blit(ready,
                             pos.GetLeft() - kElementMargin - ready->GetWidth(),
                             pos.GetVerticalCenter() - ready->GetHeight() / 2.0);
            }
            else
            {
                screen->Blit(choice,
                             pos.GetLeft() - kElementMargin - choice->GetWidth(),
                             pos.GetVerticalCenter() - choice->GetHeight() / 2.0);
            }
        }
        screen->Blit((*i), pos);
        // Advance to next position
        currY += pos.GetHeight() + kPlayerMargin;
    }
    screen->Flip(); // Flips second buffer
}

PlayerSelect::~PlayerSelect(void)
{
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    vector<Surface *>::const_iterator i;
    
    for (i = players.begin(); i < players.end(); i++)
        (*i)->DelRef();
    background->DelRef();
}
