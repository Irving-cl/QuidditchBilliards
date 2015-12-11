
#include "Table.h"

//===========================================================================//

Table::Table()
{
	m_TexturePool = NULL;
}

//===========================================================================//

Table::~Table()
{
	// Empty
}

//===========================================================================//

void Table::Draw()
{
	/// Draw base
	DrawCube(m_TexturePool[0], m_TexturePool[1],
		Vector3(TABLE_LENGTH, TABLE_BASE_THICKNESS, TABLE_WIDTH),
		Vector3(-TABLE_LENGTH / 2, 0, -TABLE_WIDTH / 2));
	
	/*- Draw walls -*/
	/// Left
	DrawCube(m_TexturePool[0], m_TexturePool[0],
		Vector3(R, TABLE_WALL_HEIGHT, TABLE_LRWALL_LENGTH),
		Vector3(-TABLE_LENGTH / 2, TABLE_BASE_THICKNESS, -TABLE_LRWALL_LENGTH / 2));
	/// Right
	DrawCube(m_TexturePool[0], m_TexturePool[0],
		Vector3(R, TABLE_WALL_HEIGHT, TABLE_LRWALL_LENGTH),
		Vector3(TABLE_LENGTH / 2 - R, TABLE_BASE_THICKNESS, -TABLE_LRWALL_LENGTH / 2));
	/// Front
	DrawCube(m_TexturePool[0], m_TexturePool[0],
		Vector3(TABLE_FBWALL_LENGTH, TABLE_WALL_HEIGHT, R),
		Vector3(-(TABLE_LENGTH / 2 - 3 * R), TABLE_BASE_THICKNESS, -TABLE_WIDTH / 2));
	DrawCube(m_TexturePool[0], m_TexturePool[0],
		Vector3(TABLE_FBWALL_LENGTH, TABLE_WALL_HEIGHT, R),
		Vector3(SQRT2 * R, TABLE_BASE_THICKNESS, -TABLE_WIDTH / 2));
	// Back
	DrawCube(m_TexturePool[0], m_TexturePool[0],
		Vector3(TABLE_FBWALL_LENGTH, TABLE_WALL_HEIGHT, R),
		Vector3(-(TABLE_LENGTH / 2 - 3 * R), TABLE_BASE_THICKNESS, TABLE_WIDTH / 2 - R));
	DrawCube(m_TexturePool[0], m_TexturePool[0],
		Vector3(TABLE_FBWALL_LENGTH, TABLE_WALL_HEIGHT, R),
		Vector3(SQRT2 * R, TABLE_BASE_THICKNESS, TABLE_WIDTH / 2 - R));
	/*- End -*/
}

//===========================================================================//

void Table::Update()
{
	// Empty
}

//===========================================================================//

void Table::DrawCube(unsigned int tex1_ID, unsigned int tex2_ID, Vector3 LHW, Vector3 position)
{
	glPushMatrix();
	{
		glTranslatef(position.x, position.y, position.z);

		/// Front
		glBindTexture(GL_TEXTURE_2D, tex1_ID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(LHW.x, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(LHW.x, LHW.y, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, LHW.y, 0.0f);
		glEnd();

		/// Back
		glBindTexture(GL_TEXTURE_2D, tex1_ID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(LHW.x, 0.0f, LHW.z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, LHW.z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, LHW.y, LHW.z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(LHW.x, LHW.y, LHW.z);
		glEnd();

		/// Top
		glBindTexture(GL_TEXTURE_2D, tex2_ID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, LHW.y, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(LHW.x, LHW.y, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(LHW.x, LHW.y, LHW.z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, LHW.y, LHW.z);
		glEnd();

		/// Bottom
		glBindTexture(GL_TEXTURE_2D, tex1_ID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(LHW.x, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(LHW.x, 0.0f, LHW.z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, LHW.z);
		glEnd();

		/// Left
		glBindTexture(GL_TEXTURE_2D, tex1_ID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, LHW.z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, LHW.y, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, LHW.y, LHW.z);
		glEnd();

		/// Right
		glBindTexture(GL_TEXTURE_2D, tex1_ID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(LHW.x, 0.0f, LHW.z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(LHW.x, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(LHW.x, LHW.y, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(LHW.x, LHW.y, LHW.z);
		glEnd();
	}
	glPopMatrix();
}