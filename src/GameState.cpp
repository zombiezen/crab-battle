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
#include <fstream>
#include <iostream>

// TODO: Remove
#include <cstdio>
using std::printf;

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
    char value1[MAXPATHLEN];
    char value2[MAXPATHLEN];
    char value3[MAXPATHLEN];
    char value4[MAXPATHLEN];
    char value5[MAXPATHLEN];
    ifstream getTitles;
    CrabBattle::Surface *surf_p1, *surf_p2;
    CrabBattle::Sprite *sprite;
    dBody *newBody;
    dMass *newMass;
    dGeom *newGeom;
    dJointID joint2d;
#ifdef NO_SDL_IMAGE
    SDL_Surface *bg, *p1, *p2;
#endif
    //cout << "tff_init()= "<<TTF_WasInit()<<endl;
    
    font = TTF_OpenFont( "times.ttf", 24 );
    if (font == NULL)
        throw FileNotFoundError("times.ttf");
    
    messPc1 = TTF_RenderText_Solid( font,"200", textColor );
    messPc2 = TTF_RenderText_Solid( font, "200", textColor );
    wins1 = TTF_RenderText_Solid( font, "0", textColor );
    wins2 = TTF_RenderText_Solid( font, "0", textColor );
    
    getTitles.open("titles.txt");

    if (!getTitles.is_open())  // if failed to open file
    {
        throw FileNotFoundError("titles.txt");
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
                       64.0 / kPhysicsScreenScale,
                       64.0 / kPhysicsScreenScale,
                       1.0);
    newGeom->setBody(newBody->id());
    player1->SetGeometry(newGeom);
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
                       64.0 / kPhysicsScreenScale,
                       64.0 / kPhysicsScreenScale,
                       1.0);
    newGeom->setBody(newBody->id());
    player2->SetGeometry(newGeom);
    // Floor
    newGeom = new dPlane(physicsSpace->id(),
                         0.0, -1.0, 0.0,
                         -(kScreenHeight / kPhysicsScreenScale));
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
    // TODO: Fix surface memory leak
    sprite = new Sprite(new Surface("images/platform.bmp"),
                        CrabBattle::Rect(160, 100, 300, 100));
    newGeom = new dBox(physicsSpace->id(),
                       300.0 / kPhysicsScreenScale,
                       100.0 / kPhysicsScreenScale,
                       1.0);
    sprite->SetGeometry(newGeom);
    envsprites.push_back(sprite);
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
                player1->GetBody()->addForce(0.0, -1000.0, 0.0);
                break;
            case SDLK_a:
                player1->GetBody()->addForce(-1000.0, 0.0, 0.0);
                break;
            case SDLK_d:
                player1->GetBody()->addForce(1000.0, 0.0, 0.0);
                break;
            case SDLK_UP:
                player2->GetBody()->addForce(0.0, -1000.0, 0.0);
                break;
            case SDLK_LEFT:
                player2->GetBody()->addForce(-1000.0, 0.0, 0.0);
                break;
            case SDLK_RIGHT:
                player2->GetBody()->addForce(1000.0, 0.0, 0.0);
                break;
            case SDLK_ESCAPE:
                shouldQuit = true;
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
    // Update physics
    physicsSpace->collide(this, &_game_state_collide);
    player1->FixPhysics();
    player2->FixPhysics();
    physicsWorld->step((dReal)kUpdateRate / 1000.0);
    allContacts->empty();
    player1->FixPhysics();
    player2->FixPhysics();
    // Switch states
    if (shouldPause)
    {
        shouldPause = false;
        return (new PausedState(this));
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
    if (allContacts == NULL)
        return;
    contact = new dContact;
    // Set up contact
    contact->geom = contactInfo;
    if (dGeomGetBody(geom1) == NULL || dGeomGetBody(geom2) == NULL)
    {
        // Non-mobile collision
        contact->surface.mode = dContactBounce | dContactSoftERP;
        contact->surface.mu = 20.0;
        contact->surface.mu2 = 0.0;
        contact->surface.bounce = 0.25;
        contact->surface.bounce_vel = 0.1;
        contact->surface.soft_erp = kPhysicsERP;
        contact->surface.soft_cfm = kPhysicsCFM;
    }
    else
    {
        contact->surface.mode = dContactSoftERP | dContactSoftCFM;
        contact->surface.mu = 25.0;
        contact->surface.mu2 = 0.0;
        contact->surface.bounce = 1.0;
        contact->surface.bounce_vel = 0.1;
        contact->surface.soft_erp = kPhysicsERP;
        contact->surface.soft_cfm = kPhysicsCFM;
    }
    // Create joint
    joint = new dContactJoint(physicsWorld->id(), allContacts->id(), contact);
    delete contact;
    joint->attach(dGeomGetBody(geom1), dGeomGetBody(geom2));
//    printf("COLLIDED: %#x/%#x\n", geom1, geom2);
}

void GameState::Display(Surface *screen)
{
    vector<Sprite *>::const_iterator i;
    screen->Fill(screen->GetRect(), 0, 0, 0); // Clears screen
    screen->Blit(background, background->GetRect()); // Blits the background
    player1->Display(screen);
    player2->Display(screen);
    for (i = envsprites.begin(); i < envsprites.end(); i++)
    {
        (*i)->Display(screen);
    }
    screen->Blit(messPc1, hpRect1);
    screen->Blit(messPc2, hpRect2);
    screen->Blit(wins1, winsRect1);
    screen->Blit(wins2, winsRect2);
    screen->Blit(healthbar1, hpRect1, player1->GetHp());
    screen->Blit(healthbar1, hpRect2, player2->GetHp());
    screen->Flip(); // Flips second buffer
}

GameState::~GameState(void)
{
    vector<Sprite *>::const_iterator i;
    for (i = envsprites.begin(); i < envsprites.end(); i++)
        (*i)->DelRef();
    background->DelRef();
    player1->DelRef();
    player2->DelRef();
    healthbar1->DelRef();
    SDL_FreeSurface(messPc1);
    SDL_FreeSurface(messPc2);
    SDL_FreeSurface(wins1);
    SDL_FreeSurface(wins2);
    TTF_CloseFont(font);
    delete physicsWorld;
    delete physicsSpace;
}
