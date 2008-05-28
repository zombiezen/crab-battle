/*
 *  VictoryScreen.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 5/28/08.
 *  $Id$
 */
 
#include "VictoryScreen.h"

using namespace std;

using CrabBattle::VictoryScreen;

VictoryScreen::VictoryScreen(unsigned short winner)
{
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
            case SDLK_SPACE:
                done = true;
                break;
            case SDLK_RETURN:
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
    background->DelRef();
}
