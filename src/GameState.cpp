/*
 *  GameState.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 3/15/08.
 *  $Id$
 */

#include "GameState.h"
#include "constants.h"

using CrabBattle::GameState;

const unsigned short kBoxSpeed = 20;

GameState::GameState(void)
{
#ifdef NO_SDL_IMAGE
    SDL_Surface *bg, *p1, *p2;
#endif
    
    // Set up player rectangles
    pcRect1 = Rect(160, 300, 64, 64);
    pcRect2 = Rect(400, 300, 64, 64);
    // Load images
#ifndef NO_SDL_IMAGE
    background = new Surface("images/bg.jpg");
    player1 = new Surface("images/player.bmp");
    player2 = new Surface("images/player2.bmp");
#else
    bg = SDL_LoadBMP("images/bg.bmp");
    p1 = SDL_LoadBMP("images/player.bmp");
    p2 = SDL_LoadBMP("images/player2.bmp");
    // Put into objects
    background = new Surface(bg);
    player1 = new Surface(p1);
    player2 = new Surface(p2);
    // Decrement surface reference counts (Surface class automatically increments)
    SDL_FreeSurface(bg);
    SDL_FreeSurface(p1);
    SDL_FreeSurface(p2);
#endif
}

void GameState::HandleEvent(SDL_Event evt)
{
}

CrabBattle::State *GameState::Update(void)
{
    Uint8 *key;
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
    return NULL;
}

void GameState::Display(Surface *screen)
{
    screen->Fill(screen->GetRect(), 0, 0, 0); // Clears screen
    screen->Blit(background, background->GetRect()); // Blits the background
    screen->Blit(player1, pcRect1); // Blits player 1 image at pcRect
    screen->Blit(player2, pcRect2); // Blits player 2 image at pcRect2
    screen->Flip(); // Flips second buffer
}

GameState::~GameState(void)
{
    background->DelRef();
    player1->DelRef();
    player2->DelRef();
}
