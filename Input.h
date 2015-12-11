
#ifndef _INPUT_H_
#define _INPUT_H_

#include "stdafx.h"
#include "Vector.h"

#define IS_USEKEYBOARD  1
#define IS_USEMOUSE     2
#define IS_USEJOYSTICK  4
#define DINPUT_BUFFERSIZE  16

/* 
    Keyboard class 
 */

class CKeyboard
{
public:
	CKeyboard(LPDIRECTINPUT8 pDI, HWND hwnd);    // Constructor
	~CKeyboard();                                // Destructor

	bool KeyDown(char key);                      // Is a key pushed down
	bool KeyUp(char key);                        // Is a key released
	void Clear();                                // Clear the keyboard data
	bool Update();                               // Update the keyboard data
	bool Acquire();                              // Acquire the keyboard data
	bool Unacquire();                            // Stop acquiring the keyboard data

private:
	LPDIRECTINPUTDEVICE8  m_pDIDev;              // Keyboard device

	char    m_keys[256];                         // Keyboard data
};

/*
    Keyboard class
*/

class CMouse
{
public:
	CMouse(LPDIRECTINPUT8 pDI, HWND hwnd, bool isExclusive);    // Constructor
	~CMouse();                                                  // Destructor

	bool	IsLButtonPressed();                                 // Is left button pressed
	bool	IsRButtonPressed();                                 // Is right button pressed
	bool	IsMButtonPressed();                                 // Is middle button pressed
	Point2	GetMousePos();                                      // Get position of mouse
	bool	Update();                                           // Update state of mouse
	bool	Acquire();                                          // Acquire mouse data
	bool	Unacquire();                                        // Stop Acquiring mouse data
	int		m_iWidth;                                           // Window width
	int		m_iHeight;                                          // Window height

private:
	LPDIRECTINPUTDEVICE8	m_pDIDev;                           // Mouse device
	DIDEVICEOBJECTDATA      m_diData[DINPUT_BUFFERSIZE];        // Buffer data
	Point2					m_iMousePos;                        // Mouse position
};

/*
    Input system class
 */

class CInputSystem
{
public:
	CInputSystem()  { m_pInput = this; }                        // Constructor
	~CInputSystem() { ShutDown(); }                             // Destructor

	bool Init(HWND hwnd, HINSTANCE appInstance,                 // Initialize the devices
		bool isExclusive, DWORD flags = 0);
	bool ShutDown();                                            // Shut down the devices
	void AcquireAll();                                          // Acquire data from all devices
	void UnacquireAll();                                        // Stop acquiring data from all devices
	void Update();                                              // Update state of all devices
	
	Vector3  GetMousePosition();                                // Get 3D position of mouse
	CKeyboard*  GetKeyboard(){ return  m_pKeyboard; }           // Get the keyboard
	CMouse*       GetMouse() { return  m_pMouse; }              // Get the mouse

	static HWND GetSysHWnd() { return  m_hWnd; }                // Get the window handle
	static CInputSystem* GetSysInput(){ return  m_pInput; }     // Get the system input

private:
    /// Members
	static CInputSystem * m_pInput;                             // Input system
	static HWND m_hWnd;                                         // Window handle
	CKeyboard * m_pKeyboard;                                    // Keyboard
	CMouse * m_pMouse;                                          // Mouse
	LPDIRECTINPUT8 m_pDI;                                       // Input device

};

/* Inline operations of CKeyboard */
//===========================================================================//

inline bool CKeyboard::KeyDown(char key)
{
	return (m_keys[key] & 0x80) ? true : false;
}


inline bool CKeyboard::KeyUp(char key)
{
	return (m_keys[key] & 0x80) ? false : true;
}

inline void CKeyboard::Clear()
{
	ZeroMemory(m_keys, 256 * sizeof(char));
}

inline bool CKeyboard::Acquire()
{
	Clear();
	return (!FAILED(m_pDIDev->Acquire()));
}

inline bool CKeyboard::Unacquire()
{
	Clear();
	return (!FAILED(m_pDIDev->Unacquire()));
}

/* Inline operations of CMouse */
//===========================================================================//

inline Point2 CMouse::GetMousePos()
{
	return m_iMousePos;
}

inline bool CMouse::Acquire()
{
	return (!FAILED(m_pDIDev->Acquire()));
}

inline bool CMouse::Unacquire()
{
	return (!FAILED(m_pDIDev->Unacquire()));
}

/* Inline operations of CInputSystem */
//===========================================================================//

inline void CInputSystem::AcquireAll()
{
	if (m_pKeyboard)	m_pKeyboard->Acquire();
	if (m_pMouse)		m_pMouse->Acquire();
}

inline void CInputSystem::UnacquireAll()
{
	if (m_pKeyboard)	m_pKeyboard->Unacquire();
	if (m_pMouse)		m_pMouse->Unacquire();
}

#endif // _INPUT_H_
