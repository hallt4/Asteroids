/***********************************************************
 * File: velocity.cpp
 * Author: Br. Burton
 *
 * Velocity class methods
 *
 * DO NOT SHARE with students from other classes!
 ***********************************************************/

#include "velocity.h"
#include <cmath>
#include <algorithm>
using namespace std;

/***********************************************************
 * Velocity :: setMagnitudeAndDirection
 * Purpose: Allows setting both the magnitude and direction
 * at the same time.
 ***********************************************************/
void Velocity :: setMagnitudeAndDirection(float magnitude, float angle)
{
   float angleRadians = deg2rad(angle);
   
   dx = cos(angleRadians) * magnitude;
   dy = -sin(angleRadians) * magnitude;
}

/***********************************************************
 * Velocity :: setMagnitude
 * Purpose: Allows setting just the magnitude.
 ***********************************************************/
void Velocity :: setMagnitude(float magnitude)
{
   float angleRadians = deg2rad(getDirection());
   
   dx = cos(angleRadians) * magnitude;
   dy = -sin(angleRadians) * magnitude;
}

/***********************************************************
 * Velocity :: setDirection
 * Purpose: Sets direction (angle in degrees) keeping the
 * magnitude constant.
 ***********************************************************/
void Velocity :: setDirection(float angle)
{
   float angleRadians = deg2rad(angle);
   float magnitude = getMagnitude();
   
   dx = cos(angleRadians) * magnitude;
   dy = -sin(angleRadians) * magnitude;
}

/***********************************************************
 * Velocity :: getDirection
 * Purpose: Gets the current angle in degrees
 ***********************************************************/
float Velocity :: getDirection() const
{
   float angle = rad2deg(atan2(-dy, dx));
   
   return angle;
}

/***********************************************************
 * Velocity :: getMagnitude
 * Purpose: Gets the magnitude
 ***********************************************************/
float Velocity :: getMagnitude() const
{
   float magnitude = sqrt(dx * dx + dy * dy);
   
   return magnitude;
}

/***********************************************************
 * Velocity :: advance
 * Purpose: Moves the point according to the current velocity
 * This function also takes into account wrap-around
 ***********************************************************/
void Velocity :: advance()
{
   // set the new coordinates
   setX(getX() + getDx());
   setY(getY() + getDy());
   
   // handle the wrap around cases
   if (getX() < getXMin())
   {
      setX(getXMax());
   }
   
   if (getX() > getXMax())
   {
      setX(getXMin());
   }
   
   if (getY() < getYMin())
   {
      setY(getYMax());
   }
   
   if (getY() > getYMax())
   {
      setY(getYMin());
   }
}

/***********************************************************
 * Velocity :: operator++
 * Purpose: Advances the velocity (taking into account
 * wrap around)
 ***********************************************************/
Velocity Velocity :: operator ++ (int postfix)
{
   Velocity old = *this;
   
   advance();
   
   return old;
}

/***********************************************************
 * Velocity :: operator+
 * Purpose: Adds two vectors together and returns a vector
 ***********************************************************/
Velocity Velocity :: operator + (const Velocity & rhs) const
{
   Velocity sum;
 
   sum.setX(getX() + rhs.getX());
   sum.setY(getY() + rhs.getY());
   
   sum.dx = dx + rhs.dx;
   sum.dy = dy + rhs.dy;
   
   return sum;
}

/***********************************************************
 * Velocity :: operator - (difference)
 * Purpose: Determines how close the two velocities are together
 * and returns this as float. You can use this to determine
 * if objects collide by subtracting their two velocities and
 * then seeing if the result is less than their combined sizes.
 ***********************************************************/
float Velocity :: operator - (const Velocity & rhs) const
{
   // from Br. Helfrich:
   // find the maximum distance traveled
   float dMax = max(abs(dx), abs(dy));
   dMax = max(dMax, abs(rhs.getDx()));
   dMax = max(dMax, abs(rhs.getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   // we will advance by this number
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point pointLhs(getX() + (dx * i / dMax),
                     getY() + (dy * i / dMax));
      Point pointRhs(rhs.getX() + (rhs.getDx() * i / dMax),
                     rhs.getY() + (rhs.getDy() * i / dMax));
      
      float distSquared =
      ((pointLhs.getX() - pointRhs.getX()) *
       (pointLhs.getX() - pointRhs.getX())) +
      ((pointLhs.getY() - pointRhs.getY()) *
       (pointLhs.getY() - pointRhs.getY()));
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

