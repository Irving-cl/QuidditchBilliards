
#ifndef _FLAG_H_
#define _FLAG_H_

#include "OpenGLObject.h"
#include "Cylinder.h"

/*
    Quidditch Flag, including a
  pillar and a waving flag
 */

class Flag : public OpenGLObject
{
public:
	Flag();                         // Constructor
	~Flag();                        // Destructor
	virtual void    Draw();         // Implement Draw function
	virtual void    Update();       // Implement Update function

private:
	///Members
	Cylinder * m_Cylinder;          // A cylinder as the flag pole
	float m_Points[45][45][3];      // Points constitutes the flag
	float hold;
	unsigned int wiggle_count;
};

#endif // _FLAG_H_