//
//  flyingObjects.cpp
//  prj4ASTEROIDS
//
//  Created by Tyler Hall on 12/12/14.
//  Copyright (c) 2014 Tyler Hall. All rights reserved.
//

#include "flyingObjects.h"
#include "uiDraw.h"
#include "game.h"


Velocity calcThrust(Velocity thrust, float speed, float orientation)
{
    float angleY = orientation;
    float angleB = 90;
    float angleX = 180 - (orientation + 90);
    
    angleY *= 0.0174532925;
    angleB *= 0.0174532925;
    angleX *= 0.0174532925;
    
    float sideY;
    float sideX;
    float sideB = speed;
    
    sideY = (sideB/sin(angleB)*sin(angleY));
    sideX = (sideB/sin(angleB)*sin(angleX));
    
    thrust.setY(thrust.getY() - sideY);
    thrust.setX(thrust.getX() - sideX);
    
    return thrust;
}

void FlyingObjects:: advance()
{
    
}

Ship:: Ship()
{
    size = 2;
    alive = true;
    orientation = 0;
    shipSpeed = 0.2;
}


void Ship :: draw()
{
    drawShip(vel.getPoint(), orientation);
    
}

void Ship :: hit(FlyingObjects * object, Game & game)
{
    float diff = vel - object->getVelocity();
    
    if(diff < getSize() + object->getSize())
    {
        kill();
    }
}

void Ship:: handleUserActions(const Interface UserInterface, Game &game)
{
    if (vel.getX() < -128)
    {
        vel.setX(128);
    }
    
    if (vel.getX() > 128)
    {
        vel.setX(-128);
    }
    
    if (vel.getY() < -128)
    {
        vel.setY(128);
    }
    
    if (vel.getY() > 128)
    {
        vel.setY(-128);
    }
    
    if (UserInterface.isDown())
    {
        vel.setY(random(-128, 128));
        vel.setX(random(-128, 128));
    }
    
    if (UserInterface.isRight())
    {
        orientation -= 10;
    }
    
    if (UserInterface.isLeft())
    {
        orientation += 10;
    }
    
    if (UserInterface.isUp())
    {
        thrust = calcThrust(thrust, shipSpeed, orientation);
        
    }
    
    if (UserInterface.isSpace())
    {
        game.addBullet(new Bullet(vel, thrust, orientation));
    }
    vel = vel + thrust;
    
}

Bullet:: Bullet()
{
    alive = true;
}

Bullet:: Bullet(Velocity velocity, Velocity thrust, float orientation)
{
    framesToLive = 30;
    alive = true;
    vel = velocity;
    shipVel = thrust;
    bullRate = 5;
    bullSpeed = calcThrust(bullSpeed, bullRate , orientation);
}

void Bullet:: draw()
{
drawDot(vel.getPoint());
}

void Bullet:: advance()
{

    if (vel.getX() < -128)
    {
        vel.setX(128);
    }
    
    if (vel.getX() > 128)
    {
        vel.setX(-128);
    }
    
    if (vel.getY() < -128)
    {
        vel.setY(128);
    }
    
    if (vel.getY() > 128)
    {
        vel.setY(-128);
    }
    
    if (framesToLive >= 0)
    {
        vel = vel + shipVel + bullSpeed;
    }
    else
    {
        alive = false;
    }
    framesToLive--;
    
    
}

void Bullet:: hit(FlyingObjects * object, Game & game)
{
    float diff = vel - object->getVelocity();
    
    if(diff < getSize() + object->getSize())
    {
        kill();
        object->kill();
    }
}

Rock:: Rock()
{
    alive = true;
}

void Rock:: hit(FlyingObjects * object, Game & game)
{
    
}

SmallRock:: SmallRock()
{
    size = 5;
    alive = true;
    orientation = 0;
}

SmallRock:: SmallRock(Velocity velo, Velocity thrusto)
{
    size = 5;
    alive = true;
    orientation = 0;
    
    thrust.setX(thrusto.getX());
    thrust.setY(thrusto.getY());
    
    vel = velo;
}


void SmallRock:: draw()
{
    
    
    if (vel.getX() < -128)
    {
        vel.setX(128);
    }
    
    if (vel.getX() > 128)
    {
        vel.setX(-128);
    }
    
    if (vel.getY() < -128)
    {
        vel.setY(128);
    }
    
    if (vel.getY() > 128)
    {
        vel.setY(-128);
    }
    
    drawPolygon(vel.getPoint(), 5, 3, orientation);
    vel = vel + thrust;
    orientation += 10;
}

