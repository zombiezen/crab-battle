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
#include <stack>

#include "SDL.h"
#if (defined(__WIN32__) || defined(WINDOWS)) || defined(MAC_OS_X)
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
#include "State.h"
#include "Surface.h"
#include "constants.h"
#include "MenuState.h"


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
    using namespace std;
    using namespace CrabBattle;
    
    SDL_Surface *screen;
    bool done = false;
    SDL_Event event;
    Surface *screenObj = NULL;
    State *newState = NULL;
    stack<State*> state_stack;
    JumpState *jump;
#if !defined(NO_SDL_IMAGE) && !defined(MAC_OS_X)
    Surface *icon = NULL;
#endif
    
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
#if !defined(NO_SDL_IMAGE) && !defined(MAC_OS_X)
    icon = new Surface("icon.png");
    SDL_WM_SetIcon(icon->GetSurface(), NULL);
#endif
    screenObj = Surface::GetVideoSurface();
    if (kMainVideoFlags & SDL_FULLSCREEN)
        SDL_ShowCursor(SDL_DISABLE);
    // Set up SDL_ttf
    TTF_Init();
    
    // Run main event loop
    state_stack.push(new MenuState());
    newState = state_stack.top();
    while (!done)
    {
        // Switch states, if necessary
        if (newState != state_stack.top())
        {
            if (newState == NULL)
            {
                state_stack.top()->DelRef();
                state_stack.pop();
            }
            else
            {
                jump = dynamic_cast<JumpState *>(newState);
                if (jump == NULL)
                {
                    // Normal state
                    // Ordinarily, we would AddRef the newState, but we own the state.
                    state_stack.push(newState);
                }
                else
                {
                    // Jump state
                    // Jump to the requested state
                    if (jump->GetIndex() < 0)
                    {
                        done = true;
                    }
                    else
                    {
                        while (state_stack.size() > jump->GetIndex() + 1)
                        {
                            state_stack.top()->DelRef();
                            state_stack.pop();
                        }
                    }
                    jump->DelRef();
                }
            }
            // Check if the game is complete
            if (state_stack.size() == 0)
                done = true;
            else
                newState = state_stack.top();
        }
        if (done)
            break;
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
                break;
            }
            else
            {
                state_stack.top()->HandleEvent(event);
            }
        }
        // Check to see whether we're done
        if (done)
            break;
        // Update timer
        currentTime = SDL_GetTicks();
        deltaTime = currentTime - lastTime;
        cumulativeTime += deltaTime;
        // Run an update if our rate has elapsed
        if (cumulativeTime > kUpdateRate)
        {
            cumulativeTime -= kUpdateRate;
            newState = state_stack.top()->Update();
        }
        // Get ready for next timer loop
        lastTime = currentTime;
        // Draw
        if (newState == state_stack.top())
        {
            state_stack.top()->Display(screenObj);
        }
    }
    
    // Clean up
    TTF_Quit();
    SDL_Quit();
    return 0;
}
