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
#include "exceptions.h"
#include "util.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

const unsigned int kCountdownDuration = 30;
const unsigned int kCountdownPosX = 256;
const unsigned int kCountdownPosY = 216;

// Maximum contacts per collision per iteration
const unsigned int kMaxContacts = 16;

const dReal kPhysicsGravity = 9.81;
const dReal kPhysicsCFM = 0.0;
const dReal kPhysicsERP = 0.0;

using namespace std;

using CrabBattle::GameState;

const unsigned short kBoxSpeed = 20;

namespace CrabBattle
{
    void _game_state_collide(void *data, dGeomID geom1, dGeomID geom2)
    {
        GameState *state = (GameState *)data;
        dContactGeom *contacts = NULL;
        unsigned int contact_count, i;
        
        if (dGeomIsSpace(geom1) || dGeomIsSpace(geom2))
        {
            // Check for collisions between spaces
            dSpaceCollide2(geom1, geom2, data, &_game_state_collide);
            // Check for collisions inside spaces
            if (dGeomIsSpace(geom1))
                dSpaceCollide((dSpaceID)geom1, data, &_game_state_collide);
            if (dGeomIsSpace(geom2))
                dSpaceCollide((dSpaceID)geom2, data, &_game_state_collide);
        }
        else
        {
            // Non-space geometries; check for collision
            contacts = new dContactGeom[kMaxContacts];
            contact_count = dCollide(geom1, geom2, kMaxContacts,
                                     contacts, sizeof(dContactGeom));
            for (i = 0; i < contact_count; i++)
            {
                state->AddContact(contacts[i], geom1, geom2);
            }
            delete [] contacts;
        }
    }
}

using CrabBattle::_game_state_collide;

