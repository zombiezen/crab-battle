/*
 *  State.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 3/15/08.
 *  $Id$
 */

#include "State.h"

using CrabBattle::State;
using CrabBattle::JumpState;

JumpState::JumpState(short initialIndex)
{
    index = initialIndex;
}

short JumpState::GetIndex(void)
{
    return index;
}

void JumpState::HandleEvent(SDL_Event event)
{
}

State *JumpState::Update(void)
{
    return this;
}

void JumpState::Display(CrabBattle::Surface *surf)
{
}
