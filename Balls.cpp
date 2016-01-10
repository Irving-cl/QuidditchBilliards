
#include "Balls.h"

/*- MainBall -*/
//===========================================================================//

void MainBall::Draw()
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, m_Position.z);    // Move the ball to its position
		Roll();                                                    // Roll
		glBindTexture(GL_TEXTURE_2D, m_TexturePool[5]);            // Bind texture
		gluSphere(m_Sphere, R, 50, 50);                            // Draw the ball
	}
	glPopMatrix();
}

//===========================================================================//

void MainBall::Update()
{
	Move();        // Move
	SlowDown();    // Slow down
}

//===========================================================================//
/*- End -*/

/*- GhostBall -*/
//===========================================================================//

void GhostBall::Draw()
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, m_Position.z);        // Move the ball to its position
		Roll();                                                        // Roll
		glBindTexture(GL_TEXTURE_2D, m_TexturePool[10]);               // Bind texture
		gluSphere(m_Sphere, R, 50, 50);                                // Draw the ball
	}
	glPopMatrix();
}

//===========================================================================//

void GhostBall::Update()
{
	Move();        // Move
	SlowDown();    // Slow down
}

//===========================================================================//
/*- End -*/

/*- WanderBall -*/
//===========================================================================//

void WanderBall::Draw()
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, m_Position.z);    // Move the ball to its position
		Roll();                                                    // Roll
		glBindTexture(GL_TEXTURE_2D, m_TexturePool[3]);            // Bind texture
		gluSphere(m_Sphere, R, 50, 50);                            // Draw the ball
	}
	glPopMatrix();
}

//===========================================================================//

void WanderBall::Update()
{
	Move();        // Move
	SlowDown();    // Slow down
}

//===========================================================================//
/*- End -*/

/*- GoldenBall -*/
//===========================================================================//

GoldenBall::GoldenBall()
{
	m_State = FLY;
	m_LastTime = clock();
}

//===========================================================================//

void GoldenBall::Draw()
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, m_Position.z);    // Move the ball to its position
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, m_TexturePool[4]);            // Bind texture
		gluSphere(m_Sphere, R, 50, 50);                            // Draw the ball
	}
	glPopMatrix();
}

//===========================================================================//

void GoldenBall::Update()
{
	clock_t currentTime = clock();
	switch (m_State)
	{
	    case FLY:
		    if ((currentTime - m_LastTime) / CLOCKS_PER_SEC > FLY_TIME)
		    {
			    m_State = DOWN;
			    m_LastTime = clock();
			    m_Speed = Vector3(0.0f, -UPDOWN_SPEED, 0.0f);
		    }
		    break;
	    case DOWN:
		    if ((currentTime - m_LastTime) / CLOCKS_PER_SEC > UPDOWN_TIME)
		    {
			    m_State = STOP;
			    m_LastTime = clock();
			    m_Speed = Vector3(0.0f, 0.0f, 0.0f);
			    m_Position = Vector3(m_Position.x, TABLE_BASE_THICKNESS + R, m_Position.z);
		    }
		    break;
	    case STOP:
	    {
		    if ((currentTime - m_LastTime) / CLOCKS_PER_SEC > STOP_TIME)
		    {
			    m_State = UP;
			    m_LastTime = clock();
			    m_Speed = Vector3(0.0f, UPDOWN_SPEED, 0.0f);
		    }
		    break;
	    }
	    case UP:
	    {
		    if ((currentTime - m_LastTime) / CLOCKS_PER_SEC > UPDOWN_TIME)
		    {
			    m_State = FLY;
			    m_LastTime = clock();
			    int direction = rand();
			    float speed = 0.2f;
			    m_Speed = Vector3(speed * cos(direction), 0.0f, speed * sin(direction));
			    m_Position = Vector3(m_Position.x, GOLDEN_BALL_HEIGHT, m_Position.z);
		    }
		    break;
	    }
	}

	Move();    // Move
}

//===========================================================================//
/*- End -*/
