/****************************************************
 * File: game.h
 * Author: Br. Burton
 *
 * Define the Game class for Asteroids
 *
 * DO NOT SHARE with students from other classes
 ****************************************************/

#ifndef GAME_H
#define GAME_H

#include "flyingObjects.h"
#include "uiInteract.h"
#include <list>
using namespace std;
class Game
{
private:
    list<Rock*> rocks;
    list<Bullet*> bullets;
    Ship enterprise;
    int levelTimer;
    int level;
    int secs;
   
   void removeDeadObjects();
   
public:
   Game();
   
   void draw();
   void advance();
   void handleUserActions(const Interface * pUserInterface);
   void handleCollisions();
    
   void addRock(Rock * rock);
   void addBullet(Bullet * bullet);
};

#endif