
#ifndef _BALL_H_
#define _BALL_H_

#include "OpenGLObject.h"

/*
    Ball class is a virtual class
  must be implemented by actual ball
  class.
 */

class Ball : public OpenGLObject
{
public:
	Ball();    // Constructor
	~Ball();   // Destructor

	/// Public interfaces
	virtual void CheckHit(Ball * otherBall);    // Check bounce with other balls
	Vector3 GetSpeed();                         // Get speed of the ball
	void    SetSpeed(Vector3 speed);            // Set speed of the ball
	void    SetIniPosition(Vector3 ini);        // Set initial position of the ball
	bool    IsStatic();                         // Is the ball static

protected:
	/// Members
	GLUquadricObj * m_Sphere;    // GLUquadricObj required to draw the sphere
	Vector3 m_IniPosition;       // Initial position of the ball
	Vector3 m_Speed;             // Speed of the ball

	/// Method
	void   Move();               // Ball move its position
	void   CheckBoundry();       // Check whether the ball is going to go out of the table and change the speed of it
	void   Roll();               // Roll, change the rotate angle
	void   SlowDown();           // Ball on the table will gradually slow down
	bool   IsGettingCloser(Ball * otherBall);    // Judge whether two balls are getting closer
};

#endif // _BALL_H_