GameState::GameState(void)
{
    using CrabBattle::FileNotFoundError;
    int count =0;
    vector<string> paths;
    CrabBattle::Surface *surf_p1L, *surf_p1R, *surf_p2L, *surf_p2R;
    CrabBattle::Sprite *sprite;
    dBody *newBody;
    dMass *newMass;
    dGeom *newGeom;
    dJointID joint2d;
    
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    music = Mix_LoadMUS( "audio/GameState.mp3" );
    Mix_PlayMusic( music, -1 );
    
    countdownTimer = 0;
    countdownSurface = NULL;
    
    font = TTF_OpenFont( "times.ttf", 24 );
    if (font == NULL)
        throw FileNotFoundError("times.ttf");
    
    lastHP1 = lastHP2 = -1;
//    messPc1 = TTF_RenderText_Solid( font,"200", textColor );
//    messPc2 = TTF_RenderText_Solid( font, "200", textColor );
//    lives1 = TTF_RenderText_Solid( font, "0", textColor );
//    lives2 = TTF_RenderText_Solid( font, "0", textColor );
    
    paths = LoadConfigFile("titles.txt");

    // Set up player rectangles
    hpRect1 = Rect(60, 30, 200, 30);
    hpRect2 = Rect(360, 30, 200, 30);
    winsRect1 = Rect(270 , 30 , 200 , 30);
    winsRect2 = Rect(315 , 30 , 200 , 30);
    // Load images
    background = new Surface(paths[0]);
    healthbar1 = new Surface(paths[1]);
    surf_p1L = new Surface(paths[2]);
    surf_p1R = new Surface(paths[3]);
    surf_p2L = new Surface(paths[6]);
    surf_p2R = new Surface(paths[7]);
    // Create players
    player1 = new Player(surf_p1L, surf_p1R, CrabBattle::Rect(160, 350, 64, 64));
    player2 = new Player(surf_p2L, surf_p2R, CrabBattle::Rect(400, 350, 64, 64));
    player1->TurnRight();
    player2->TurnLeft();
    // Clean up images
    surf_p1L->DelRef();
    surf_p1R->DelRef();
    surf_p2L->DelRef();
    surf_p2R->DelRef();
    // Don't pause yet
    shouldPause = shouldQuit = false;
    // Set up physics
    physicsWorld = new dWorld();
    physicsSpace = new dHashSpace(NULL);
    // Gravity is positive to fit with SDL screen coordinates
    physicsWorld->setGravity(0.0, kPhysicsGravity, 0.0);
    allContacts = new dJointGroup(0);
    // Player 1 Physics
    joint2d = dJointCreatePlane2D(physicsWorld->id(), NULL);
    newBody = new dBody(physicsWorld->id());
    newMass = new dMass; // yeah, this'll leak memory
    newMass->setBox(50.0,
                    64.0 / kPhysicsScreenScale,
                    64.0 / kPhysicsScreenScale,
                    1.0 / kPhysicsScreenScale);
    newBody->setMass(newMass);
    player1->SetBody(newBody);
    dJointAttach(joint2d, newBody->id(), NULL);
    // Player 1 Collision
    newGeom = new dBox(physicsSpace->id(),
                       player1->GetPosition().GetWidth() / kPhysicsScreenScale,
                       player1->GetPosition().GetHeight() / kPhysicsScreenScale,
                       1.0);
    newGeom->setBody(newBody->id());
    player1->SetGeometry(newGeom);
    // Player 1 Motor
    player1->CreateMotor(physicsWorld);
    // Player 2 Physics
    joint2d = dJointCreatePlane2D(physicsWorld->id(), NULL);
    newBody = new dBody(physicsWorld->id());
    newMass = new dMass; // yeah, this'll leak memory
    newMass->setBox(50.0,
                    64.0 / kPhysicsScreenScale,
                    64.0 / kPhysicsScreenScale,
                    1.0 / kPhysicsScreenScale);
    newBody->setMass(newMass);
    player2->SetBody(newBody);
    dJointAttach(joint2d, newBody->id(), NULL);
    // Player 2 Collision
    newGeom = new dBox(physicsSpace->id(),
                       player2->GetPosition().GetWidth() / kPhysicsScreenScale,
                       player2->GetPosition().GetHeight() / kPhysicsScreenScale,
                       1.0);
    newGeom->setBody(newBody->id());
    player2->SetGeometry(newGeom);
    // Player 2 Motor
    player2->CreateMotor(physicsWorld);
    // Floor
    newGeom = new dPlane(physicsSpace->id(),
                         0.0, -1.0, 0.0,
                         -(439 / kPhysicsScreenScale));
    // Walls
    newGeom = new dPlane(physicsSpace->id(),
                         1.0, 0.0, 0.0,
                         0.0);
    newGeom = new dPlane(physicsSpace->id(),
                         -1.0, 0.0, 0.0,
                         -(kScreenWidth / kPhysicsScreenScale));
    // Ceiling
    newGeom = new dPlane(physicsSpace->id(),
                         0.0, 1.0, 0.0,
                         0.0);
    // Platforms
    LoadStage();
}

void GameState::LoadStage(void)
{
    dGeom *newGeom;
    Sprite *sprite;
    vector<string> configRects;
    vector<string>::const_iterator i;
    double rectValues[4];
    
    configRects = LoadConfigFile("platforms.txt");
    for (i = configRects.begin(); i < configRects.end(); i++)
    {
        // Parse line
        stringstream(*i) >> rectValues[0] >> rectValues[1]
                         >> rectValues[2] >> rectValues[3];
        // Create sprite
        sprite = new InvisibleSprite(Rect(rectValues[0], rectValues[1],
                                          rectValues[2], rectValues[3]));
        newGeom = new dBox(physicsSpace->id(),
                           rectValues[2] / kPhysicsScreenScale,
                           rectValues[3] / kPhysicsScreenScale,
                           1.0);
        sprite->SetGeometry(newGeom);
        sprite->SetIsEnv(true);
        envsprites.push_back(sprite);
    }
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
            case SDLK_w:
                player1->Jump();
                break;
            case SDLK_a:
                player1->GoLeft();
                break;
            case SDLK_d:
                player1->GoRight();
                break;
            case SDLK_SPACE:
                player1->Punch();
                break;
            case SDLK_UP:
                player2->Jump();
                break;
            case SDLK_LEFT:
                player2->GoLeft();
                break;
            case SDLK_RIGHT:
                player2->GoRight();
                break;
            case SDLK_RETURN:
                player2->Punch();
                break;
            case SDLK_ESCAPE:
                //Mix_HaltMusic();
                shouldQuit = true;
                break;
            default:
                break;
        }
    }
    else if (evt.type == SDL_KEYUP)
    {
        switch (evt.key.keysym.sym)
        {
            case SDLK_a:
                player1->StopLeft();
                break;
            case SDLK_d:
                player1->StopRight();
                break;
            case SDLK_LEFT:
                player2->StopLeft();
                break;
            case SDLK_RIGHT:
                player2->StopRight();
                break;
            default:
                break;
        }
    }
}

