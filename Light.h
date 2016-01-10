
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "stdafx.h"
#include "Input.h"
#include "QuidditchConstants.h"

/*
    Light class. This class control
  light in the scene.
*/

class Light
{
public:
	Light();            // Constructor
	~Light();           // Destructor

	/// Public interfaces
	void Init();                                // Initialization
	void SetInput(CInputSystem * input);        // Set input system for light
	void Update();                              // Update the light

private:
	CInputSystem * m_Input;                     // Pointer to input system

};

#endif // _LIGHT_H_