
#ifndef	_GLWINDOW_H_
#define	_GLWINDOW_H_

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

/*
    Window class
 */

class GLWindow
{
public:

	/// Constuctor
	GLWindow();
	bool	Create(const char * window_title,        // Create a window
		const char * class_name, bool fullscreen, HINSTANCE h_instance, LPVOID lpParam);
	void	Destroy();                               // Destroy the window
	bool	ChangeScreenSetting();                   // Change the window's settings
	void	ReshapeGL();                             // Reshape the window
	void	SwapBuffers() { ::SwapBuffers(m_hDC); }  // Swap buffers

	/// Set left-top position
	void	SetPosX(int x);
	void	SetPosX(unsigned short x) { SetPosX((signed short)x); }
	void	SetPosY(int y);
	void	SetPosY(unsigned short y) { SetPosY((signed short)y); }
	/// Return the window's size
	int		GetWidth();
	int		GetHeight();
	/// Set the window's size
	void	SetWidth(int width);
	void	SetHeight(int height);
	/// Return the position
	int		GetPosX();
	int		GetPosY();
	/// Set bits per pixel
	void	SetHiColor()	{ m_BitsPerPixel = 16; }
	void	SetTrueColor()	{ m_BitsPerPixel = 32; }

	operator HWND() { return m_hWnd; }
	HWND  GetHwnd() { return m_hWnd; }
	HDC  GetHDC()   { return m_hDC; }

private:
	HWND	m_hWnd;														// Window handle
	HDC		m_hDC;														// Device description
	HGLRC	m_hRC;														// Render description

	int		m_WindowPosX;												// Left-top X
	int		m_WindowPosY;												// Left-top Y
	int		m_WindowWidth;												// Width of window
	int		m_WindowHeight;												// Height of window
	int		m_ScreenWidth;												// Width of full screen
	int		m_ScreenHeight;												// Height of full screen
	int		m_BitsPerPixel;												// Bits per pixel
	bool	m_IsFullScreen;												// Is full screen
};

#endif	// _GLWINDOW_H_