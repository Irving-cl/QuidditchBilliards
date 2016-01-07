
#ifndef _BALLS_H_
#define _BALLS_H_

#include "Ball.h"

/*
    Main ball class. In quidditch,
  we use cue to hit main ball to hit
  other balls.
 */

class MainBall : public Ball
{
public:
	/// Public interfaces
	virtual void Draw();          // Implement Draw function
	virtual void Update();        // Implement Update function

};

/*
    Ghost ball class. Normal balls with
  nothing special and the lowest score.
 */

class GhostBall : public Ball
{
public:
	/// Public interfaces
	virtual void Draw();          // Implement Draw function
	virtual void Update();        // Implement Update function

};

/*
    Wander Ball class. Wander balls are
  given speed at some time which makes 
  them difficult to hit. Thus they have 
  higher score.
 */

class WanderBall : public Ball
{
public:
	/// Public interfaces
	virtual void Draw();          // Implement Draw function
	virtual void Update();        // Implement Update function

};

/*
    Golden Ball class. Golden ball will fly 
  above the table and occasionally land on
  the table which makes it extremelly difficult
  to hit. Thus you get considerable score when
  you hit it.
 */

enum GoldenBallState { FLY, STOP, UP, DOWN };        // Different states of golden ball

class GoldenBall : public Ball
{
public:
	/// Public interfaces
	GoldenBall();                 // Golden ball has its own constructor
	virtual void Draw();          // Implement Draw function
	virtual void Update();        // Implement Update function

private:
	GoldenBallState m_State;
	clock_t m_LastTime;

};

#endif // _BALLS_H_