
#include "Particle.h"

//===========================================================================//

static GLfloat colors[12][3] =
{
	{ 255.0f, 0.0f, 0.0f }, { 255.0f, 128.0f, 0.0f }, { 255.0f, 255.0f, 0.0f }, { 0.0f, 255.0f, 0.0f },
	{ 0.0f, 255.0f, 255.0f }, { 0.0f, 0.0f, 255.0f }, { 128.0f, 0.0f, 255.0f }
};

//===========================================================================//

ParticleExplosion::ParticleExplosion()
{
	m_Num = 0;
	m_List = NULL;
}

//===========================================================================//

ParticleExplosion::~ParticleExplosion()
{
	if (m_List)
	{
		delete [] m_List;
		m_List = NULL;
	}
}

//===========================================================================//

void ParticleExplosion::Init(int num)
{
	m_Num = num;
	m_List = new Particle[m_Num];

	/// Initialize each single particle
	for (int i = 0; i < m_Num; i++)
	{
		float x, y, z, vx, vy, vz;        // Position and velocity
		x = 0.0005f * (rand() % 9);
		y = 0.0005f * (rand() % 9) + 1.0f;
		z = 0.0005f * (rand() % 9);
		float v = 0.00004f;
		float alpha = rand() % 360;
		float beta = rand() % 90;
		int random = rand() % 2000;
		vy = v * sin(beta * PI / 180.0f) * random;
		vx = v * cos(beta * PI / 180.0f) * cos(alpha * PI / 180.0f) * random;
		vz = v * cos(beta * PI / 180.0f) * sin(alpha * PI / 180.0f) * random;

		m_List[i].position = Vector3(x, y, z);                        // Set position
		m_List[i].velocity = Vector3(vx, vy, vz);                     // Set velocity
		m_List[i].acceleration = Vector3(0.0, -0.0008f, 0.0);         // Set acceleration
		m_List[i].lifetime = 100.0f;                                  // Set life time
		m_List[i].size = 0.06f;                                       // Set size
		m_List[i].dec = 0.05f * (rand() % 50);                        // Set diminishing speed

		/// Set color
		int index = rand() % 7;
		m_List[i].color[0] = colors[index][0];
		m_List[i].color[1] = colors[index][1];
		m_List[i].color[2] = colors[index][2];
	}
}

//===========================================================================//

void ParticleExplosion::Draw()
{
	glPushMatrix();
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_TexturePool[9]);
		for (int i = 0; i < m_Num; i++)
		{
			float x = m_List[i].position.x;
			float y = m_List[i].position.y;
			float z = m_List[i].position.z;
			float size = m_List[i].size;
			glColor4f(m_List[i].color[0], m_List[i].color[1], m_List[i].color[2], m_List[i].lifetime / 100.0f);
			glNormal3f(0.0f, 0.0f, 1.0f);

			// Draw the particle
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x - size, y - size, z);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x - size, y + size, z);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x + size, y + size, z);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x + size, y - size, z);
			glEnd();
			glColor4f(0.75f, 0.75f, 0.75f, 1.0f);
		}
		glDisable(GL_BLEND);
	}
	glPopMatrix();
}

//===========================================================================//

void ParticleExplosion::Update()
{
	for (int i = 0; i< m_Num; ++i)
	{
		/// Update position
		m_List[i].position.x += m_List[i].velocity.x;
		m_List[i].position.y += m_List[i].velocity.y;
		m_List[i].position.z += m_List[i].velocity.z;

		/// Update velocity
		m_List[i].velocity.y += m_List[i].acceleration.y;

		/// Update lifetime
		m_List[i].lifetime -= m_List[i].dec;
	}
}