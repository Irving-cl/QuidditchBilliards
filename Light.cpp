
#include "Light.h"

//===========================================================================//

/// Default light
static float ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
static float lightPosition[] = { 0.0f, 15.0f, 0.0f, 1.0f };

//===========================================================================//

Light::Light()
{

}

//===========================================================================//

Light::~Light()
{

}

//===========================================================================//

void Light::Init()
{
	glEnable(GL_LIGHTING);

	/// Set default light
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}