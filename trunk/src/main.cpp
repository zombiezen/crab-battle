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

using namespace std;

// Our wonderful main function
// The extern "C" is necessary so that mac_main and SDL can get access to it
// Windows sucks, so this undef-ing main kludge makes it so it runs on Windows.
#if (defined(__WIN32__) || defined(WINDOWS)) && defined(main)
#undef main
#endif
extern "C" int main(int argc, char *argv[])
{
    Uint32 initflags = SDL_INIT_VIDEO;  /* See documentation for details */
    SDL_Surface *screen;
    Uint8 video_bpp = 0;
    Uint32 videoflags = SDL_SWSURFACE;
    int done;
    SDL_Event event;
    
    /* Initialize the SDL library */
    if (SDL_Init(initflags) < 0)
    {
        cerr << "Couldn't initialize SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    
    /* Set 640x480 video mode */
    screen = SDL_SetVideoMode(640, 480, video_bpp, videoflags);
    if (screen == NULL)
    {
        cerr << "Couldn't set 640x480x" << video_bpp << " video mode: " << SDL_GetError() << endl;
        SDL_Quit();
        exit(2);
    }
    
    done = 0;
    while (!done)
    {
        /* Check for events */
        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
                    
                case SDL_MOUSEMOTION:
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    break;
                case SDL_KEYDOWN:
                    /* Any keypress quits the app... */
                case SDL_QUIT:
                    done = 1;
                    break;
                default:
                    break;
            }
        }
    }
    
    /* Clean up the SDL library */
    SDL_Quit();
    return(0);
}
