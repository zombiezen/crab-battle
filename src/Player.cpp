/*
 *  Player.cpp
 *  Crab Battle
 *
 *  Created by Ephraim Ruprecht on 4/25/08.
 *  $Id$
 */
 
#include "Player.h"

using CrabBattle::Sprite;
using CrabBattle::Player;

Player::Player(Surface *surf) : Sprite(surf)
{
    hp = 200;
    wins = 0;   
}

Player::Player(Surface *surf, Rect rect) : Sprite(surf, rect)
{
    hp = 200;
    wins = 0;
}

double Player::GetHp(void)
{
    return hp;
}

void Player::ModHp(double dh)
{
    hp += dh;
}

void Player::SetHp(double dh)
{
    hp = dh;
}

double Player::GetWins(void)
{
    return wins;
}

void Player::AddWins(double dw)
{
    wins += dw;
}
