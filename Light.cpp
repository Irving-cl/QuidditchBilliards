
#include "Light.h"

//===========================================================================//

/// Default light
static float ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
static float diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
static float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
static float lightPosition[] = { 10.0f, 20.0f, 10.0f, 1.0f };
static float specularRef[] = { 0.8f, 0.8f, 0.8f, 1.0f };

//===========================================================================//

Light::Light()
{
	// Empty
}

//===========================================================================//

Light::~Light()
{
	// Empty
}

//===========================================================================//

void Light::Init()
{
	glEnable(GL_LIGHTING);

	/// Set default light
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT0);
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularRef);
	glMateriali(GL_FRONT, GL_SHININESS, 64);
}

//===========================================================================//

void Light::SetInput(CInputSystem * input)
{
	m_Input = input;
}

//===========================================================================//

void Light::Update()
{
	if (m_Input->GetKeyboard()->KeyDown(DIK_O))
		glEnable(GL_LIGHT0);
	if (m_Input->GetKeyboard()->KeyDown(DIK_P))
		glDisable(GL_LIGHT0);
}