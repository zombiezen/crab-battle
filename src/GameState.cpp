/*
 *  GameState.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 3/15/08.
 *  $Id$
 */

#include "GameState.h"
#include "PausedState.h"
#include "constants.h"
#include <fstream>
#include <iostream>

using namespace std;

using CrabBattle::GameState;

const unsigned short kBoxSpeed = 20;

GameState::GameState(void)
{
    int count =0;
    char value1[MAXPATHLEN];
    char value2[MAXPATHLEN];
    char value3[MAXPATHLEN];
    char value4[MAXPATHLEN];
    ifstream getTitles;
#ifdef NO_SDL_IMAGE
    SDL_Surface *bg, *p1, *p2;
#endif
    
    getTitles.open("titles.txt");

    if (!getTitles.is_open())  // if failed to open file
    {
        cout << "Could not open the file " << endl;
        cout << "Program terminating.\n";
        cin.get();
        exit(EXIT_FAILURE);
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
    
    // Set up player rectangles
    pcRect1 = Rect(160, 300, 64, 64);
    pcRect2 = Rect(400, 300, 64, 64);
    // Load images
#ifndef NO_SDL_IMAGE
    background = new Surface(value1);
    player1 = new Surface(value2);
    player2 = new Surface(value3);
#else
    bg = SDL_LoadBMP(value1);
    p1 = SDL_LoadBMP(value2);
    p2 = SDL_LoadBMP(value3);
    // Put into objects
    background = new Surface(bg);
    player1 = new Surface(p1);
    player2 = new Surface(p2);
    // Decrement surface reference counts (Surface class automatically increments)
    SDL_FreeSurface(bg);
    SDL_FreeSurface(p1);
    SDL_FreeSurface(p2);
#endif
    // Don't pause yet
    shouldPause = false;
}

void GameState::HandleEvent(SDL_Event evt)
{
    if (evt.type == SDL_KEYDOWN)
    {
        switch (evt.key.keysym.sym)
        {
            case SDLK_p:
                shouldPause = true;
                break;
        }
    }
}

CrabBattle::State *GameState::Update(void)
{
    Uint8 *key;
    key = SDL_GetKeyState(NULL);
    // Check for keys
    if (key[SDLK_w])
    {
        pcRect1.Move(0, -kBoxSpeed);
        if (pcRect1.GetTop() < 0)
            pcRect1.SetTop(0);
    }
    if (key[SDLK_s])
    {
        pcRect1.Move(0, kBoxSpeed);
        if (pcRect1.GetBottom() > kScreenHeight)
            pcRect1.SetBottom(kScreenHeight);
    }
    if (key[SDLK_a])
    {
        pcRect1.Move(-kBoxSpeed, 0);
        if (pcRect1.GetLeft() < 0)
            pcRect1.SetLeft(0);
    }
    if (key[SDLK_d])
    {
        pcRect1.Move(kBoxSpeed, 0);
        if (pcRect1.GetRight() > kScreenWidth)
            pcRect1.SetRight(kScreenWidth);
    }
    if (key[SDLK_UP])
    {
        pcRect2.Move(0, -kBoxSpeed);
        if (pcRect2.GetTop() < 0)
            pcRect2.SetTop(0);
    }
    if (key[SDLK_DOWN])
    {
        pcRect2.Move(0, kBoxSpeed);
        if (pcRect2.GetBottom() > kScreenHeight)
            pcRect2.SetBottom(kScreenHeight);
    }
    if (key[SDLK_LEFT])
    {
        pcRect2.Move(-kBoxSpeed, 0);
        if (pcRect2.GetLeft() < 0)
            pcRect2.SetLeft(0);
    }
    if (key[SDLK_RIGHT])
    {
        pcRect2.Move(kBoxSpeed, 0);
        if (pcRect2.GetRight() > kScreenWidth)
            pcRect2.SetRight(kScreenWidth);
    }
    // Switch states
    if (shouldPause)
    {
        shouldPause = false;
        return (new PausedState(this));
    }
    else
        return NULL;
}

void GameState::Display(Surface *screen)
{
    screen->Fill(screen->GetRect(), 0, 0, 0); // Clears screen
    screen->Blit(background, background->GetRect()); // Blits the background
    screen->Blit(player1, pcRect1); // Blits player 1 image at pcRect
    screen->Blit(player2, pcRect2); // Blits player 2 image at pcRect2
    screen->Flip(); // Flips second buffer
}

GameState::~GameState(void)
{
    background->DelRef();
    player1->DelRef();
    player2->DelRef();
}
