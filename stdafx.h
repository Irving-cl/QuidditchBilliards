
#ifndef _STDAFX_H_
#define _STDAFX_H_

/* Common headers */
#include <windows.h>
#include <stdio.h>
#include <math.h>       
#include <cmath>
#include <time.h>

/* GL headers */
#include <gl\gl.h>				 
#include <gl\glu.h>
#include <glaux.h>
#include <glext.h>

/* DirectX header */
#define DIRECTINPUT_VERSION  0x0800
#include <dinput.h>

/* OpenGL lib */
#pragma comment(lib, "opengl32.lib")		
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")	

/* DirectX lib */
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

/* Forbid the warning of type transforming by the complier */
#pragma warning(disable: 4311)                                 
#pragma warning(disable: 4312)
#pragma warning(disable: 4244)
#pragma warning(disable: 4018)
#pragma warning(disable: 4267)

#endif // _STDAFX_H_