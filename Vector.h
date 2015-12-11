
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "stdafx.h"

/*
   Three-dimensional vector class
 */

class Vector3
{
public:
	/// Constructor
	Vector3()  { x = 0.0; y = 0.0; z = 0.0; }
	Vector3(float xx, float yy, float zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}
	Vector3(const Vector3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	/// Member functions
	inline float length();                       // Compute the length of the vector
	Vector3 normalize();                         // Normalize itself
	float dotProduct(const Vector3& v);          // Compute dotproduct
	Vector3 crossProduct(const Vector3& v);      // Compute crossProduct

	/// Overloaded operators
	Vector3 operator + (const Vector3& v);
	Vector3 operator - (const Vector3& v);
	Vector3 operator * (float scale);
	Vector3 operator / (float scale);
	Vector3 operator - ();

public:
	float x, y, z;

};

/*
   Two-dimensional point class
 */

struct Point2
{
	int x, y;

	Point2() :x(0), y(0) {}
	Point2(int _x, int _y) :x(_x), y(_y) {}
	const Point2 &operator=(const Point2 &p)
	{
		x = p.x;
		y = p.y;
		return *this;
	}
};

#endif // _VECTOR_H_