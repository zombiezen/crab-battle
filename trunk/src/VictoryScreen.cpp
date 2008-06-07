/*
 *  VictoryScreen.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 5/28/08.
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
 
#include "VictoryScreen.h"

using namespace std;

using CrabBattle::VictoryScreen;

VictoryScreen::VictoryScreen(unsigned short winner)
{
    applauseSfx = new SoundEffect("audio/applause.ogg");
    applauseSfx->Play();
    // Load image
    switch (winner)
    {
        case 1:
            background = new Surface("images/victory_p1.png");
            break;
        case 2:
            background = new Surface("images/victory_p2.png");
            break;
        default:
            background = new Surface("images/victory_p1.png");
            break;
    }
    // Tell ourselves to be patient
    done = false;
}

void VictoryScreen::HandleEvent(SDL_Event evt)
{
    if (evt.type == SDL_KEYDOWN)
    {
        switch (evt.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                done = true;
                break;
            default:
                break;
        }
    }
    else if (evt.type == SDL_MOUSEBUTTONDOWN)
    {
        done = true;
    }
}

CrabBattle::State *VictoryScreen::Update(void)
{
    if (done)
        return new JumpState(0);
    else
        return this;
}

void VictoryScreen::Display(Surface *screen)
{
    screen->Fill(screen->GetRect(), 0, 0, 0); // Clears screen
    screen->Blit(background, background->GetRect()); // Blits the background
    screen->Flip(); // Flips second buffer
}

VictoryScreen::~VictoryScreen(void)
{
    applauseSfx->DelRef();
    background->DelRef();
}
