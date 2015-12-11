
#ifndef _QUIDDITCH_H_
#define _QUIDDITCH_H_

#include "GLFrame.h"
#include "CameraRotate.h"
#include "Input.h"
#include "ObjectManager.h"

class Quidditch : public GLApplication
{
public:
	bool   Init();
	void   Uninit();
	void   Update(DWORD milliseconds);
	void   Draw();

private:
	friend class GLApplication;
	Quidditch(const char * class_name);

	/// Members
	CameraRotate * m_pCamera;                // Camera
	CInputSystem * m_pInput;                 // DirectX input system
	ObjectManager * m_pObjectManager;        // Object manager

	/// Processes
	void   UpdateCamera();                   // Update camera in accordance with input
};

#endif // _QUIDDITCH_H_