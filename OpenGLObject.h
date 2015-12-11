
#ifndef _OPENGLOBJECT_H_
#define _OPENGLOBJECT_H_

#include "Vector.h"
#include "QuidditchConstants.h"

/* 
   An interface that must be
 inherited by actual OpenGL
 object
 */

class OpenGLObject
{
public:
	/// Virtual methods must be implemented by actual class
	virtual void Draw() = 0;                // Draw the object
	virtual void Update() = 0;              // Update state of itself

	/// Set the pointer to texture pool
	void SetTexturePool(unsigned int * texturePool)
	{
		m_TexturePool = texturePool;
	}

	// Set the position
	void SetPosition(Vector3 position)
	{
		m_Position = position;
	}

	// Get the position
	Vector3 GetPosition()
	{
		return m_Position;
	}

protected:
	Vector3 m_Position;
	unsigned int * m_TexturePool;
};

#endif // _OPENGLOBJECT_H_