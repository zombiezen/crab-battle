/*
 *  Player.cpp
 *  Crab Battle
 *
 *  Created by Ephraim Ruprecht on 4/25/08.
 *  $Id$
 */
 
#include "Player.h"

using CrabBattle::BaseObject;
using CrabBattle::Rect;
using CrabBattle::Player;

Player::Player(void)
{
    hp = 200;
    wins = 0;   
}

Player::Player(double width, double height) : Rect(width, height)
{
    hp = 200;
    wins = 0;
}

Player::Player(double dx, double dy, double width, double height) : Rect(dx, dy, width, height)
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
