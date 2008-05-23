/*
 *  MenuState.cpp
 *  Crab Battle
 *
 *  Created by Ephraim Ruprecht on 5/21/08.
 *  $Id$
 */

#include "MenuState.h"
#include "GameState.h"
#include "constants.h"
#include <fstream>
#include <iostream>

using namespace std;

using CrabBattle::MenuState;

const unsigned short kBoxSpeed = 20;

MenuState::MenuState(void)
{
   int count =0;
   char value1[MAXPATHLEN];
   char value2[MAXPATHLEN];
   char value3[MAXPATHLEN];
   char value4[MAXPATHLEN];
   char value5[MAXPATHLEN];
   ifstream getTitles;
   TTF_Init(); //apparently extremely important
   //cout << "tff_init()= "<<TTF_WasInit()<<endl;

   font = TTF_OpenFont( "times.ttf", 24 );
   if (font == NULL)
    throw FileNotFoundError("times.ttf");
   
   messPc1 = TTF_RenderText_Solid( font,"New Game", textColor );
   messPc2 = TTF_RenderText_Solid( font, "Quit", textColor );
   startRect = Rect(300, 300, 200, 30);
   quitRect = Rect(300, 330, 200, 30);
   choiceRect = Rect(250, 300, 200, 30); 
   
   
#ifdef NO_SDL_IMAGE
   SDL_Surface *bg, *p1, *p2;
#endif
   
   getTitles.open("titles-menu.txt");

    if (!getTitles.is_open())  // if failed to open file
        throw FileNotFoundError("titles-menu.txt");
   
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
       
   cout << value1 << endl<< value2 <<endl<< value3<<endl<<value4<<endl;
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
   choice = new Surface(value2);
#else
   bg = SDL_LoadBMP(value1);
   p1 = SDL_LoadBMP(value2);
   p2 = SDL_LoadBMP(value3);
   // Put into objects
   // Decrement surface reference counts (Surface class automatically increments)
   SDL_FreeSurface(bg);
   SDL_FreeSurface(p1);
   SDL_FreeSurface(p2);
#endif
   // Don't advance yet
   action = 0;
}

void MenuState::HandleEvent(SDL_Event evt)
{
   if (evt.type == SDL_KEYDOWN)
   {
       switch (evt.key.keysym.sym)
       {
           case SDLK_w:
           case SDLK_s:
           case SDLK_UP:
           case SDLK_DOWN:
            if(choiceRect.GetY()==300)
               choiceRect.SetY(330);
            else choiceRect.SetY(300);
            break;

           case SDLK_RETURN:
           case SDLK_KP_ENTER:
                if(choiceRect.GetY()==300)
                {
                    action = 1;
                }
                else 
                {
                action = 2;
                }
                break;
       }
   }
}

SDL_Surface* MenuState::render(double dh){
   SDL_Surface *temp;
   outs << dh;
   sOutput = outs.str();
   if(sOutput == "0" && dh != 0) sOutput = "200";
   outs.str("");
   temp = TTF_RenderText_Solid( font, sOutput.c_str(), textColor );
return temp;
}

SDL_Surface* MenuState::render(const char * dh){
   SDL_Surface *temp;
   temp = TTF_RenderText_Solid( font, dh, textColor );
return temp;
}

CrabBattle::State *MenuState::Update(void)
{
    SDL_Event quit_event;
   // Switch states
    switch (action)
    {
        case 0: return this;
        case 1:
            action = 0;
            return (new GameState());
        case 2:
            action = 0;
            quit_event.type = SDL_QUIT;
            SDL_PushEvent(&quit_event);
            return this;
    }
}


void MenuState::Display(Surface *screen)
{
   screen->Fill(screen->GetRect(), 0, 0, 0); // Clears screen
   screen->Blit(background, background->GetRect()); // Blits the background
   screen->Blit(messPc1, startRect);
   screen->Blit(messPc2, quitRect);
   screen->Blit(choice, choiceRect);
   screen->Flip(); // Flips second buffer
}

MenuState::~MenuState(void)
{
   background->DelRef();
   SDL_FreeSurface(messPc1);
   SDL_FreeSurface(messPc2);
   //SDL_FreeSurface(wins2);
   TTF_CloseFont(font);
}