void SmallRock:: hit(FlyingObjects * object, Game & game)
{
    {
        float diff = vel - object->getVelocity();
        
        if(diff < getSize() + object->getSize())
        {
            kill();
            object->kill();
        }
    }
    
}

MedRock:: MedRock()
{
    size = 10;
    alive = true;
    thrust.setY(2);
    thrust.setX(2);
    orientation = 0;
    
}

MedRock:: MedRock(Velocity velo, Velocity thrusto)
{
    size = 10;
    alive = true;
    orientation = 0;
    
    if(thrusto.getX() > 0)
    {
        thrust.setX(2);
     
    }
    else
    {
        thrust.setX(-2);
    
    }
    
    if(thrusto.getY() > 0)
    {
        thrust.setY(2);
    }
  
    else{
    thrust.setY(-2);
    }
    vel = velo;
}
void MedRock:: draw()
{
    
    if (vel.getX() < -128)
    {
        vel.setX(128);
    }
    
    if (vel.getX() > 128)
    {
        vel.setX(-128);
    }
    
    if (vel.getY() < -128)
    {
        vel.setY(128);
    }
    
    if (vel.getY() > 128)
    {
        vel.setY(-128);
    }
    
    drawRect(vel.getPoint(), 20, 20, orientation);
    
    vel = vel + thrust;
    orientation += 5;
    
}

void MedRock:: hit(FlyingObjects * object, Game & game)
{
    {
        float diff = vel - object->getVelocity();
        
        if(diff < getSize() + object->getSize())
        {
            kill();
            object->kill();
            
            Velocity thrust2;
            Velocity thrust3;
            
            thrust2.setY(thrust.getY());
            thrust2.setX(5);
            thrust3.setY(thrust.getY());
            thrust3.setX(-5);
            
            game.addRock(new SmallRock(vel, thrust2));
            game.addRock(new SmallRock(vel, thrust3));
        }
    }
}

//BigRock:: BigRock()
//{
//    
//}
BigRock:: BigRock()
{
    size = 20;
//    int choice;
//    choice = random(1, 4);
//    if (choice == 1){
//        thrust.setX(-1);
//        thrust.setY(-1);
//    }
//    else if(choice == 2){
//        thrust.setX(1);
//        thrust.setY(1);
//    }
//    else if(choice == 3){
//        thrust.setX(1);
//        thrust.setY(-1);
//    }
//    else{
//         thrust.setX(-1);
//         thrust.setY(1);
//    }
//
    do{
    thrust.setX(random(-1, 1));
    thrust.setY(random(-1,1));
    }
    while (thrust.getX() == 0 && thrust.getY() == 0);

    orientation = 0;
    
    int x = random(-123, 123);
    int y = random(-123, 123);
    
    alive = true;
    
    if(x%2)
    {
        vel.setX(random(-128,40));
    }
    else{
        vel.setX(random(40, 128));
    }
    
    if(y%2)
    {
        vel.setY(random(40,128));
    }
    else{
        vel.setY(random(-128, 40));
    }
}

void BigRock:: draw()
{
    drawPolygon(vel.getPoint(), 20, 6, orientation);
    
   
    if (vel.getX() < -128)
    {
        vel.setX(128);
    }
    
    if (vel.getX() > 128)
    {
        vel.setX(-128);
    }
    
    if (vel.getY() < -128)
    {
        vel.setY(128);
    }
    
    if (vel.getY() > 128)
    {
        vel.setY(-128);
    }
    
    vel = vel + thrust;
    orientation += 2;
}


void BigRock:: hit(FlyingObjects *object, Game &game)
{
        float diff = vel - object->getVelocity();
    
        if(diff < getSize() + object->getSize())
        {
            kill();
            object->kill();
            
            Velocity thrust2;
            Velocity thrust3;

            thrust.setY(2);
            
            thrust2.setY(-2);
            thrust2.setX(thrust.getX());
            
            thrust3.setX(3);
            thrust3.setY(-thrust.getY());
            
            game.addRock(new MedRock(vel, thrust));
            game.addRock(new MedRock(vel, thrust2));
            game.addRock(new SmallRock(vel, thrust3));
            
        }
    
}