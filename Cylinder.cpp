
#include "Cylinder.h"

//===========================================================================//

Cylinder::Cylinder()
{
	m_Quadratic = gluNewQuadric();
}

//===========================================================================//

Cylinder::~Cylinder()
{
	gluDeleteQuadric(m_Quadratic);
	m_Quadratic = NULL;
}

//===========================================================================//

void Cylinder::DrawCircleArea(float cx, float cy, float cz, float r, int num_segments)
{
	GLfloat vertex[4];

	const GLfloat delta_angle = 2.0 * PI / num_segments;
	glBegin(GL_TRIANGLE_FAN);

	vertex[0] = cx;
	vertex[1] = cy;
	vertex[2] = cz;
	vertex[3] = 1.0;
	glVertex4fv(vertex);

	/// Draw the vertex on the contour of the circle   
	for (int i = 0; i < num_segments; i++)
	{
		vertex[0] = std::cos(delta_angle * i) * r + cx;
		vertex[1] = std::sin(delta_angle * i) * r + cy;
		vertex[2] = cz;
		vertex[3] = 1.0;
		glVertex4fv(vertex);
	}

	vertex[0] = 1.0 * r + cx;
	vertex[1] = 0.0 * r + cy;
	vertex[2] = cz;
	vertex[3] = 1.0;
	glVertex4fv(vertex);
	glEnd();
}

//===========================================================================//

GLUquadricObj* Cylinder::GetQuadratic()
{
	return m_Quadratic;
}