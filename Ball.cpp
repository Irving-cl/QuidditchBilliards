
#include "Ball.h"

//===========================================================================//

Ball::Ball()
{
	/// New a quadric object
	m_Sphere = gluNewQuadric();

	/// Initialize the object
	gluQuadricOrientation(m_Sphere, GLU_OUTSIDE);
	gluQuadricNormals(m_Sphere, GLU_SMOOTH);
	gluQuadricTexture(m_Sphere, GL_TRUE);
}

//===========================================================================//

Ball::~Ball()
{
	/// Delete the object
	gluDeleteQuadric(m_Sphere);
	m_Sphere = NULL;
}

//===========================================================================//

bool Ball::CheckHit(Ball * otherBall)
{
	Vector3 v = otherBall->m_Position - m_Position;    // Vector of positions
	float distance = v.length();
	if ((distance < 2 * R) && IsGettingCloser(otherBall))
	{   /// Swap speed 
		Vector3 temp = m_Speed;
		m_Speed = otherBall->m_Speed;
		otherBall->m_Speed = temp;
		return true;
	}
	return false;
}

//===========================================================================//

Vector3 Ball::GetSpeed()
{
	return m_Speed;
}

//===========================================================================//

void Ball::SetSpeed(Vector3 speed)
{
	m_Speed = speed;
}

//===========================================================================//

void Ball::SetIniPosition(Vector3 position)
{
	m_IniPosition = m_Position = position;
}

//===========================================================================//

bool Ball::IsStatic()
{
	return m_Speed.length() <= 0.0f;
}

//===========================================================================//

void Ball::Move()
{
	m_Position = m_Position + m_Speed;
	CheckBoundry();
}

//===========================================================================//

void Ball::CheckBoundry()
{
	if (m_Position.z - R < WALL_FRONT_BOUND)
	{
		if (m_Speed.z < 0.0f)
			m_Speed.z = -m_Speed.z;
	}
	if (m_Position.z + R > WALL_BACK_BOUND)
	{
		if (m_Speed.z > 0.0f)
			m_Speed.z = -m_Speed.z;
	}
	if (m_Position.x - R < WALL_LEFT_BOUND)
	{
		if (m_Speed.x < 0.0f)
			m_Speed.x = -m_Speed.x;
	}
	if (m_Position.x + R > WALL_RIGHT_BOUND)
	{
		if (m_Speed.x > 0.0f)
			m_Speed.x = -m_Speed.x;
	}
}

//===========================================================================//

void Ball::Roll()
{
	Vector3 s = m_Position - m_IniPosition;
	glRotatef(s.length() / R * 2, s.z, 0.0f, -s.x);
}

//===========================================================================//

void Ball::SlowDown()
{
	if (m_Speed.length() > 0.0003f)
	{
		m_Speed.x *= 0.995f;
		m_Speed.z *= 0.995f;
	}
	else
	{
		m_Speed.x = 0.0f;
		m_Speed.z = 0.0f;
	}
}

//===========================================================================//

bool Ball::IsGettingCloser(Ball * otherBall)
{
	Vector3 v1 = otherBall->m_Position - m_Position;    // Vector of position
	Vector3 v2 = m_Speed - otherBall->m_Speed;          // Vector of speed
	return (v1.x * v2.x + v1.z * v2.z) > 0;
}