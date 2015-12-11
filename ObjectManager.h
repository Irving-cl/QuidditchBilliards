
#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <vector>
#include "CBMPLoader.h"
#include "OpenGLObject.h"
#include "Table.h"
#include "Flag.h"
#include "Balls.h"
#include "Cue.h"

/*
    ObjectMananger class, manage
  all objects in the application
 */

class ObjectManager
{
public:
	ObjectManager(CInputSystem * input);      // Constructor
	~ObjectManager();                         // Destructor

	/// Public interfaces
	void   Draw();      // Draw all objects
	void   Update();    // Update all objects

private:
	/// Members
	std::vector<OpenGLObject*> m_Objects;    // The vector stores all the objects
	CBMPLoader m_Textures[NUM_TEXTURES];     // Textures
	unsigned int * m_TexturePool;            // Texture pool offered to objects to pick textures
	CInputSystem * m_Input;                  // Pointer to input system

	/// Processes
	void   LoadTextures();          // Load textures required from files
	void   CreateObjects();         // New all objects
	void   SetInitialPosition();    // Set initial position of all objects
};

#endif // _OBJECTMANAGER_H_