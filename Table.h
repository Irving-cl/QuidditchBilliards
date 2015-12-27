
#ifndef _TABLE_H_
#define _TABLE_H_

#include "OpenGLObject.h"
#include "CBMPLoader.h"

/*
    Quidditch Table
 */

class Table : public OpenGLObject
{
public:
	Table();                        // Constructor
	~Table();                       // Destructor
	virtual void    Draw();         // Implement Draw function
	virtual void    Update();       // Implement Update function

private:
	/// Method
	void   DrawCube(unsigned int tex1_ID,
		unsigned int tex2_ID, Vector3 LHW,
		Vector3 position);          // Draw a cube with assigned textures
};

#endif // _TABLE_H