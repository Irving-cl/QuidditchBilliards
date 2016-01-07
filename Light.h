
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "stdafx.h"
#include "QuidditchConstants.h"

/*
Light class. This class control
light in the scene.
*/

class Light
{
public:
	Light();        // Constructor
	~Light();       // Destructor

	void Init();    // Initialization
};

#endif // _LIGHT_H_