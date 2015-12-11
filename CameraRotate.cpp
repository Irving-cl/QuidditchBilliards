
#include "CameraRotate.h"

//===========================================================================//

const float DISTANCE = 25.0f;
const float PI = 3.14159265f;
const float PI2 = 6.283f;
const float OMEGA = 0.008f;

//===========================================================================//

CameraRotate::CameraRotate()
	:distance(DISTANCE),
	Alpha(PI * 8 / 7), Beta(PI / 8),
	x(0.0f), y(0.0f), z(0.0f)
{
	/* empty */
}

//===========================================================================//

CameraRotate:: ~CameraRotate()
{
	/* empty */
}

//===========================================================================//

void CameraRotate::LRotate()
{
	if (Alpha < PI2)
		Alpha += OMEGA;
	else
		Alpha = 0.0f;
}

//===========================================================================//

void CameraRotate::RRotate()
{
	if (Alpha < 0)
		Alpha = PI2;
	else
		Alpha -= OMEGA;
}

//===========================================================================//

void CameraRotate::URotate()
{
	if (Beta < PI2)
		Beta += OMEGA;
	else
		Beta = 0.0f;
}

//===========================================================================//

void CameraRotate::DRotate()
{
	if (Beta < 0)
		Beta = PI2;
	else
		Beta -= OMEGA;
}

//===========================================================================//

void CameraRotate::UpdatePosition()
{
	/** 更新观测点 */
	x = distance * cos(Beta) * sin(Alpha);
	y = distance * sin(Beta);
	z = distance * cos(Beta) * cos(Alpha);
}

//===========================================================================//

void CameraRotate::SetLook()
{
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}