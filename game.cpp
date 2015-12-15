/****************************************************
 * File: game.cpp
 * Author: Br. Burton
 *         Tyler Hall
 * Description: Holds the methods for the game class.
 * It also has the main function which runs the game.
 *
 * These functions are not complete. You need to fill them
 * in.
 *
 * DO NOT SHARE with students from other classes
 ******************************************************/

#include "game.h"

#include "uiDraw.h"
#include "uiInteract.h"
#include <math.h>
#include <iostream> // just in case we need to debug
using namespace std;

// set the bounds of the game

#define SCREEN_SIZE 128.0

float Point :: xMin = -SCREEN_SIZE;
float Point :: xMax =  SCREEN_SIZE;
float Point :: yMin = -SCREEN_SIZE;
float Point :: yMax =  SCREEN_SIZE;

#define INITIAL_ROCK_COUNT 3




/******************************************************
 * Game - Default Constructor
 *
 * Purpose: Initializes an empty game
 *******************************************************/
Game :: Game()
{
    for (int i = 0; i < INITIAL_ROCK_COUNT; i++)
    {
        rocks.push_back(new BigRock);
    }
//    levelTimer = 0;
//    level = 1;
//    secs = 0;
}

/******************************************************
 * Game :: addRock
 *
 * Purpose: Adds a rock to the list
 ******************************************************/
void Game :: addRock(Rock * rock)
{
    rocks.push_back(rock);
}

/******************************************************
 * Game :: addBullet
 *
 * Purpose: Adds a bullet to the list
 ******************************************************/
void Game :: addBullet(Bullet * bullet)
{
    bullets.push_back(bullet);
}

/******************************************************
 * Game :: draw
 *
 * Purpose: Tells each entity in the game to draw itself
 *******************************************************/
void Game :: draw()
{
    if (enterprise.isAlive()) {
    
    enterprise.draw();
    }
    for (list<Bullet*> :: iterator it = bullets.begin();it != bullets.end(); it++)
    {
        (*it)->draw();
    }
   
    for (list<Rock*> :: iterator it = rocks.begin();it != rocks.end(); it++)
    {
        (*it)->draw();
    }
    
//    char text[20] = "Level :";
//    Point topL;
//    topL.setY(100);
//    topL.setX(-30);
//    drawText(topL, text);
//    
//    Point topMid;
//    topMid.setY(109);
//    topMid.setX(10);
//    drawNumber(topMid, level);
//
//    if (rocks.size() == 0 || levelTimer % 900 == 0)
//    {
//        level++;
//        for(int i = 0; i < level + 2; i++)
//        {
//            addRock(new BigRock(*this));
//        }
//        levelTimer = 0;
//    }
//    
//    levelTimer++;
//    
//    if (levelTimer%30 == 0)
//    {
//        secs++;
//    }
//    
//    Point botL;
//    botL.setX(-120);
//    botL.setY(-110);
//    drawNumber(botL, secs);
    
}

/******************************************************
 * Game :: removeDeadObjects
 *
 * Purpose: Looks for any dead bullets or rocks deletes
 * the object (frees the memory) and takes them out of
 * the list.
 *******************************************************/
void Game :: removeDeadObjects()
{
    
    
    for (list<Bullet*> :: iterator it = bullets.begin();it != bullets.end();)
    {
        
        if(!(*it)->isAlive())
        {
            
            delete *it;
            it = bullets.erase(it);
            
        }
        else
        {
            it++;
        }
    }
    
    for (list<Rock*> :: iterator it = rocks.begin();it != rocks.end();)
    {
        if(!(*it)->isAlive())
        {
            
            delete *it;
            it = rocks.erase(it);
            
        }
        else
        {
            it++;
        }
    }
}

/******************************************************
 * Game :: handleCollisions
 *
 * Purpose: Looks for any collisions among objects and
 * handle them properly.
 *******************************************************/
void Game :: handleCollisions()
{
    for (list<Rock*> :: iterator it = rocks.begin();it != rocks.end(); it++)
    {
        if(enterprise.isAlive())
        {
            enterprise.hit(*it, *this);
        }
        
        for (list<Bullet*> :: iterator bullit = bullets.begin();bullit != bullets.end(); bullit++)
        {
            (*it)->hit(*bullit, *this);
        }
}

   removeDeadObjects();
}

/******************************************************
 * Game :: handleUserActions
 *
 * Purpose: Handles the different keyboard inputs from the
 * user.
 *******************************************************/
void Game :: handleUserActions(const Interface * pUserInterface)
{
   // pass the userInterface object and a reference to the
   // current game object of the ship class
   //
   // Something like:
    if(enterprise.isAlive())
    {
        enterprise.handleUserActions(*pUserInterface, *this);
    }
}

/******************************************************
 * Game :: advance
 *
 * Purpose: Moves the game forward in time. In other words
 * tells the ship, the bullets and the rocks to all
 * advance by one.
 *******************************************************/
void Game :: advance()
{
   // advance the ship
   
    for (list<Bullet*> :: iterator it = bullets.begin();it != bullets.end(); it++)
    {
        (*it)->advance();
    }
   
    for (list<Rock*> :: iterator it = rocks.begin();it != rocks.end(); it++)
    {
        (*it)->advance();
    }
}

/******************************************************
 * Function: callback
 *
 * Purpose: This function gets called by the user interface
 * when it's time to do something. It will pass a pointer
 * to our game object, and then we can call the appropriate
 * methods on that.
 *******************************************************/
void callback(const Interface * pUserInterface, void * p)
{
   // this void pointer actually points to our game class
   // so we can cast it to a "Game"
   Game * pGame = (Game *)p;
   
   // check for collisions
   pGame->handleCollisions();
   
   // handle the keyboard input
   pGame->handleUserActions(pUserInterface);
   
   // move everything forward one step
   pGame->advance();
   
   // draw everything
   pGame->draw();
}

/******************************************************
 * Function: main
 *
 * Purpose: Starts the game!
 *******************************************************/
int main(int argc, char * argv[])
{
   // Start up the graphical interface
   Interface userInterface(argc, argv, "Asteroids");
   
   // Initialize the game
   Game game;
   
   // Tell the interface to call our callback method when it needs to
   userInterface.run(callback, (void*)&game);
   
   return 0;
}






