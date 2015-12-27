
#ifndef _ROOM_H_
#define _ROOM_H_

#include "OpenGLObject.h"

/*
    Room contains a skybox to
  display a indoor room scene.
 */

class Room : public OpenGLObject
{
public:
	Room();                   // Constructor
	~Room();                  // Destructor
	virtual void Draw();      // Implement Draw function
	virtual void Update();    // Implement Update function

private:
	/// Member
	//unsigned int * m_TextureIDs;    // IDs of textures of the six surfaces of the room
};

#endif _ROOM_H_