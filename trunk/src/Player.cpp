/*
 *  Player.cpp
 *  Crab Battle
 *
 *  Created by Ephraim Ruprecht on 4/25/08.
 *  $Id$
 */
 
#include "Player.h"
#include "constants.h"

using CrabBattle::Sprite;
using CrabBattle::Player;

const short kPlayerMaxJumpCount = 2;
const short kPlayerJumpTicks = 4;
const short kPunchDamage = 5;
const unsigned short kInitialLives = 3;

const dReal kPhysicsMaxPlayerForce = 500.0;
const dReal kPhysicsPlayerVelocity = 10.0;
const dReal kPhysicsPlayerMidairVelocity = 5.0;
const dReal kPhysicsPlayerJumpVelocity = 10.0;

Player::Player(Surface *newSurfL, Surface *newSurfR) : Sprite(newSurfR)
{
    lSurf = newSurfL;
    rSurf = newSurfR;
    lSurf->AddRef();
    rSurf->AddRef();
    hp = 200;
    lives = kInitialLives;
    jumpCount = -1;
    jumpTicks = -1;
    jumpTouchedOff = false;
    direction = 1;
}

Player::Player(Surface *newSurfL, Surface *newSurfR, Rect rect) : Sprite(newSurfR, rect)
{
    lSurf = newSurfL;
    rSurf = newSurfR;
    lSurf->AddRef();
    rSurf->AddRef();
    hp = 200;
    lives = kInitialLives;
    jumpCount = -1;
    jumpTicks = -1;
    jumpTouchedOff = false;
    direction = 1;
}

int Player::GetHp(void)
{
    return hp;
}

void Player::ModHp(int dh)
{
    hp += dh;
    while (hp <= 0)
    {
        hp += 200;
        if (lives != 0)
            lives--;
    }
}

void Player::SetHp(int dh)
{
    hp = dh;
    while (hp <= 0)
    {
        hp += 200;
        if (lives != 0)
            lives--;
    }
}

unsigned short Player::GetLives(void)
{
    return lives;
}

void Player::SetLives(unsigned short newCount)
{
    lives = newCount;
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
        // We're in mid-air, hinder X movement
        if (motor->getParam(dParamVel) > 0.0)
        {
            motor->setParam(dParamFMax, kPhysicsMaxPlayerForce);
            motor->setParam(dParamVel, kPhysicsPlayerMidairVelocity);
        }
        else if (motor->getParam(dParamVel) < 0.0)
        {
            motor->setParam(dParamFMax, kPhysicsMaxPlayerForce);
            motor->setParam(dParamVel, -kPhysicsPlayerMidairVelocity);
        }
        else
        {
            // No movement, allow free fall!
            motor->setParam(dParamFMax, 0.0);
        }
        jumpTouchedOff = true;
    }
    else
    {
        // We're colliding with something, allow X movement
        motor->setParam(dParamFMax, kPhysicsMaxPlayerForce);
        // Un-hinder X movement
        if (motor->getParam(dParamVel) > 0.0)
            motor->setParam(dParamVel, kPhysicsPlayerVelocity);
        else if (motor->getParam(dParamVel) < 0.0)
            motor->setParam(dParamVel, -kPhysicsPlayerVelocity);
        // Check if we're colliding with environment, if so, allow jumping
        for (i = colliders.begin(); i < colliders.end(); i++)
        {
            currSprite = (Sprite *)(*i);
            if (currSprite == NULL || currSprite->GetIsEnv())
                anyenv = true;
        }
        if (anyenv && jumpTouchedOff)
        {
            // If we're on ground, allow jumping
            // (We check on jumpTicks to ensure that this isn't a remnant
            // collision)
            jumpCount = 0;
            jumpTouchedOff = false;
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
    TurnLeft();
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
    TurnRight();
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

void Player::TurnLeft(void)
{
    SetSurface(lSurf);
    direction = -1;
}

void Player::TurnRight(void)
{
    SetSurface(rSurf);
    direction = 1;
}

void Player::Punch(void)
{
    std::vector<Sprite *>::const_iterator i;
    Player *otherPlayer;
    Rect pos1, pos2;
    for (i = colliders.begin(); i < colliders.end(); i++)
    {
        otherPlayer = dynamic_cast<Player *>(*i);
        if (otherPlayer != NULL)
        {
            pos1 = GetPosition();
            pos2 = otherPlayer->GetPosition();
            if (pos1.GetY() - kDamageHeightTolerance * kPhysicsScreenScale <= pos2.GetY() &&
                pos1.GetY() + kDamageHeightTolerance * kPhysicsScreenScale >= pos2.GetY() &&
                ((direction == 1 && pos1.GetX() <= pos2.GetX()) ||
                 (direction == -1 && pos1.GetX() >= pos2.GetX())))
            {
                otherPlayer->ModHp(-kPunchDamage);
            }
        }
    }
}

Player::~Player(void)
{
    lSurf->DelRef();
    rSurf->DelRef();
    delete motor;
}
