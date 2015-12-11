
#ifndef	_GLFRAME_H_
#define	_GLFRAME_H_

#include "stdafx.h"
#include "GLWindow.h"											

/*  
    A basic class that would be inherited 
  by actual OpenGL program class 
 */

class GLApplication
{
public:
	static GLApplication * Create(const char * class_name); 	// Create subclass
	virtual ~GLApplication() {};

protected:
	/* Virtual methods that must be inherited by subclass */
	virtual bool	Init() = 0;							        // Initialization
	virtual void	Uninit() = 0;							    // Uninitialization
	virtual void	Update(DWORD milliseconds) = 0;				// Update of the program
	virtual void	Draw() = 0;									// Draw the scene of the program

	void	TerminateApplication();								// Terminate the  application
	void	ResizeDraw(bool enable) { m_ResizeDraw = enable; }	// If drawing is enabled while changing the window's size 

	/* Constructor */
	GLApplication(const char * class_name);
	GLWindow	m_Window;										// Window class
private:
	/* Main loop of the program */
	friend int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	int		Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	/* Message callback function */
	friend LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT	Message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	const char* m_ClassName;									// Program name
	bool		m_IsProgramLooping;								// If the sign is false, the program ends
	bool		m_IsVisible;									// Is the window visible
	bool		m_ResizeDraw;									// Is drawing function called when resizing the window
	DWORD		m_LastTickCount;								// Value of last tickcount
};

#endif	// _GLFRAMEWORK_H_