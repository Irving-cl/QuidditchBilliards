
#include "Input.h"

//===========================================================================//

CKeyboard::CKeyboard(LPDIRECTINPUT8 pDI, HWND hwnd)
{
	/// Create device object
	if (FAILED(pDI->CreateDevice(GUID_SysKeyboard, &m_pDIDev, NULL)))
	{
		MessageBox(NULL, "���������豸����ʧ�ܣ�", "����", MB_OK);
	}

	/// Set data format
	if (FAILED(m_pDIDev->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(NULL, "���ü������ݸ�ʽʧ�ܣ�", "����", MB_OK);
	}

	/// Set cooperative level
	if (FAILED(m_pDIDev->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		MessageBox(NULL, "���ü���Э�����ʧ�ܣ�", "����", MB_OK);
	}

	/// Acquire device
	if (FAILED(m_pDIDev->Acquire()))
	{
		MessageBox(NULL, "��������豸ʧ�ܣ�", "����", MB_OK);
	}

	Clear();    // Clear keyboard data
}

//===========================================================================//

CKeyboard::~CKeyboard()
{
	if (m_pDIDev)
	{
		m_pDIDev->Unacquire();
		m_pDIDev->Release();
	}
}

//===========================================================================//

bool CKeyboard::Update()
{
	if (FAILED(m_pDIDev->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
	{
		if (FAILED(m_pDIDev->Acquire()))
			return false;

		if (FAILED(m_pDIDev->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
			return false;
	}

	return TRUE;
}

//===========================================================================//

CMouse::CMouse(LPDIRECTINPUT8 pDI, HWND hwnd, bool isExclusive)
{
	/// Get current window's size
	RECT r;
	GetClientRect(hwnd, &r);
	m_iWidth = r.right - r.left;
	m_iHeight = r.bottom - r.top;
	m_iMousePos.x = m_iWidth / 2;
	m_iMousePos.y = m_iHeight / 2;

	/// Create device object
	if (FAILED(pDI->CreateDevice(GUID_SysMouse, &m_pDIDev, NULL)))
	{
		MessageBox(NULL, "��������豸����ʧ�ܣ�", "����", MB_OK);
	}

	/// Set data format
	if (FAILED(m_pDIDev->SetDataFormat(&c_dfDIMouse)))
	{
		MessageBox(NULL, "����������ݸ�ʽʧ�ܣ�", "����", MB_OK);
	}

	DWORD flags;
	if (isExclusive)
		flags = DISCL_FOREGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY;
	else
		flags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;

	/// Set cooperative level
	if (FAILED(m_pDIDev->SetCooperativeLevel(hwnd, flags)))
	{
		MessageBox(NULL, "�������Э�����ʧ�ܣ�", "����", MB_OK);
	}

	/// Set mouse property
	DIPROPDWORD  dipROPWORD;
	dipROPWORD.diph.dwSize = sizeof(DIPROPDWORD);
	dipROPWORD.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipROPWORD.diph.dwObj = 0;
	dipROPWORD.diph.dwHow = DIPH_DEVICE;
	dipROPWORD.dwData = DINPUT_BUFFERSIZE;

	if (FAILED(m_pDIDev->SetProperty(DIPROP_BUFFERSIZE, &dipROPWORD.diph)))
	{
		MessageBox(NULL, "��������豸����ʧ�ܣ�", "����", MB_OK);
	}

	/// Acquire device
	if (FAILED(m_pDIDev->Acquire()))
	{
		MessageBox(NULL, "��������豸ʧ�ܣ�", "����", MB_OK);
	}

}

//===========================================================================//

bool CMouse::IsLButtonPressed()
{
	for (int i = 0; i<DINPUT_BUFFERSIZE; i++)
	{
		if ((m_diData[i].dwOfs == DIMOFS_BUTTON0) &&
			(m_diData[i].dwData & 0x80))
			return true;
	}
	return false;
}

//===========================================================================//

bool CMouse::IsRButtonPressed()
{
	for (int i = 0; i<DINPUT_BUFFERSIZE; i++)
	{
		if ((m_diData[i].dwOfs == DIMOFS_BUTTON1) &&
			(m_diData[i].dwData & 0x80))
			return true;
	}
	return false;
}

//===========================================================================//

bool CMouse::IsMButtonPressed()
{
	for (int i = 0; i<DINPUT_BUFFERSIZE; i++)
	{
		if ((m_diData[i].dwOfs == DIMOFS_BUTTON2) &&
			(m_diData[i].dwData & 0x80))
			return true;
	}
	return false;
}

//===========================================================================//

CMouse::~CMouse()
{
	if (m_pDIDev)
	{
		m_pDIDev->Unacquire();
		m_pDIDev->Release();
	}
}

//===========================================================================//

bool CMouse::Update()
{
	HRESULT  hr;
	DWORD  dwReadNum = 1;
	int i;

	ZeroMemory(m_diData, sizeof(DIDEVICEOBJECTDATA) * DINPUT_BUFFERSIZE);    // Clear the buffer

	for (i = 0; i < DINPUT_BUFFERSIZE; i++)
	{
		hr = m_pDIDev->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),
			&m_diData[i], &dwReadNum, 0);
		if (hr == DIERR_INPUTLOST)
		{
			m_pDIDev->Acquire();
			hr = m_pDIDev->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),
				&m_diData[i], &dwReadNum, 0);
			if (FAILED(hr))
			{
				MessageBox(NULL, "ȡ����껺��������ʧ��!", "����", MB_OK);
				return false;
			}
		}

		/// Update position of mouse
		if (m_diData[i].dwOfs == DIMOFS_X)
			m_iMousePos.x += m_diData[i].dwData;
		if (m_diData[i].dwOfs == DIMOFS_Y)
			m_iMousePos.y += m_diData[i].dwData;

		/// Confine mouse in the window
		if (m_iMousePos.x < 0)
			m_iMousePos.x = 0;
		if (m_iMousePos.x> m_iWidth)
			m_iMousePos.x = m_iWidth;
		if (m_iMousePos.y < 0)
			m_iMousePos.y = 0;
		if (m_iMousePos.y > m_iHeight)
			m_iMousePos.y = m_iHeight;
	}
	return true;
}

//===========================================================================//

CInputSystem* CInputSystem::m_pInput = NULL;
HWND CInputSystem::m_hWnd = NULL;

//===========================================================================//

bool CInputSystem::Init(HWND hwnd, HINSTANCE appInstance,
	bool isExclusive, DWORD flags)
{
	m_pKeyboard = NULL;
	m_pMouse = NULL;

	m_hWnd = hwnd;

	// Create DirectX interface object
	if (FAILED(DirectInput8Create(appInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void **)&m_pDI, NULL)))
	{
		MessageBox(NULL, "����DirectInput�ӿڶ���ʧ��!", "����", MB_OK);
		return false;
	}

	// Create keyboard
	if (flags & IS_USEKEYBOARD)
	{
		m_pKeyboard = new CKeyboard(m_pDI, hwnd);
	}

	// Create mouse
	if (flags & IS_USEMOUSE)
	{
		m_pMouse = new CMouse(m_pDI, hwnd, true);
	}

	return true;

}

//===========================================================================//

void CInputSystem::Update()
{
	// Update keyboard
	if (m_pKeyboard)
		m_pKeyboard->Update();

	// Update mouse
	if (m_pMouse)
		m_pMouse->Update();
}

//===========================================================================//

bool CInputSystem::ShutDown()
{
	UnacquireAll();

	if (m_pKeyboard)
	{
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	if (m_pMouse)
	{
		delete m_pMouse;
		m_pMouse = NULL;
	}

	// Release device interface
	if (FAILED(m_pDI->Release()))
		return false;

	return true;
}

//===========================================================================//

Vector3  CInputSystem::GetMousePosition()
{
	float depth[2];
	Point2 p;

	// Get position of mouse
	p = m_pMouse->GetMousePos();

	GLdouble x, y, z;

	// Read depth of pixels
	glReadPixels(p.x, p.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, depth);

	// Get modelview matrix and projection matrix
	GLdouble model[16], project[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, project);

	// Compute world position of this point
	GLint viewport[4] = { 0, 0, m_pMouse->m_iWidth, m_pMouse->m_iHeight };
	gluUnProject(p.x, p.y, depth[0], model, project, viewport, &x, &y, &z);

	return Vector3((float)x, (float)y, (float)z);
}