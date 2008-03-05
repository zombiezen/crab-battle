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
    int done;
    SDL_Event event;
    Surface *screenObj = NULL;
    Rect pcRect = Rect(0, 0, 64, 64);
    
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
    
    done = 0;
    screenObj = new Surface(screen);
    while (!done)
    {
        // Check for events
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_MOUSEMOTION:
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    break;
                case SDL_KEYDOWN:
                    // Key definitions
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        {
                            // Quit
                            done = 1;
                            break;
                        }
                        case SDLK_UP:
                        {
                            //up
                            //to be defined:)
                            break;
                        }
                        case SDLK_DOWN:
                        {
                            //down
                            //to be defined:)
                            break;
                        }
                        case SDLK_RIGHT:
                        {
                            //right
                            //to be defined :)
                            break;
                        }
                        case SDLK_LEFT:
                        {
                            //left
                            //To be defined :)
                            break;
                        }   
                    }
                    break;
                case SDL_QUIT:
                    // !DO NOT REMOVE!
                    // Terminate the loop if a QUIT event is received.
                    //
                    // If this is removed, the user cannot quit by using the
                    // close button or by other OS-specific means.
                    done = 1;
                    break;
                default:
                    break;
            }
        }
        // Update
        // Draw
        screenObj->Fill(screenObj->GetRect(), 0, 0, 255);
        screenObj->Fill(pcRect, 0, 255, 0);
        screenObj->Update(screenObj->GetRect());
    }
    
    delete screenObj;
    
    // Clean up the SDL library
    SDL_Quit();
    return(0);
}