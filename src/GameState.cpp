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
    char value5[MAXPATHLEN];
    ifstream getTitles;
    CrabBattle::Surface *surf_p1, *surf_p2;
#ifdef NO_SDL_IMAGE
    SDL_Surface *bg, *p1, *p2;
#endif
    //cout << "tff_init()= "<<TTF_WasInit()<<endl;

    font = TTF_OpenFont( "times.ttf", 24 );
    //if (font==NULL)cout<<TTF_GetError()<<endl;
    
    messPc1 = TTF_RenderText_Solid( font,"200", textColor );
    messPc2 = TTF_RenderText_Solid( font, "200", textColor );
    wins1 = TTF_RenderText_Solid( font, "0", textColor );
    wins2 = TTF_RenderText_Solid( font, "0", textColor );
    
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
    count++;
    getTitles >> value5;
        
    cout << value1 << endl<< value2 <<endl<< value3<<endl<<value4<<endl;
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
    hpRect1 = Rect(60, 30, 200, 30);
    hpRect2 = Rect(360, 30, 200, 30);
    winsRect1 = Rect(270 , 30 , 200 , 30);
    winsRect2 = Rect(315 , 30 , 200 , 30);
    // Load images
#ifndef NO_SDL_IMAGE
    background = new Surface(value1);
    surf_p1 = new Surface(value2);
    surf_p2 = new Surface(value3);
    healthbar1 = new Surface(value4);
#else
    bg = SDL_LoadBMP(value1);
    p1 = SDL_LoadBMP(value2);
    p2 = SDL_LoadBMP(value3);
    // Put into objects
    background = new Surface(bg);
    surf_p1 = new Surface(p1);
    surf_p2 = new Surface(p2);
#endif
    // Create players
    player1 = new Player(surf_p1, CrabBattle::Rect(160, 300, 64, 64));
    player2 = new Player(surf_p2, CrabBattle::Rect(400, 300, 64, 64));
    // Clean up images
    surf_p1->DelRef();
    surf_p2->DelRef();
#ifdef NO_SDL_IMAGE
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

SDL_Surface *GameState::render(double dh)
{
    SDL_Surface *temp;
    outs << dh;
    sOutput = outs.str();
    if(sOutput == "0" && dh != 0)
        sOutput = "200";
    outs.str("");
    temp = TTF_RenderText_Solid(font, sOutput.c_str(), textColor);
    return temp;
}

CrabBattle::State *GameState::Update(void)
{
    Uint8 *key;
    Rect p1rect = player1->GetPosition(), p2rect = player2->GetPosition();
    key = SDL_GetKeyState(NULL);
    if (player1->GetHp() <= 0)
    {
        player1->SetHp(200);
        player2->AddWins(1);   
    }
    if (player2->GetHp() <= 0)
    {
        player2->SetHp(200);
        player1->AddWins(1);
    }
    // Check for keys
    if (key[SDLK_q])//for testing
    {
      player1->ModHp(-1);   
      player2->ModHp(-5); 
      
      messPc1 = render(player1->GetHp());
      messPc2 = render(player2->GetHp());
      wins1 = render(player1->GetWins());
      wins2 = render(player2->GetWins());
      
    }
    if (key[SDLK_w])
    {
        p1rect.Move(0, -kBoxSpeed);
        if (p1rect.GetTop() < 0)
            p1rect.SetTop(0);
    }
    if (key[SDLK_s])
    {
        p1rect.Move(0, kBoxSpeed);
        if (p1rect.GetBottom() > kScreenHeight)
            p1rect.SetBottom(kScreenHeight);
    }
    if (key[SDLK_a])
    {
        p1rect.Move(-kBoxSpeed, 0);
        if (p1rect.GetLeft() < 0)
            p1rect.SetLeft(0);
    }
    if (key[SDLK_d])
    {
        p1rect.Move(kBoxSpeed, 0);
        if (p1rect.GetRight() > kScreenWidth)
            p1rect.SetRight(kScreenWidth);
    }
    if (key[SDLK_UP])
    {
        p2rect.Move(0, -kBoxSpeed);
        if (p2rect.GetTop() < 0)
            p2rect.SetTop(0);
    }
    if (key[SDLK_DOWN])
    {
        p2rect.Move(0, kBoxSpeed);
        if (p2rect.GetBottom() > kScreenHeight)
            p2rect.SetBottom(kScreenHeight);
    }
    if (key[SDLK_LEFT])
    {
        p2rect.Move(-kBoxSpeed, 0);
        if (p2rect.GetLeft() < 0)
            p2rect.SetLeft(0);
    }
    if (key[SDLK_RIGHT])
    {
        p2rect.Move(kBoxSpeed, 0);
        if (p2rect.GetRight() > kScreenWidth)
            p2rect.SetRight(kScreenWidth);
    }
    // Update player rectangles
    player1->SetPosition(p1rect);
    player2->SetPosition(p2rect);
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
    screen->Blit(healthbar1, hpRect1, player1->GetHp());
    screen->Blit(healthbar1, hpRect2, player2->GetHp());
    player1->Display(screen);
    player2->Display(screen);
    screen->Blit(messPc1, hpRect1);
    screen->Blit(messPc2, hpRect2);
    screen->Blit(wins1, winsRect1);
    screen->Blit(wins2, winsRect2);
    screen->Flip(); // Flips second buffer
}

GameState::~GameState(void)
{
    background->DelRef();
    player1->DelRef();
    player2->DelRef();
    healthbar1->DelRef();
    SDL_FreeSurface(messPc1);
    SDL_FreeSurface(messPc2);
    SDL_FreeSurface(wins1);
    SDL_FreeSurface(wins2);
    TTF_CloseFont(font);
}
