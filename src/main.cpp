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
    SDL_Surface *screen, *background, *player1, *player2;
    Uint8 video_bpp = 0;
    Uint32 videoflags = SDL_SWSURFACE;
    bool done = false;
    SDL_Event event;
    Surface *screenObj = NULL;
    Rect pcRect = Rect(0, 0, 64, 64);
    Rect pcRect2 = Rect(0, 0, 64, 64);
    Uint8* key;
    
       
    //TODO: add some sort of user input to change background image
    //      possibly in the form of if(input==2)background=LoadBMP bg2.bmp
    background = SDL_LoadBMP("images/bg.bmp");
    player1 = SDL_LoadBMP("images/player.bmp");
    player2 = SDL_LoadBMP("images/player2.bmp");
    
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
    
    SDL_WM_SetCaption( "Crab Battle", NULL ); //sets the title of the window
    
    screenObj = new Surface(screen);
    /*
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
                {
                    // Key definitions
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        {
                            // Quit
                            done = true;
                            break;
                        }
                        case SDLK_UP:
                        {
                            //up
                            pcRect.SetY(-10);
                            //to be defined:)
                            break;
                        }
                        case SDLK_DOWN:
                        {
                            //down
                            pcRect.SetY(10);
                            //to be defined:)
                            break;
                        }
                        case SDLK_RIGHT:
                        {
                            //right
                            pcRect.SetX(10);
                            //to be defined :)
                            break;
                        }
                        case SDLK_LEFT:
                        {
                            //left
                            pcRect.SetX(-10);
                            //To be defined :)
                            break;
                        }   
                    }
                    break;
                }
                case SDL_QUIT:
                    // !DO NOT REMOVE!
                    // Terminate the loop if a QUIT event is received.
                    //
                    // If this is removed, the user cannot quit by using the
                    // close button or by other OS-specific means.
                    done = true;
                    break;
                default:
                    break;
            }
        }*/
    pcRect.SetXY(160,300); //set initial position for Rect
    pcRect2.SetXY(400,300); //set initial position for Rect2
    
    //screenObj->Update(screenObj->GetRect());

    while(!done)
    {
    while ( SDL_PollEvent(&event) )
    {
      if ( event.type == SDL_QUIT ) 
       {
        done = 1;
        }
      if ( event.type == SDL_KEYDOWN )
      {
        if ( event.key.keysym.sym == SDLK_ESCAPE ) 
        { 
            done = 1; 
        }
      }
    }//while
    key = SDL_GetKeyState(NULL); //so holding down buttons loops
//controls for first rect
    if ( key[SDLK_w] ) 
    { 
        pcRect.Move(0, -1); 
        if(pcRect.GetY()<0)pcRect.SetY(0);
    }
    if ( key[SDLK_s] ) 
    { 
        pcRect.Move(0, 1); 
        if(pcRect.GetY()>416)pcRect.SetY(416); //480(size of screen) - 64(size of pcRect)
    }
    if ( key[SDLK_a] ) 
    { 
        pcRect.Move(-1, 0);
        if(pcRect.GetX()<0)pcRect.SetX(0);
    }
    if ( key[SDLK_d] )
    { 
        pcRect.Move(1, 0); 
        if(pcRect.GetX()>576)pcRect.SetX(576);//640(size of screen) - 64(size of pcRect)
    }
//controls for second rect
    if ( key[SDLK_UP] )
    {
        pcRect2.Move(0, -1);
        if(pcRect2.GetY()<0)pcRect2.SetY(0);
    }
    if ( key[SDLK_DOWN] )
    {
        pcRect2.Move(0, 1);
        if(pcRect2.GetY()>416)pcRect2.SetY(416); //480(size of screen) - 64(size of pcRect2)
    }
    if ( key[SDLK_LEFT] )
    {
        pcRect2.Move(-1, 0);
        if(pcRect2.GetX()<0)pcRect2.SetX(0);
    }
    if ( key[SDLK_RIGHT] )
    {
        pcRect2.Move(1, 0);
        if(pcRect2.GetX()>576)pcRect2.SetX(576);//640(size of screen) - 64(size of pcRect2)
    }

        // Update
        // TODO: insert updating code here...
        // Draw
        //screenObj->Fill(screenObj->GetRect(), 0, 0, 255);
        screenObj->Blit(background); //blits the background
        screenObj->Blit(player1, pcRect); //blits player 1 image at pcRect
        screenObj->Blit(player2, pcRect2); //blits player 2 image at pcRect2
        //screenObj->Fill(pcRect, 0, 255, 0);
        //screenObj->Fill(pcRect2, 255, 255, 255);
        SDL_Flip(screen); //flips screen buffer
        //screenObj->Update(screenObj->GetRect());
    }//while
    
    delete screenObj;
    
    // Clean up the SDL library
    SDL_Quit();
    return(0);
}
