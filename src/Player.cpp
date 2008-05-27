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

const short kPlayerMaxJumpCount = 2;
const short kPlayerJumpTicks = 4;

const dReal kPhysicsMaxPlayerForce = 500.0;
const dReal kPhysicsPlayerVelocity = 10.0;
const dReal kPhysicsPlayerJumpVelocity = 10.0;

Player::Player(Surface *surf) : Sprite(surf)
{
    hp = 200;
    wins = 0;
    jumpCount = -1;
    jumpTicks = -1;
}

Player::Player(Surface *surf, Rect rect) : Sprite(surf, rect)
{
    hp = 200;
    wins = 0;
    jumpCount = -1;
    jumpTicks = -1;
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

void Player::Update(void)
{
    bool anyenv = false;
    std::vector<Sprite *>::const_iterator i;
    Sprite *currSprite;
    // Increment jump time counter
    if (jumpTicks >= 0)
        jumpTicks++;
    // Check to see if we're done jumping
    if (jumpTicks >= kPlayerJumpTicks || jumpTicks < 0)
    {
        // Finished jumping; stop everything
        jumpTicks = -1;
        motor->setParam(dParamFMax2, 0.0);
        motor->setParam(dParamVel2, 0.0);
    }
    else
    {
        // We're still jumping; continue jump procedure
        motor->setParam(dParamFMax2, kPhysicsMaxPlayerForce);
        motor->setParam(dParamVel2, kPhysicsPlayerJumpVelocity);
    }
    // Check collisions
    if (colliders.size() == 0)
    {
        // We're in mid-air by unknown means, disable X movement
        motor->setParam(dParamFMax, 0.0);
    }
    else
    {
        // We're colliding with something, allow X movement
        motor->setParam(dParamFMax, kPhysicsMaxPlayerForce);
        // Check if we're colliding with environment, if so, allow jumping
        for (i = colliders.begin(); i < colliders.end(); i++)
        {
            currSprite = (Sprite *)(*i);
            if (currSprite == NULL || currSprite->GetIsEnv())
                anyenv = true;
        }
        if (anyenv && (jumpTicks > 2 || jumpTicks < 0))
        {
            // If we're on ground, allow jumping
            // (We check for jumpTicks > 2 to ensure that this isn't a remnant
            // collision)
            jumpCount = 0;
        }
        else if (!anyenv && jumpCount == 0)
        {
            // If we got shoved up, disable jumping
            jumpCount = -1;
        }
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
    if (motor != NULL && jumpCount >= 0 && jumpCount < kPlayerMaxJumpCount)
    {
        jumpCount++;
        jumpTicks = 0;
    }
}
