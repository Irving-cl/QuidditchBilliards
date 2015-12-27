
#include "Room.h"

//===========================================================================//

Room::Room()
{
	// Empty
}

//===========================================================================//

Room::~Room()
{
	// Empty
}

//===========================================================================//

void Room::Draw()
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, m_Position.z);
		unsigned int tex1_ID = m_TexturePool[8];

		/// Front
		glBindTexture(GL_TEXTURE_2D, tex1_ID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(ROOM_LENGTH, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(ROOM_LENGTH, ROOM_LENGTH, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, ROOM_LENGTH, 0.0f);
		glEnd();

		/// Back
		glBindTexture(GL_TEXTURE_2D, tex1_ID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(ROOM_LENGTH, 0.0f, ROOM_LENGTH);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, ROOM_LENGTH);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, ROOM_LENGTH, ROOM_LENGTH);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(ROOM_LENGTH, ROOM_LENGTH, ROOM_LENGTH);
		glEnd();

		/// Top
		glBindTexture(GL_TEXTURE_2D, tex1_ID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, ROOM_LENGTH, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(ROOM_LENGTH, ROOM_LENGTH, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(ROOM_LENGTH, ROOM_LENGTH, ROOM_LENGTH);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, ROOM_LENGTH, ROOM_LENGTH);
		glEnd();

		/// Bottom
		glBindTexture(GL_TEXTURE_2D, tex1_ID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(ROOM_LENGTH, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(ROOM_LENGTH, 0.0f, ROOM_LENGTH);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, ROOM_LENGTH);
		glEnd();

		/// Left
		glBindTexture(GL_TEXTURE_2D, tex1_ID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, ROOM_LENGTH);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, ROOM_LENGTH, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, ROOM_LENGTH, ROOM_LENGTH);
		glEnd();

		/// Right
		glBindTexture(GL_TEXTURE_2D, tex1_ID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(ROOM_LENGTH, 0.0f, ROOM_LENGTH);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(ROOM_LENGTH, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(ROOM_LENGTH, ROOM_LENGTH, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(ROOM_LENGTH, ROOM_LENGTH, ROOM_LENGTH);
		glEnd();
	}
	glPopMatrix();
}

//===========================================================================//

void Room::Update()
{
	// Empty
}