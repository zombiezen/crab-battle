/*
 *  main.cpp
 *  Crab Battle
 *
 *  Created by TJ Ferrell on 2/22/08.
 *  $Id$
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "SDL.h"
#include "GameState.h"
#include "State.h"
#include "Surface.h"
#include "constants.h"

using namespace std;
using namespace CrabBattle;

// CONSTANTS //

// Program initialization constants
const Uint32 kMainInitFlags = SDL_INIT_VIDEO;
const Uint32 kMainVideoFlags = SDL_SWSURFACE | SDL_DOUBLEBUF;
const int kMainBitsPerPixel = 0;

// Our wonderful main function
// The extern "C" is necessary so that mac_main and SDL can get access to it
// Windows sucks, so this undef-ing main kludge makes it so it runs on Windows.
#if (defined(__WIN32__) || defined(WINDOWS)) && defined(main)
#undef main
#endif
extern "C" int main(int argc, char *argv[])
{
    SDL_Surface *screen;
    bool done = false;
    SDL_Event event;
    Surface *screenObj = NULL;
    State *state = NULL, *newState = NULL;
    
    Uint32 cumulativeTime = 0;
    Uint32 lastTime = 0, currentTime = 0, deltaTime = 0;
        
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
    state = new GameState();
    while (!done)
    {
        // Switch states, if necessary
        if (newState != NULL)
            state = newState;
        // Get events
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
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                done = true; 
            }
            else
            {
                state->HandleEvent(event);
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
            newState = state->Update();
        }
        // Get ready for next timer loop
        lastTime = currentTime;
        // Draw
        state->Display(screenObj);
    }
    
    // Clean up the SDL library
    SDL_Quit();
    return 0;
}