SDL_Surface *GameState::render(double dh)
{
    SDL_Surface *temp;
    stringstream outs;
    outs << dh;
    sOutput = outs.str();
    if(sOutput == "0" && dh != 0)
        sOutput = "200";
    temp = TTF_RenderText_Solid(font, sOutput.c_str(), textColor);
    return temp;
}

CrabBattle::State *GameState::Update(void)
{
    vector<Sprite *>::const_iterator i;
    // Update physics if we're after countdown
    if (countdownTimer >= kCountdownDuration * 3)
    {
        // Clear sprite colliders
        player1->ClearColliders();
        player2->ClearColliders();
        for (i = envsprites.begin(); i < envsprites.end(); i++)
            (*i)->ClearColliders();
        // Update physics
        physicsSpace->collide(this, &_game_state_collide);
        player1->FixPhysics();
        player2->FixPhysics();
        physicsWorld->step((dReal)kUpdateRate / 1000.0);
        allContacts->empty();
        player1->FixPhysics();
        player2->FixPhysics();
        // Update sprites
        player1->Update();
        player2->Update();
        for (i = envsprites.begin(); i < envsprites.end(); i++)
            (*i)->Update();
    }
    if (countdownTimer < kCountdownDuration * 4)
    {
        countdownTimer++;
    }
    if (player1->GetLives() == 0 || player2->GetLives() == 0)
        shouldQuit = true;
    // Switch states if we're done
    if (shouldPause)
    {
        shouldPause = false;
        return (new PausedState());
    }
    else if (shouldQuit)
    {
        shouldQuit = false;
        return NULL;
    }
    else
        return this;
}

void GameState::AddContact(dContactGeom contactInfo, dGeomID geom1, dGeomID geom2)
{
    using std::cout;
    using std::endl;
    dContactJoint *joint;
    dContact *contact;
    Sprite *sprite1, *sprite2;
    dReal p1Height, p2Height;
    if (allContacts == NULL)
        return;
    if (dGeomGetBody(geom1) == NULL && dGeomGetBody(geom2) == NULL)
        return;
    contact = new dContact;
    // Determine sprites
    if (dGeomGetData(geom1) != NULL)
        sprite1 = (Sprite *)dGeomGetData(geom1);
    else
        sprite1 = NULL;
    if (dGeomGetData(geom2) != NULL)
        sprite2 = (Sprite *)dGeomGetData(geom2);
    else
        sprite2 = NULL;
    // Add colliders
    if (sprite1 != NULL)
        sprite1->AddCollider(sprite2);
    if (sprite2 != NULL)
        sprite2->AddCollider(sprite1);
    // Set up contact
    contact->geom = contactInfo;
    if ((player1->GetGeometry()->id() == geom1 ||
         player1->GetGeometry()->id() == geom2) &&
        (player2->GetGeometry()->id() == geom1 ||
         player2->GetGeometry()->id() == geom2))
    {
        // Player-Player collision
        contact->surface.mode = 0;
        contact->surface.mu = 25.0;
        contact->surface.mu2 = 0.0;
        contact->surface.bounce = 1.0;
        contact->surface.bounce_vel = 0.1;
        contact->surface.soft_erp = kPhysicsERP;
        contact->surface.soft_cfm = kPhysicsCFM;
        // Do health check
        p1Height = player1->GetGeometry()->getPosition()[1];
        p2Height = player2->GetGeometry()->getPosition()[1];
        if (p1Height > p2Height + kDamageHeightTolerance)
            player1->ModHp(-1);
        else if (p1Height + kDamageHeightTolerance < p2Height)
            player2->ModHp(-1);
    }
    else if (player1->GetGeometry()->id() == geom1 ||
             player1->GetGeometry()->id() == geom2 ||
             player2->GetGeometry()->id() == geom1 ||
             player2->GetGeometry()->id() == geom2)
    {
        // Player-Environment Collision
        contact->surface.mode = dContactBounce | dContactSoftERP;
        contact->surface.mu = 20.0;
        contact->surface.mu2 = 0.0;
        contact->surface.bounce = 0.1;
        contact->surface.bounce_vel = 0.1;
        contact->surface.soft_erp = kPhysicsERP;
        contact->surface.soft_cfm = kPhysicsCFM;
    }
    else
    {
        // Environment-Environment Collision
        contact->surface.mode = dContactBounce | dContactSoftERP;
        contact->surface.mu = 20.0;
        contact->surface.mu2 = 0.0;
        contact->surface.bounce = 0.1;
        contact->surface.bounce_vel = 0.1;
        contact->surface.soft_erp = kPhysicsERP;
        contact->surface.soft_cfm = kPhysicsCFM;
    }
    // Create joint
    joint = new dContactJoint(physicsWorld->id(), allContacts->id(), contact);
    delete contact;
    joint->attach(dGeomGetBody(geom1), dGeomGetBody(geom2));
}

