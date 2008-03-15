/*
 *  main.cpp
 *  Crab Battle
 *
 *  Created by TJ Ferrell on 2/22/08.
 *  $Id$
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <cstring>

#include "SDL.h"
#include "Surface.h"

using namespace std;
using namespace CrabBattle;

// CONSTANTS //

// Globally useful constants
const unsigned short kUpdateRate = 33; // in ms
const int kScreenWidth = 640; // in pixels
const int kScreenHeight = 480; // in pixels

// Program initialization constants
static const Uint32 kMainInitFlags = SDL_INIT_VIDEO;
static const Uint32 kMainVideoFlags = SDL_SWSURFACE | SDL_DOUBLEBUF;
static const int kMainBitsPerPixel = 0;

// Game state-specific constants
static const unsigned short kBoxSpeed = 20;

// Our wonderful main function
// The extern "C" is necessary so that mac_main and SDL can get access to it
// Windows sucks, so this undef-ing main kludge makes it so it runs on Windows.
#if (defined(__WIN32__) || defined(WINDOWS)) && defined(main)
#undef main
#endif
extern "C" int main(int argc, char *argv[])
{
    SDL_Surface *screen;
    SDL_Surface *background, *player1, *player2;
    bool done = false;
    SDL_Event event;
    Surface *screenObj = NULL;
    Rect pcRect1 = Rect(160, 300, 64, 64);
    Rect pcRect2 = Rect(400, 300, 64, 64);
    Uint8* key;
    
    Uint32 cumulativeTime = 0;
    Uint32 lastTime = 0, currentTime = 0, deltaTime = 0;
    
    //TODO: add some sort of user input to change background image
    //      possibly in the form of if(input==2)background=LoadBMP bg2.bmp
    background = SDL_LoadBMP("images/bg.bmp");
    player1 = SDL_LoadBMP("images/player.bmp");
    player2 = SDL_LoadBMP("images/player2.bmp");
    
    // Initialize the SDL library
    if (SDL_Init(kMainInitFlags) < 0)
    {
        cerr << "Couldn't initialize SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    
    // Set video mode
    screen = SDL_SetVideoMode(kScreenWidth, kScreenHeight, kMainBitsPerPixel, kMainVideoFlags);
    if (screen == NULL)
    {
        cerr << "Couldn't set " << kScreenWidth
                         << "x" << kScreenHeight
                         << "x" << kScreenWidth;
        cerr << " video mode: " << SDL_GetError() << endl;
        SDL_Quit();
        exit(2);
    }
    
    // Set up window manager
    SDL_WM_SetCaption("Crab Battle", NULL); // Sets the title of the window
    screenObj = Surface::GetVideoSurface();
    if (kMainVideoFlags & SDL_FULLSCREEN)
        SDL_ShowCursor(SDL_DISABLE);
    
    // Run main event loop
    while (!done)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                // !DO NOT REMOVE!
                // Terminate the loop if a QUIT event is received.
                //
                // If this is removed, the user cannot quit by using the
                // close button or by other OS-specific means.
                done = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                done = true; 
            }
        }
        // Update timer
        currentTime = SDL_GetTicks();
        deltaTime = currentTime - lastTime;
        cumulativeTime += deltaTime;
        // Run an update if our rate has elapsed
        if (cumulativeTime > kUpdateRate)
        {
            cumulativeTime -= kUpdateRate;
            // Update
            key = SDL_GetKeyState(NULL); // holding down buttons repeats
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
        }
        // Get ready for next timer loop
        lastTime = currentTime;
        // Draw
        screenObj->Fill(screenObj->GetRect(), 0, 0, 0); // Clears screen
        screenObj->Blit(background); // Blits the background
        screenObj->Blit(player1, pcRect1); // Blits player 1 image at pcRect
        screenObj->Blit(player2, pcRect2); // Blits player 2 image at pcRect2
        SDL_Flip(screen); // Flips second buffer
    }
    
    // Clean up the SDL library
    SDL_Quit();
    return 0;
}
