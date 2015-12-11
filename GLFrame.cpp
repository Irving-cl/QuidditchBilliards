
#include "GLFrame.h"

/* Entrance of main function */
//===========================================================================//

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int ret = -1;
	GLApplication * appl = GLApplication::Create("OpenGL");			    // Create actual OpenGL program class
	if (appl != 0)
	{
		ret = appl->Main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);// Execute main loop of the program
		delete appl;													// Delete the program class
	}
	else
	{																	// An error occurred when creating the program class
		MessageBox(HWND_DESKTOP, "创建程序出错", "Error", MB_OK | MB_ICONEXCLAMATION);
	}
	return ret;
}

/* Handling the window messages */
//===========================================================================//

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LONG user_data = GetWindowLong(hWnd, GWL_USERDATA);					// Return the 32-bit program appending value defined by the user
	if (user_data == 0)
	{
		/// If the program is running for first time
		if (uMsg == WM_CREATE)											// Handling the message of creating windows
		{
			CREATESTRUCT * creation = reinterpret_cast<CREATESTRUCT *>(lParam);
			GLApplication * appl = reinterpret_cast<GLApplication *>(creation->lpCreateParams);
			SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<LONG>(appl));
			appl->m_IsVisible = true;									// Set the program to be visible
			return 0;
		}
	}
	else
	{	/// If the program is not running for first time, return the pointer to itself
		GLApplication * appl = reinterpret_cast<GLApplication *>(user_data);
		return appl->Message(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);					// Call the default message handling function
}

/* Constructor */
//===========================================================================//

GLApplication::GLApplication(const char * class_name)
{
	m_ClassName = class_name;											// Class name
	m_IsProgramLooping = true;											// Set the loop sign to be true
	m_IsVisible = false;												// Invisible
	m_ResizeDraw = false;												// Drawing disabled while resizing the window
	m_LastTickCount = 0;
}

//===========================================================================//

void GLApplication::TerminateApplication()
{
	PostMessage(m_Window, WM_QUIT, 0, 0);								// Send a quiting message
	m_IsProgramLooping = false;											// Stop the program loop
}

/* Message loop */
//===========================================================================//

LRESULT GLApplication::Message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)														// Handling different window message
	{
	case WM_SYSCOMMAND:												    // System command
		switch (wParam)
		{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0;
			break;
		}
		break;
	case WM_CLOSE:													    // Close the application
		TerminateApplication();										    // Call the terminate function
		return 0;
		break;
	case WM_EXITMENULOOP:
	case WM_EXITSIZEMOVE:
		m_LastTickCount = GetTickCount();							    // Update the tickcount
		return 0;
		break;
	case WM_MOVE:
		m_Window.SetPosX(LOWORD(lParam));							    // Update the position of the mouse
		m_Window.SetPosY(HIWORD(lParam));
		return 0;
		break;
	case WM_PAINT:
		if (m_ResizeDraw == true)									    // If redrawing is required
		{
			m_Window.ReshapeGL();									    // Resize the window
			Draw();													    // Redraw
			m_Window.SwapBuffers();									    // Swap two buffers
		}
		break;
	case WM_SIZING:													    // Window is changing size
	{
		RECT * rect = (RECT *)lParam;
		m_Window.SetWidth(rect->right - rect->left);				    // Set width of window
		m_Window.SetHeight(rect->bottom - rect->top);				    // Set height of window
		return TRUE;
	}
		break;
	case WM_SIZE:													    // After changing size
		switch (wParam)												    // Handling different window status
		{
		case SIZE_MINIMIZED:									        // Is minimized
			m_IsVisible = false;								        // If minimized, set it to be invisible
			return 0;
			break;
		case SIZE_MAXIMIZED:									        // Is maximized
		case SIZE_RESTORED:										        // Is restored
			m_IsVisible = true;									        // Set it to be visible
			m_Window.SetWidth(LOWORD(lParam));					        // Set the width of window
			m_Window.SetHeight(HIWORD(lParam));					        // Set the height of window
			m_Window.ReshapeGL();								        // Resizing the window
			m_LastTickCount = GetTickCount();					        // Update the tickcount
			return 0;
			break;
		}
		break;
	case WM_KEYDOWN:												    // Update info of keys pushed down								
		return 0;
		break;
	case WM_KEYUP:													    // Update info of keys released								
		return 0;
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);					// Call default message handling function
}

/* Mainloop of the program */
//===========================================================================//

int GLApplication::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/// Register a window
	WNDCLASSEX windowClass;												// Window class
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));						// Clear the frame
	windowClass.cbSize = sizeof(WNDCLASSEX);					        // Size of the structure
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	            // Set the window style
	windowClass.lpfnWndProc = (WNDPROC)(WindowProc);				    // WndProc handles the messages
	windowClass.hInstance = hInstance;							        // Set instance
	windowClass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);			// Set background
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);			        // Load cursor
	windowClass.lpszClassName = m_ClassName;							// Set class name
	if (RegisterClassEx(&windowClass) == 0)								// Attempt to register the window class
	{																	// NOTE: Failure, Should Never Happen
		MessageBox(HWND_DESKTOP, "注册窗口失败!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return -1;														// Exit and return false
	}
	while (m_IsProgramLooping)											// Loop until the program terminates
	{
		/// Create a window
		if (m_Window.Create("Quidditch", m_ClassName, false, hInstance, this) == true)
		{

			/// If the initialization failed, exit
			if (Init() == false)									    // Call the initialization function
			{															// Initialization failed
				TerminateApplication();									// Close the window and quit the program
			}
			else														// Succeed to start the message looping
			{
				MSG msg;												// MSG structrue
				bool isMessagePumpActive = true;
				m_LastTickCount = GetTickCount();						// Return tickcount
				//m_Keys.Clear();									    // Clear all the keys' info
				while (isMessagePumpActive == true)						// When there are messages, start message loop
				{														// Successfully create the window
					if (PeekMessage(&msg, m_Window, 0, 0, PM_REMOVE) != 0)
					{
						if (msg.message != WM_QUIT)
						{
							DispatchMessage(&msg);
						}
						else
						{
							isMessagePumpActive = false;
						}
					}
					/// If there are no messages
					else
					{
						if (m_IsVisible == false)						// If the window is invisible
						{
							WaitMessage();								// Pause the program and wait for messages
						}
						else											// If the it's visible
						{												// Execute message loop
							DWORD tickCount = GetTickCount();			// Return the tickcount value
							Update(tickCount - m_LastTickCount);		// Call the update function defined by user
							m_LastTickCount = tickCount;				// Set last tickcount
							Draw();										// Call the draw function defined by user
							m_Window.SwapBuffers();						// Swap two buffers
						}
					}
				}
			}
			/// Program comes to an end
			Uninit();												    // Uninitialzation
			m_Window.Destroy();											// Destroy the window
		}
		else															// There's a failure creating the window
		{
			MessageBox(HWND_DESKTOP, "创建OpenGL窗口错误", "Error", MB_OK | MB_ICONEXCLAMATION);
			m_IsProgramLooping = false;									// Stop program loop
		}
	}

	UnregisterClass(m_ClassName, hInstance);							// Cancel the window registered
	return 0;
}