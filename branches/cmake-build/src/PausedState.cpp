/*
 *  PausedState.cpp
 *  Crab Battle
 *
 *  Created by Ephraim Ruprecht on 3/19/08.
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
 
#include "PausedState.h"
#include "constants.h"
#include "exceptions.h"
#include <fstream>
#include <iostream>

using namespace std;

using CrabBattle::PausedState;

PausedState::PausedState()
{
    using CrabBattle::FileNotFoundError;
#ifdef NO_SDL_IMAGE
    SDL_Surface *bg, *p1, *p2;
#endif
    int count = 0;
    char value1[MAXPATHLEN];
    char value2[MAXPATHLEN];
    char value3[MAXPATHLEN];
    char value4[MAXPATHLEN];
    
    // Read file
    ifstream getTitles;
    getTitles.open("pause-paths.txt");

    if (!getTitles.is_open())  // if failed to open file
    {
        throw FileNotFoundError("pause-paths.txt");
    }

    //hard coded for base implementation
    getTitles >> value1;
    count++;
    getTitles >> value2;
    count++;
    getTitles >> value3;
    count++;
    getTitles >> value4;

    cout << value1 << endl<< value2 <<endl<< value3<<endl;
    /*
    while (getTitles.good())   // while input good and not at EOF
    {
        count++;
        cout << value <<endl;
        getTitles >> value;    // get next value
    }
    */
    if (getTitles.eof())
        cout << "End of file reached.\n";
    else if (getTitles.fail())
        cout << "Input terminated by data mismatch.\n";
    else
        cout << "Input terminated for unknown reason.\n";
    if (count == 0)
        cout << "No data processed.\n";
    else
    {
        cout << "# items read: " << count << endl;
    }
    getTitles.close();
    
    // Load images
#ifndef NO_SDL_IMAGE
    background = new Surface(value1);
#else
    bg = SDL_LoadBMP(value1);
    // Put into objects
    background = new Surface(bg);
    // Decrement surface reference counts (Surface class automatically increments)
    SDL_FreeSurface(bg);
#endif
    // Tell ourselves to be patient
    done = false;
}

void PausedState::HandleEvent(SDL_Event evt)
{
    if (evt.type == SDL_KEYDOWN)
    {
        switch (evt.key.keysym.sym)
        {
            case SDLK_ESCAPE:
            case SDLK_p:
                done = true;
                break;
            default:
                break;
        }
    }
}

CrabBattle::State *PausedState::Update(void)
{
    if (done)
        return NULL;
    else
        return this;
}

void PausedState::Display(Surface *screen)
{
    screen->Fill(screen->GetRect(), 0, 0, 0); // Clears screen
    screen->Blit(background, background->GetRect()); // Blits the background
    screen->Flip(); // Flips second buffer
}

PausedState::~PausedState(void)
{
    background->DelRef();
}
