
#include "Flag.h"

//===========================================================================//

Flag::Flag()
{
	m_TexturePool = NULL;
	m_Cylinder = new Cylinder();
	hold = 0.0f;
	wiggle_count = 0;
	/// Initialize points
	for (int x = 0; x < 45; ++x)
	{
		for (int y = 0; y < 45; ++y)
		{
			m_Points[x][y][0] = float(x / FLAG_PARAMETER - 4.5f);
			m_Points[x][y][1] = float(y / FLAG_PARAMETER);
			m_Points[x][y][2] = float(sin((((x / FLAG_PARAMETER) * 80.0f) / 360.0f) * PI * 2.0f));
		}
	}
}

//===========================================================================//

Flag::~Flag()
{
	if (m_Cylinder)
	{
		delete m_Cylinder;
		m_Cylinder = NULL;
	}
}

//===========================================================================//

void Flag::Draw()
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, m_Position.z);
		/// Draw the pole
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, m_TexturePool[5]);
			glRotatef(90.0f, -1.0f, 0.0f, 0.0f);            // Rotate to vertical
			gluCylinder(m_Cylinder->GetQuadratic(), 
				FLAG_ROLE_RADIUS, FLAG_ROLE_RADIUS, FLAG_ROLE_LENGTH, 32, 32);
			m_Cylinder->DrawCircleArea(0.0, 0.0, 
				FLAG_ROLE_LENGTH, FLAG_ROLE_RADIUS, 32);    // Top  
			m_Cylinder->DrawCircleArea(0.0, 0.0, 
				0.0, FLAG_ROLE_RADIUS, 32);                 // Bottom
		}
		glPopMatrix();
		/// Draw the flag
		glPushMatrix();
		{
			glTranslatef(-0.4f, 3.1f, 0.0f);
			int x, y;
			float float_x, float_y, float_xb, float_yb;
			glBindTexture(GL_TEXTURE_2D, m_TexturePool[7]);
			glBegin(GL_QUADS);
			for (x = 0; x < 44; x++)
			{
				for (y = 0; y < 44; y++)
				{
					float_x = float(x) / 44.0f;
					float_y = float(y) / 44.0f;
					float_xb = float(x + 1) / 44.0f;
					float_yb = float(y + 1) / 44.0f;

					glTexCoord2f(float_x, float_y);
					glVertex3f(m_Points[x][y][0], m_Points[x][y][1], m_Points[x][y][2]);

					glTexCoord2f(float_x, float_yb);
					glVertex3f(m_Points[x][y + 1][0], m_Points[x][y + 1][1], m_Points[x][y + 1][2]);

					glTexCoord2f(float_xb, float_yb);
					glVertex3f(m_Points[x + 1][y + 1][0], m_Points[x + 1][y + 1][1], m_Points[x + 1][y + 1][2]);

					glTexCoord2f(float_xb, float_y);
					glVertex3f(m_Points[x + 1][y][0], m_Points[x + 1][y][1], m_Points[x + 1][y][2]);
				}
			}
			glEnd();
		}
		glPopMatrix();
		/// Draw two ropes connects the pole and the flag
		glPushMatrix();
		{
			glLineStipple(3, LINE_PATTERN);
			glBegin(GL_LINES);
			glVertex3f(0.0f, 3.1f, 0.0f);
			glVertex3f(m_Points[44][0][0] - 0.4f, 3.1f, m_Points[44][0][2]);
			glVertex3f(0.0f, 7.5f, 0.0f);
			glVertex3f(m_Points[44][44][0] - 0.4f, 7.5f, m_Points[44][44][2]);
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

//===========================================================================//

void Flag::Update()
{
	if (wiggle_count == 3)
	{
		for (int y = 0; y < 45; y++)
		{
			hold = m_Points[0][y][2];
			for (int x = 0; x < 44; x++)
			{
				m_Points[x][y][2] = m_Points[x + 1][y][2];
			}
			m_Points[44][y][2] = hold;
		}
		wiggle_count = 0;
	}

	wiggle_count++;
}

//===========================================================================//