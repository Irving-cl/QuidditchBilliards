
#ifndef _CAMERA_ROTATE_H_
#define _CAMERA_ROTATE_H_

#include "stdafx.h"

/*
    Camera class, used to change
  visual angle. Rotate around the
  center
 */

class CameraRotate
{
public:
	CameraRotate();             // Constructor
	~CameraRotate();            // Destructor

	void   SetLook();           // Set the visual angle
	void   LRotate();           // Left Rotate
	void   RRotate();           // Right Rotate
	void   URotate();           // Up Rotate
	void   DRotate();           // Down Rotate
	void   UpdatePosition();    // Update the position

private:

	float   x;
	float   y;
	float   z;

	float   Alpha;
	float   Beta;

	float   distance;

};

#endif // _CAMERA_ROTATE_H_