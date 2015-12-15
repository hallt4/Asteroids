/***********************************************************
 * File: velocity.h
 * Author: Br. Burton
 *
 * Velocity class declaration
 *
 * DO NOT SHARE with students from other classes!
 ***********************************************************/

#ifndef VELOCITY_H
#define VELOCITY_H

#include "point.h"

#define deg2rad(value) ((M_PI / 180) * (value))
#define rad2deg(value) ((value) * (180 / M_PI))

class Velocity
{
private:
   Point point;
   float dx;
   float dy;
   
public:
   /*****************
    * Constructor
    *****************/
   Velocity() : point()
   {
      setDx(0);
      setDy(0);
   }
   
   Velocity(int x, int y) : point(x, y)
   {
      setDx(0);
      setDy(0);
   }
   
   Velocity(int x, int y, float dx, float dy) : point(x, y)
   {
      setDx(dx);
      setDy(dy);
   }
   
   /*****************
    * Getters
    *****************/
   Point getPoint() const { return point; }
   
   float getX() const { return point.getX(); }
   float getY() const { return point.getY(); }
   
   float getDx() const { return dx; }
   float getDy() const { return dy; }
   
   float getXMin() const { return point.getXMin(); }
   float getXMax() const { return point.getXMax(); }
   float getYMin() const { return point.getYMin(); }
   float getYMax() const { return point.getYMax(); }
   
   /*****************
    * Setters
    *****************/
   void setPoint(const Point & point) { this->point = point; }
   
   void setX(float x) { point.setX(x); }
   void setY(float y) { point.setY(y); }
   
   void setDx(float dx) { this->dx = dx; }
   void setDy(float dy) { this->dy = dy; }
   
   /*****************
    * Add
    *****************/
   void addDx(float amount) { setDx(getDx() + amount); }
   void addDy(float amount) { setDy(getDy() + amount); }
   
   void setMagnitudeAndDirection(float magnitude, float direction);
   void setMagnitude(float magnitude);
   void setDirection(float angle);
   
   float getDirection() const;
   float getMagnitude() const;

   
   void advance();
   Velocity operator + (const Velocity & rhs) const;
   float operator - (const Velocity & rhs) const;
   Velocity operator ++ (int postfix);
};

#endif