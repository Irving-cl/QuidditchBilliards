
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
	CameraRotate();                 // Constructor
	~CameraRotate();                // Destructor

	/// Public interfaces
	void   SetLook();               // Set the visual angle
	void   LRotate();               // Left Rotate
	void   RRotate();               // Right Rotate
	void   URotate();               // Up Rotate
	void   DRotate();               // Down Rotate
	void   UpdatePosition();        // Update the position

private:
	/// Members
	float   x;               // x position
	float   y;               // y position
	float   z;               // z position
	float   Alpha;           // angle alpha
	float   Beta;            // angle beta
	float   distance;        // Distance from this to the center

};

#endif // _CAMERA_ROTATE_H_