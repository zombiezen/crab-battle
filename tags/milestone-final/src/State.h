/*
 *  State.h
 *  Crab Battle
 *
 *  Created by Ross Light on 3/15/08.
 *  $Id$
 */

#include "BaseObject.h"
#include "Surface.h"

#ifndef _CRAB_BATTLE_STATE_H_
#define _CRAB_BATTLE_STATE_H_

namespace CrabBattle
{
    /* State abstract class
     *
     * The game is consisted of multiple states, which handle different
     * functionality (i.e. paused, game, and main menu).  Each subclass of
     * state represents a different set of behaviors.
     */
    class State : public BaseObject
    {
    public:
        // state->HandleEvent(event)
        // Handle a single event polled from SDL_PollEvent
        virtual void HandleEvent(SDL_Event) = 0;
        // state->Update()
        // Updates the state after kUpdateRate amount of time.  Returns which
        // state the game should change to, or NULL if no change should be
        // made.  If a non-NULL value is returned, then the reference count
        // should be one, so ownership is passed to the main function.
        virtual State *Update(void) = 0;
        // state->Display(screen)
        // Draws the state to the surface given (usually the video surface of
        // the screen).
        virtual void Display(Surface *) = 0;
        // delete state
        // Destructor
        virtual ~State(void) {};
    };
    
    /* A special return value to go to a specific state
     *
     * If a jump state is returned from Update, then the given index in the
     * stack will be used.  If a negative index is given, then the program
     * terminates.
     */
    class JumpState : public State
    {
    private:
        short index;
    public:
        JumpState(short);
        short GetIndex(void);
        virtual void HandleEvent(SDL_Event);
        virtual State *Update(void);
        virtual void Display(Surface *);
    };
}

#endif
