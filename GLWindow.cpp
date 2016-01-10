
#include "GLWindow.h"												

//===========================================================================//

GLWindow::GLWindow()
{
	m_WindowPosX = 0;
	m_WindowPosY = 0;
	m_WindowWidth = 1024;
	m_WindowHeight = 768;
	m_ScreenWidth = 1024;
	m_ScreenHeight = 768;
	m_BitsPerPixel = 16;
	m_IsFullScreen = false;

	m_hWnd = 0;
	m_hDC = 0;
	m_hRC = 0;
}

//===========================================================================//

int GLWindow::GetWidth()
{
	if (m_IsFullScreen == true)
	{
		return m_ScreenWidth;
	}
	else
	{
		return m_WindowWidth;
	}
}

//===========================================================================//

int GLWindow::GetHeight()
{
	if (m_IsFullScreen == true)
	{
		return m_ScreenHeight;
	}
	else
	{
		return m_WindowHeight;
	}
}

//===========================================================================//

void GLWindow::SetWidth(int width)
{
	if (m_IsFullScreen == true)
	{
		m_ScreenWidth = width;
	}
	else
	{
		m_WindowWidth = width;
	}
}

//===========================================================================//

void GLWindow::SetHeight(int height)
{
	if (m_IsFullScreen == true)
	{
		m_ScreenHeight = height;
	}
	else
	{
		m_WindowHeight = height;
	}
}

//===========================================================================//

int GLWindow::GetPosX()
{
	if (m_IsFullScreen == false)
	{
		return m_WindowPosX;
	}
	return 0;
}

//===========================================================================//

int GLWindow::GetPosY()
{
	if (m_IsFullScreen == false)
	{
		return m_WindowPosY;
	}
	return 0;
}

//===========================================================================//

void GLWindow::SetPosX(int x)
{
	if (m_IsFullScreen == false)
	{
		m_WindowPosX = x;
	}
}

//===========================================================================//

void GLWindow::SetPosY(int y)
{
	if (m_IsFullScreen == false)
	{
		m_WindowPosY = y;
	}
}

//===========================================================================//

void GLWindow::ReshapeGL()
{
	GLsizei width = GetWidth();
	GLsizei height = GetHeight();
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//===========================================================================//

bool GLWindow::ChangeScreenSetting()
{
	DEVMODE dmScreenSettings;
	ZeroMemory(&dmScreenSettings, sizeof(DEVMODE));
	dmScreenSettings.dmSize = sizeof(DEVMODE);
	dmScreenSettings.dmPelsWidth = GetWidth();
	dmScreenSettings.dmPelsHeight = GetHeight();
	dmScreenSettings.dmBitsPerPel = m_BitsPerPixel;	
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	/// Change display mode
	if (ChangeDisplaySettings(&dmScreenSettings, 0) != DISP_CHANGE_SUCCESSFUL)
	{
		return false;													// Return false when it fails
	}

	return true;
}

//===========================================================================//

bool GLWindow::Create(const char * window_title, const char * class_name, bool fullscreen, HINSTANCE h_instance, LPVOID lpParam)
{
	m_IsFullScreen = fullscreen;
	int nX = 0;
	int nY = 0;
	PIXELFORMATDESCRIPTOR pfd =											// Set pixel format descriptor
	{
		sizeof(PIXELFORMATDESCRIPTOR),									// Size of the structrue
		1,																// Version number
		PFD_DRAW_TO_WINDOW |											// Output to one window
		PFD_SUPPORT_OPENGL |											// Support OpenGL
		PFD_STEREO |											        // Color buffer is stereo
		PFD_DOUBLEBUFFER,												// Color buffer is double buffer
		PFD_TYPE_RGBA,													// Use RGBA mode
		m_BitsPerPixel,													// Bits per pixel
		0, 0, 0, 0, 0, 0,												// Use default color settings
		0,																// No alpha buffer
		0,																// Alpha offset count
		0,																// No accumulated buffer
		0, 0, 0, 0,                                                     // No offset
		32,																// 32-bit depth buffer
		0,
		0,
		PFD_MAIN_PLANE,													// Must be PFD_MAIN_PLANE
		0,
		0, 0, 0															// Out of time
	};

	DWORD windowStyle = WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX;
	DWORD windowExtendedStyle = WS_EX_APPWINDOW;

	/// Resize the window
	RECT windowRect = { GetPosX(), GetPosY(), GetPosX() + GetWidth(), GetPosY() + GetHeight() };
	if (m_IsFullScreen == false)
	{
		windowExtendedStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	    // Give the window a 3D image
		int wid = GetSystemMetrics(SM_CXSCREEN);		                // Get screen's width
		int hei = GetSystemMetrics(SM_CYSCREEN);		                // Get screen's height
		nX = (wid - GetWidth()) / 2;                                    // Put the window into middle
		nY = (hei - GetHeight()) / 2;
		/// Adjust window's size
		AdjustWindowRectEx(&windowRect, windowStyle, 0, windowExtendedStyle);
		
		if (windowRect.left < 0)
		{
			windowRect.right -= windowRect.left;
			windowRect.left = 0;
		}
		if (windowRect.top < 0)
		{
			windowRect.bottom -= windowRect.top;
			windowRect.top = 0;
		}
		ShowCursor(true);
	}

	/// ´´½¨´°¿Ú
	m_hWnd = CreateWindowEx(windowExtendedStyle,
		class_name,
		window_title,
		windowStyle,
		nX, nY,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		HWND_DESKTOP,
		0,
		h_instance,
		lpParam);

	while (m_hWnd != 0)
	{
		m_hDC = GetDC(m_hWnd);
		if (m_hDC == 0)
		{
			break;
		}

		GLuint PixelFormat = ChoosePixelFormat(m_hDC, &pfd);
		if (PixelFormat == 0)
		{
			break;
		}
		if (SetPixelFormat(m_hDC, PixelFormat, &pfd) == false)
		{
			break;
		}
		m_hRC = wglCreateContext(m_hDC);
		if (m_hRC == 0)
		{
			break;
		}
		if (wglMakeCurrent(m_hDC, m_hRC) == false)
		{
			break;
		}

		ShowWindow(m_hWnd, SW_NORMAL);
		ReshapeGL();
		return true;
	}

	Destroy();
	return false;
}

//===========================================================================//

void GLWindow::Destroy()
{
	if (m_hWnd != 0)
	{
		if (m_hDC != 0)
		{
			wglMakeCurrent(m_hDC, 0);
			if (m_hRC != 0)
			{
				wglDeleteContext(m_hRC);
				m_hRC = 0;
			}
			ReleaseDC(m_hWnd, m_hDC);
			m_hDC = 0;
		}
		DestroyWindow(m_hWnd);
		m_hWnd = 0;
	}

	if (m_IsFullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(true);
	}
}
