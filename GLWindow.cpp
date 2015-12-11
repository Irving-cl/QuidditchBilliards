
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
		/// 判断窗口的左上角是否隐藏在桌面外
		if (windowRect.left < 0)										/**< 如果窗口X坐标为负，移动坐标到0处，并调整窗口的位置 */
		{
			windowRect.right -= windowRect.left;
			windowRect.left = 0;
		}
		if (windowRect.top < 0)											/**< 如果窗口Y坐标为负，移动坐标到0处，并调整窗口的位置 */
		{
			windowRect.bottom -= windowRect.top;
			windowRect.top = 0;
		}
		ShowCursor(true);
	}

	/// 创建窗口
	m_hWnd = CreateWindowEx(windowExtendedStyle,						/**< 窗口的扩展风格 */
		class_name,									/**< 窗口的类名 */
		window_title,								/**< 窗口标题 */
		windowStyle,								/**< 窗口的风格 */
		nX, nY,                                      /**< 窗口的左上角位置 */
		windowRect.right - windowRect.left,			/**< 窗口的宽度 */
		windowRect.bottom - windowRect.top,			/**< 窗口的高度 */
		HWND_DESKTOP,								/**< 窗口的父窗口为桌面 */
		0,											/**< 无菜单 */
		h_instance,									/**< 传入窗口的实例句柄 */
		lpParam);									/**< 传入程序类参数 */

	while (m_hWnd != 0)													/**< 窗口是否创建成功 */
	{
		m_hDC = GetDC(m_hWnd);											/**< 返回窗口的设备描述表 */
		if (m_hDC == 0)													/**< 如果为空 */
		{																/**< 失败 */
			break;
		}

		GLuint PixelFormat = ChoosePixelFormat(m_hDC, &pfd);			/**< 查找一个兼容的像素格式 */
		if (PixelFormat == 0)											/**< 如果没找到 */
		{																/**< 失败 */
			break;
		}
		if (SetPixelFormat(m_hDC, PixelFormat, &pfd) == false)			/**< 设置像素格式 */
		{																/**< 失败 */
			break;
		}
		m_hRC = wglCreateContext(m_hDC);								/**< 创建OpenGL的渲染描述表 */
		if (m_hRC == 0)													/**< 如果为空 */
		{																/**< 失败 */
			break;
		}
		if (wglMakeCurrent(m_hDC, m_hRC) == false)						/**< 设置当前的OpenGL的渲染对象为当前的窗口 */
		{																/**< 失败 */
			break;
		}

		ShowWindow(m_hWnd, SW_NORMAL);									/**< 显示窗口 */
		ReshapeGL();													/**< 告诉OpenGL调整窗口大小 */
		return true;													/**< 成功返回 */
	}

	Destroy();															/**< 释放资源 */
	return false;														/**< 返回失败 */
}

//===========================================================================//

void GLWindow::Destroy()
{
	if (m_hWnd != 0)										/**< 窗口句柄是否存在 */
	{
		if (m_hDC != 0)										/**< 窗口设备描述表是否存在 */
		{
			wglMakeCurrent(m_hDC, 0);						/**< 设置当前的OpenGL的渲染对象为空NULL */
			if (m_hRC != 0)									/**< OpenGL的渲染描述表是否存在 */
			{
				wglDeleteContext(m_hRC);					/**< 释放OpenGL的渲染描述表 */
				m_hRC = 0;									/**< 设置OpenGL的渲染描述表为0 */
			}
			ReleaseDC(m_hWnd, m_hDC);						/**< 释放窗口的设备描述表 */
			m_hDC = 0;										/**< 设置窗口的设备描述表为0 */
		}
		DestroyWindow(m_hWnd);								/**< 删除窗口 */
		m_hWnd = 0;											/**< 设置窗口句柄为0 */
	}

	if (m_IsFullScreen)										/**< 如果为全屏模式，在程序结束后，变换到窗口模式，并显示鼠标 */
	{
		ChangeDisplaySettings(NULL, 0);						/**< 变换到窗口模式 */
		ShowCursor(true);									/**< 显示鼠标 */
	}
}
