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
#include "exceptions.h"
#include "util.h"
#include <fstream>
#include <iostream>

using namespace std;

using CrabBattle::MenuState;

MenuState::MenuState(void)
{
    using CrabBattle::FileNotFoundError;
    int count =0;
    vector<string> paths; 
    ifstream getTitles;
    
    font = TTF_OpenFont("times.ttf", 24);
    if (font == NULL)
        throw FileNotFoundError("times.ttf");
    messPc1 = TTF_RenderText_Solid( font,"New Game", textColor );
    messPc2 = TTF_RenderText_Solid( font, "Quit", textColor );
    startRect = Rect(300, 300, 200, 30);
    quitRect = Rect(300, 330, 200, 30);
    choiceRect = Rect(250, 300, 200, 30);
    paths = LoadConfigFile("titles-menu.txt");
    // Load images
    background = new Surface(paths[0]);
    choice = new Surface(paths[1]);
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
                if (choiceRect.GetY() == 300)
                    choiceRect.SetY(330);
                else
                    choiceRect.SetY(300);
                break;
           case SDLK_RETURN:
           case SDLK_KP_ENTER:
                if (choiceRect.GetY()==300)
                    action = 1;
                else
                    action = 2;
                break;
            default:
                break;
        }
    }
}

SDL_Surface *MenuState::render(double dh)
{
    SDL_Surface *temp;
    outs << dh;
    sOutput = outs.str();
    if (sOutput == "0" && dh != 0)
        sOutput = "200";
    outs.str("");
    temp = TTF_RenderText_Solid( font, sOutput.c_str(), textColor );
    return temp;
}

SDL_Surface *MenuState::render(const char * dh)
{
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
        case 0:
            return this;
        case 1:
            action = 0;
            return (new GameState());
        case 2:
            action = 0;
            quit_event.type = SDL_QUIT;
            SDL_PushEvent(&quit_event);
            return this;
        default:
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