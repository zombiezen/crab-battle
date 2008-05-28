/*
 *  PlayerSelect.cpp
 *  Crab Battle
 *
 *  Created by TJ Ferrell on 5/27/08.
 *  $Id$
 */

#include "PlayerSelect.h"
#include "constants.h"
#include "exceptions.h"
#include <fstream>
#include <iostream>

using CrabBattle::PlayerSelect;
using namespace std;

PlayerSelect::PlayerSelect()
{
    using CrabBattle::FileNotFoundError;
#ifdef NO_SDL_IMAGE
    SDL_Surface *bg, *chuckNorris, *mudkips, *zim;
#endif
    int count = 0;
    char value1[MAXPATHLEN];
    char value2[MAXPATHLEN];
    char value3[MAXPATHLEN];
    char value4[MAXPATHLEN];
    char value5[MAXPATHLEN];
    
    // Read file
    ifstream getTitles;
    getTitles.open("PlayerSelection.txt");
    
    if (!getTitles.is_open())  // if failed to open file
    {
        throw FileNotFoundError("PlayerSelection.txt");
    }
    
    //hard coded for base implementation
    getTitles >> value1;
    count++;
    getTitles >> value2;
    count++;
    getTitles >> value3;
    count++;
    getTitles >> value4;
    count++;
    getTitles >> value5;
    
    cout << value1 << endl<< value2 <<endl<< value3<<endl;
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
    chuckNorris = new Surface(value2);
    mudkips = new Surface(value3);
    zim = new Surface(value4);
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
    
void PlayerSelect::HandleEvent(SDL_Event evt)
{
    
}
CrabBattle::State *PlayerSelect::Update(void)
{
    if (done)
        return NULL;
    else
        return this;
}
void PlayerSelect::Display(Surface *screen)
{
    screen->Fill(screen->GetRect(), 0, 0, 0); // Clears screen
    screen->Blit(background, background->GetRect()); // Blits the background
    screen->Flip(); // Flips second buffer
}
PlayerSelect::~PlayerSelect(void)
{
    background->DelRef();
}
