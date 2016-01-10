
#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include "stdafx.h"
#include "QuidditchConstants.h"

/*
    Cylinder class, help to draw
  a cylinder, usually as part of a
  opengl object
 */

class Cylinder
{
public:
	Cylinder();        // Constructor
	~Cylinder();       // Destructor

	void   DrawCircleArea(float cx, float cy,        // Draw top and bottom of a cylinder
		float cz, float r, int num_segments);
	GLUquadricObj* GetQuadratic();                   // Get the quadratic

private:
	GLUquadricObj * m_Quadratic;                     // Required to draw main body of a cylinder
};

#endif // _CYLINDER_H_