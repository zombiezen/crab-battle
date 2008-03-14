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

const unsigned short kUpdateRate = 33; // in ms
const unsigned short kBoxSpeed = 20;

// Our wonderful main function
// The extern "C" is necessary so that mac_main and SDL can get access to it
// Windows sucks, so this undef-ing main kludge makes it so it runs on Windows.
#if (defined(__WIN32__) || defined(WINDOWS)) && defined(main)
#undef main
#endif
extern "C" int main(int argc, char *argv[])
{
    Uint32 initflags = SDL_INIT_VIDEO;  // See documentation for details
    SDL_Surface *screen;
    Uint8 video_bpp = 0;
    Uint32 videoflags = SDL_SWSURFACE;
    bool done = false;
    SDL_Event event;
    Surface *screenObj = NULL;
    Rect pcRect1 = Rect(160, 300, 64, 64);
    Rect pcRect2 = Rect(400, 300, 64, 64);
    Uint8* key;
    
    Uint32 cumulativeTime = 0;
    Uint32 lastTime = 0, currentTime = 0, deltaTime = 0;
    
    // Initialize the SDL library
    if (SDL_Init(initflags) < 0)
    {
        cerr << "Couldn't initialize SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    
    // Set 640x480 video mode
    screen = SDL_SetVideoMode(640, 480, video_bpp, videoflags);
    if (screen == NULL)
    {
        cerr << "Couldn't set 640x480x" << video_bpp << " video mode: " << SDL_GetError() << endl;
        SDL_Quit();
        exit(2);
    }
    
    SDL_WM_SetCaption("Crab Battle", NULL); // Sets the title of the window
    
    screenObj = Surface::GetVideoSurface();
    
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
                done = 1;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                done = 1; 
            }
        }
        // Do time stuff
        currentTime = SDL_GetTicks();
        deltaTime = currentTime - lastTime;
        cumulativeTime += deltaTime;
        if (cumulativeTime > kUpdateRate)
        {
            cumulativeTime -= kUpdateRate;
            // Update
            key = SDL_GetKeyState(NULL); // holding down buttons repeats
            if (key[SDLK_w])
            {
                pcRect1.Move(0, -kBoxSpeed);
            }
            if (key[SDLK_s])
            {
                pcRect1.Move(0, kBoxSpeed);
            }
            if (key[SDLK_a])
            {
                pcRect1.Move(-kBoxSpeed, 0);
            }
            if (key[SDLK_d])
            {
                pcRect1.Move(kBoxSpeed, 0);
            }
            if (key[SDLK_UP])
            {
                pcRect2.Move(0, -kBoxSpeed);
            }
            if (key[SDLK_DOWN])
            {
                pcRect2.Move(0, kBoxSpeed);
            }
            if (key[SDLK_LEFT])
            {
                pcRect2.Move(-kBoxSpeed, 0);
            }
            if (key[SDLK_RIGHT])
            {
                pcRect2.Move(kBoxSpeed, 0);
            }
        }
        // Get ready for next timer loop
        lastTime = currentTime;
        // Draw
        screenObj->Fill(screenObj->GetRect(), 0, 0, 255);
        screenObj->Fill(pcRect1, 0, 255, 0);
        screenObj->Fill(pcRect2, 255, 255, 255);
        screenObj->Update(screenObj->GetRect());
    }//while
    
    delete screenObj;
    
    // Clean up the SDL library
    SDL_Quit();
    return(0);
}
