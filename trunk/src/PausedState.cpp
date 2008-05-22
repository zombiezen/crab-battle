/*
 *  PausedState.cpp
 *  Crab Battle
 *
 *  Created by Ephraim Ruprecht on 3/19/08.
 *  $Id$
 */
 
#include "PausedState.h"
#include "constants.h"
#include "exceptions.h"
#include <fstream>
#include <iostream>

using namespace std;

using CrabBattle::PausedState;

PausedState::PausedState(GameState *prev)
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
    
    // Set previous to argument
    prev->AddRef();
    previous = prev;
    // Read file
    ifstream getTitles;
    getTitles.open("titles1.txt");

    if (!getTitles.is_open())  // if failed to open file
    {
        throw FileNotFoundError("titles1.txt");
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

PausedState::PausedState(MenuState *prev)
{
    done = false;
}

void PausedState::HandleEvent(SDL_Event evt)
{
    if (evt.type == SDL_KEYDOWN)
    {
        switch (evt.key.keysym.sym)
        {
            case SDLK_p:
                done = true;
                break;
        }
    }
}

CrabBattle::State *PausedState::Update(void)
{
    /*
    if(qwe)
    {
        previous1->AddRef();
        return previous1;
    }*/
    if (done)
    {
        previous->AddRef(); // for main.cpp ownership
        return previous;
    }
    else
        return NULL;
}

void PausedState::Display(Surface *screen)
{
    screen->Fill(screen->GetRect(), 0, 0, 0); // Clears screen
    screen->Blit(background, background->GetRect()); // Blits the background
    screen->Flip(); // Flips second buffer
}

PausedState::~PausedState(void)
{
    previous->DelRef();
    background->DelRef();
}
