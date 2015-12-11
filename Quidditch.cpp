#include "Quidditch.h"

//===========================================================================//

GLApplication * GLApplication::Create(const char * class_name)
{
	Quidditch * quidditch = new Quidditch(class_name);
	return reinterpret_cast<GLApplication *>(quidditch);
}

//===========================================================================//

Quidditch::Quidditch(const char* class_name) : GLApplication(class_name)
{
	/* empty */
}

//===========================================================================//

bool Quidditch::Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LINE_STIPPLE);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	ResizeDraw(true);

	/// Create instances of members and initialize them
	m_pCamera = new CameraRotate();
	m_pInput = new CInputSystem();
	m_pInput->Init(this->m_Window.GetHwnd(), (HINSTANCE)GetModuleHandle(NULL),
		true, IS_USEKEYBOARD);
	m_pObjectManager = new ObjectManager(m_pInput);

	return true;
}

//===========================================================================//

void Quidditch::Uninit()
{
	/// Delete members and set the pointers to NULL
	if (m_pInput)
	{
		delete m_pInput;
		m_pInput = NULL;
	}

	if (m_pCamera)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}

	if (m_pObjectManager)
	{
		delete m_pObjectManager;
		m_pObjectManager = NULL;
	}
}

//===========================================================================//

void Quidditch::Update(DWORD milliseconds)
{
	/// Update input system
	m_pInput->Update();

	/// When esc is pressed, terminate the application
	if (m_pInput->GetKeyboard()->KeyDown(DIK_ESCAPE))
	{
		TerminateApplication();
	}

	UpdateCamera();    // Update camera

	/// Update all objects 
	m_pObjectManager->Update();
}

//===========================================================================//

void Quidditch::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	m_pCamera->SetLook();        // Set view angle and view position
	m_pObjectManager->Draw();    // Draw all objects 
	glFlush();
}

//===========================================================================//

void Quidditch::UpdateCamera()
{
	if (m_pInput->GetKeyboard()->KeyDown(DIK_A))
	{
		m_pCamera->LRotate();
	}
	if (m_pInput->GetKeyboard()->KeyDown(DIK_D))
	{
		m_pCamera->RRotate();
	}
	if (m_pInput->GetKeyboard()->KeyDown(DIK_W))
	{
		m_pCamera->URotate();
	}
	if (m_pInput->GetKeyboard()->KeyDown(DIK_S))
	{
		m_pCamera->DRotate();
	}
	m_pCamera->UpdatePosition();
}