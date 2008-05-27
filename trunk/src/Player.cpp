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

const dReal kPhysicsMaxPlayerForce = 500.0;
const dReal kPhysicsPlayerVelocity = 10.0;
const dReal kPhysicsPlayerJumpVelocity = 5.0;

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

void Player::CreateMotor(dWorld *world)
{
    dBody *body = GetBody();
    if (body != NULL)
    {
        motor = new dLMotorJoint(world->id());
        motor->attach(body->id(), NULL);
        motor->setNumAxes(2);
        motor->setAxis(0, 0, 1.0, 0.0, 0.0);
        motor->setAxis(1, 0, 0.0, -1.0, 0.0); // SDL coordinates, remember?
        motor->setParam(dParamFMax, kPhysicsMaxPlayerForce);
        motor->setParam(dParamFMax2, 0.0);
        motor->setParam(dParamVel, 0.0);
        motor->setParam(dParamVel2, 0.0);
    }
}

void Player::GoLeft(void)
{
    if (motor != NULL)
    {
        motor->setParam(dParamVel, -kPhysicsPlayerVelocity);
    }
}

void Player::StopLeft(void)
{
    if (motor != NULL)
    {
        motor->setParam(dParamVel, 0.0);
    }
}

void Player::GoRight(void)
{
    if (motor != NULL)
    {
        motor->setParam(dParamVel, kPhysicsPlayerVelocity);
    }
}

void Player::StopRight(void)
{
    if (motor != NULL)
    {
        motor->setParam(dParamVel, 0.0);
    }
}

void Player::Jump(void)
{
    if (motor != NULL)
    {
        motor->setParam(dParamFMax2, kPhysicsMaxPlayerForce);
        motor->setParam(dParamVel2, kPhysicsPlayerJumpVelocity);
    }
}

void Player::StopJump(void)
{
    if (motor != NULL)
    {
        motor->setParam(dParamFMax2, 0.0);
        motor->setParam(dParamVel2, 0.0);
    }
}
