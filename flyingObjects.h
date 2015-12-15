//
//  flyingObjects.h
//  prj4ASTEROIDS
//
//  Created by Tyler Hall on 12/12/14.
//  Copyright (c) 2014 Tyler Hall. All rights reserved.
//

#ifndef __prj4ASTEROIDS__flyingObjects__
#define __prj4ASTEROIDS__flyingObjects__

#include <stdio.h>
#include "velocity.h"
#include "uiInteract.h"
class Game;

class FlyingObjects
{
protected:
    bool alive;
    Velocity vel;
    float size;

public:
    virtual void draw() = 0;
    virtual void advance();
    virtual void kill(){alive = false;}
    virtual bool isAlive(){return alive;}
    virtual Velocity getVelocity(){return vel;}
    virtual void hit(FlyingObjects * object, Game & game) = 0;
    virtual float getSize(){return size;}
    
};

class Ship : public FlyingObjects
{
private:
    float orientation;
    Velocity thrust;
    float shipSpeed;
public:
    Ship();
    
    virtual void draw();
    virtual void hit(FlyingObjects * object, Game & game);
    void handleUserActions(const Interface UserInterface, Game & game);
    

    
};

class Bullet : public FlyingObjects
{
private:
    int framesToLive;
    Velocity bullSpeed;
    float bullRate;
    Velocity shipVel;
public:
    Bullet();
    Bullet(Velocity velocity, Velocity thrust, float orientation);
    virtual void draw();
    virtual void advance();
    virtual void hit(FlyingObjects * object, Game & game);

    
};

class Rock : public FlyingObjects
{
protected:
    float orientation;
    Velocity thrust;
public:
    Rock();
    
    virtual void hit(FlyingObjects * object, Game & game);
};

class SmallRock : public Rock
{
public:
    SmallRock();
    SmallRock(Velocity velo, Velocity thrusto);
    
    virtual void draw();
    virtual void hit(FlyingObjects * object, Game & game);
    
};

class MedRock : public Rock
{
public:
    MedRock();
    MedRock(Velocity velo, Velocity thrusto);
    
    virtual void draw();
    virtual void hit(FlyingObjects * object, Game & game);
};



class BigRock : public Rock
{
public:
    BigRock();
//    BigRock(Game & game);
    
    virtual void draw();
    virtual void hit(FlyingObjects * object, Game & game);
};

Velocity calcThrust(Velocity thrust, float speed, float orientation);


#endif /* defined(__prj4ASTEROIDS__flyingObjects__) */
