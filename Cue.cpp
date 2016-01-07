
#include "Cue.h"

//===========================================================================//

Cue::Cue(Ball * mainBall)
{
	m_Cylinder = new Cylinder();    // New a cylinder object
	m_DirectionAngle = 30.0f;       // Initialize the angle to 30 degree
	m_MainBall = mainBall;          // The cue will always point to the main ball
	m_StippleMove = 0.0f;           // Initialize movement to 0
	m_CueMove = 0.0f;               // Initialize movement to 0
	m_State = READY;                // The cue is ready to hit
	m_Input = NULL;                 // Set the pointer to null
}

//===========================================================================//

Cue::~Cue()
{
	if (m_Cylinder)
	{
		delete m_Cylinder;
		m_Cylinder = NULL;
	}
	m_MainBall = NULL;
	m_Input = NULL;
}

//===========================================================================//

void Cue::SetInput(CInputSystem * input)
{
	m_Input = input;
}

//===========================================================================//

void Cue::Draw()
{
	//if (!m_MainBall->IsStatic())    // Only draw cue when the main ball is static
	//	return;

	glPushMatrix();
	{
		Vector3 mainBallPos = m_MainBall->GetPosition();
		glTranslatef(mainBallPos.x, mainBallPos.y, mainBallPos.z);
		glPushMatrix();
		{
			glRotatef(m_DirectionAngle, 0.0f, 1.0f, 0.0f);
			glRotatef(CUE_ANGLE, 1.0f, 0.0f, 0.0f);

			/// Draw stipple
			glPushMatrix();
			{
				glLineStipple(3, STIPPLE_PATTERN);
				glTranslatef(0.0f, 0.0f, -m_StippleMove);
				glBindTexture(GL_TEXTURE_2D, m_TexturePool[5]);
				glBegin(GL_LINES);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, 0.0f, CUE_BALL_DISTANCE);
				glEnd();
			}
			glPopMatrix();

			/// Draw cue
			glTranslatef(0.0f, 0.0f, CUE_BALL_DISTANCE - m_CueMove);
			glBindTexture(GL_TEXTURE_2D, m_TexturePool[6]);                              // Bind texture
			gluCylinder(m_Cylinder->GetQuadratic(), 0.06f, 0.18f, CUE_LENGTH, 32, 32);   // Draw a cylinder as body
			m_Cylinder->DrawCircleArea(0.0, 0.0, CUE_LENGTH, 0.18f, 32);                 // Draw top
			m_Cylinder->DrawCircleArea(0.0, 0.0, 0.0, 0.06f, 32);                        // Draw base
		}
		glPopMatrix();
	}
	glPopMatrix();
}

//===========================================================================//

void Cue::Update()
{
	if (!m_MainBall->IsStatic())    // Only update cue when the main ball is static
		return;

	/// Update stipple
	m_StippleMove += STIPPLE_MOVEMENT;
	if (m_StippleMove > STIPPLE_MAX_MOVEMENT)
		m_StippleMove = 0.0f;
	
	/// Adjust the direction
	if (m_Input->GetKeyboard()->KeyDown(DIK_Q))
	{
		m_DirectionAngle -= CUE_ROTATE_SPEED;
		if (m_DirectionAngle < 0.0f)
			m_DirectionAngle = 360.0f;
	}
	if (m_Input->GetKeyboard()->KeyDown(DIK_E))
	{
		m_DirectionAngle += CUE_ROTATE_SPEED;
		if (m_DirectionAngle < 0.0f)
			m_DirectionAngle = 360.0f;
	}

	/// State
	if (m_State == READY)
	{
		if (m_Input->GetKeyboard()->KeyDown(DIK_SPACE))
		{
			m_State = MOVE;
		}
	}
	else if (m_State == MOVE)
	{
		if (m_CueMove < CUE_BALL_DISTANCE)
			m_CueMove += CUE_HIT_SPEED;
		else
		{
			m_State = HIT;
			m_CueMove = 0.0f;
		}
	}
	else
	{
		HitBall();
		m_State = READY;
	}
}

//===========================================================================//

void Cue::HitBall()
{
	float direction = m_DirectionAngle * PI / 180.0f;
	float velocity = 0.3f;
	Vector3 speed(-sin(direction) * velocity, 0.0f, -cos(direction) * velocity);
	m_MainBall->SetSpeed(speed);
}