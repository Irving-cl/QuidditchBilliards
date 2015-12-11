
#ifndef _CUE_H_
#define _CUE_H_

#include "OpenGLObject.h"
#include "Cylinder.h"
#include "Ball.h"
#include "Input.h"

/// State of the cue
enum CueState { READY, MOVE, HIT };

/*
    Cue class. We use cue to
  hit the main ball in the game 
  and we can adjust the direction 
  of the cue as we wish.
 */

class Cue : public OpenGLObject
{
public:
	Cue(Ball * mainBall);           // Constructor
	~Cue();                         // Destructor
	virtual void    Draw();         // Implement Draw function
	virtual void    Update();       // Implement Update function

	void SetInput(CInputSystem * input);    // Set the pointer to input system

private:
	/// Members
	CInputSystem * m_Input;         // Pointer to input system
	Cylinder * m_Cylinder;          // A cylinder as the flag pole
	Ball * m_MainBall;              // The cue will always point to the main ball
	float m_DirectionAngle;         // Direction angle of the cue
	float m_StippleMove;            // Movement of the stipple
	float m_CueMove;                // Movement of the cue when we are hitting the ball
	CueState m_State;               // State of the cue

	// Method
	void HitBall();                 // Hit the ball, give the ball a speed
};

#endif // _CUE_H_