void GameState::Display(Surface *screen)
{
    vector<Sprite *>::const_iterator i;
    // Display background
    screen->Fill(screen->GetRect(), 0, 0, 0); // Clears screen
    screen->Blit(background, background->GetRect()); // Blits the background
    // Display environment
    for (i = envsprites.begin(); i < envsprites.end(); i++)
    {
        (*i)->Display(screen);
    }
    // Display players
    player1->Display(screen);
    player2->Display(screen);
    // Display HUD
    if (lastHP1 != player1->GetHp())
    {
        lives1 = render(player1->GetLives());
        messPc1 = render(player1->GetHp());
        lastHP1 = player1->GetHp();
    }
    if (lastHP2 != player2->GetHp())
    {
        lives2 = render(player2->GetLives());
        messPc2 = render(player2->GetHp());
        lastHP2 = player2->GetHp();
    }
    screen->Blit(lives1, winsRect1);
    screen->Blit(lives2, winsRect2);
    screen->Blit(healthbar1, hpRect1, player1->GetHp());
    screen->Blit(healthbar1, hpRect2, player2->GetHp());
    screen->Blit(messPc1, hpRect1);
    screen->Blit(messPc2, hpRect2);
    // Display countdown
    if (countdownSurface == NULL)
    {
        countdownSurface = new Surface("images/count3.png");
    }
    else if (countdownTimer == kCountdownDuration)
    {
        countdownSurface->DelRef();
        countdownSurface = new Surface("images/count2.png");
    }
    else if (countdownTimer == kCountdownDuration * 2)
    {
        countdownSurface->DelRef();
        countdownSurface = new Surface("images/count1.png");
    }
    else if (countdownTimer == kCountdownDuration * 3)
    {
        countdownSurface->DelRef();
        countdownSurface = new Surface("images/countgo.png");
    }
    if (countdownTimer < kCountdownDuration * 4)
    {
        screen->Blit(countdownSurface, Rect(kCountdownPosX, kCountdownPosY,
                                            countdownSurface->GetWidth(),
                                            countdownSurface->GetHeight()));
    }
    // Updates the screen
    screen->Flip();
}

GameState::~GameState(void)
{
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    vector<Sprite *>::const_iterator i;
    for (i = envsprites.begin(); i < envsprites.end(); i++)
        (*i)->DelRef();
    background->DelRef();
    player1->DelRef();
    player2->DelRef();
    healthbar1->DelRef();
    SDL_FreeSurface(messPc1);
    SDL_FreeSurface(messPc2);
    SDL_FreeSurface(lives1);
    SDL_FreeSurface(lives2);
    TTF_CloseFont(font);
    delete physicsWorld;
    delete physicsSpace;
}
