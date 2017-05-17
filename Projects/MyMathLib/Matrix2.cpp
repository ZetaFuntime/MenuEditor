#include "Matrix2.h"
#include "Vector2.h"
#include <math.h>
#include <memory>



Matrix2::Matrix2() : m1(1), m2(0), m3(0), m4(1)
{
}

Matrix2::Matrix2(float *a_ptr) :
	m1(a_ptr[0]), m2(a_ptr[1]),
	m3(a_ptr[2]), m4(a_ptr[3])
{
}

Matrix2::Matrix2(float a_m1, float a_m2, float a_m3, float a_m4) :
	m1(a_m1), m2(a_m2),
	m3(a_m3), m4(a_m4)
{
}

Matrix2 Matrix2::createIdentity()
{
	return Matrix2(1.f, 0.f,
				   0.f, 1.f);
}

Matrix2 Matrix2::createTranslation(float a_x, float a_y)
{
	return Matrix2(1.f, 0.f,
				   a_x, a_y);
}

Matrix2 Matrix2::createTranslation(const Vector2 &a_vec)
{
	return Matrix2(1.f, 0.f,
				a_vec.x, a_vec.y);
}

Matrix2 Matrix2::createRotation(float a_rot)
{
	return Matrix2(cos(a_rot), sin(a_rot),
		          -sin(a_rot), cos(a_rot));
}

Matrix2 Matrix2::createScale(float a_xScale, float a_yScale)
{
	return Matrix2(a_xScale, 0.f,
		0.f, a_yScale);
}

Matrix2  Matrix2::operator * (const Matrix2 &a_rhs) const
{
	//return Matrix2((m1 * a_rhs.m1 + m3 * a_rhs.m2), (m2 * a_rhs.m1 + m4 * a_rhs.m2),
	//	(m1 * a_rhs.m3 + m3 * a_rhs.m3), (m2 * a_rhs.m3 + m4 * a_rhs.m4));
	return Matrix2( (m1 * a_rhs.m1 + m3 * a_rhs.m2), (m2 * a_rhs.m1 + m4 * a_rhs.m2),
					(m1 * a_rhs.m3 + m3 * a_rhs.m4), (m2 * a_rhs.m3 + m4 * a_rhs.m4));
}

Matrix2& Matrix2::operator *=(const Matrix2 &a_rhs)
{
	*this = *this * a_rhs;
	return *this;
}

Vector2 Matrix2::operator * (const Vector2 &a_vec) const
{
	return Vector2(m1*a_vec.x + m3*a_vec.y,
				   m2*a_vec.x + m4*a_vec.y);
}

// rebuild the matrix
void Matrix2::set(float a_m1, float a_m2, float a_m3, float a_m4)
{
	m1 = a_m1;
	m2 = a_m2;
	m3 = a_m3;
	m4 = a_m4;
}

// rebuild the matrix - expects pointer to array of 9 floats
void Matrix2::set(float *a_ptr)
{
	memcpy(m, &a_ptr, sizeof(float) * 4);
}

// only set the translation component of the matrix
void Matrix2::setTranslation(float a_x, float a_y)
{
	m3 = a_x;
	m4 = a_y;
}
// only set the translation component of the matrix
void Matrix2::setTranslation(const Vector2 &a_vec)
{
	m3 = a_vec.x;
	m4 = a_vec.y;
}

void Matrix2::setRotateZ(float a_rot)
{
	set(cosf(a_rot), sinf(a_rot),
		-sinf(a_rot), cosf(a_rot));
}

float Matrix2::getRotationZ()
{
	return atan2f(m2, m1);
}

// add x and y onto the translation component of the matrix
void Matrix2::translate(float a_x, float a_y)
{
	m3 += a_x;
	m4 += a_y;
}

// add x and y onto the translation component of the matrix
void Matrix2::translate(const Vector2 &a_vec)
{
	m3 += a_vec.x;
	m4 += a_vec.y;
}

// returns the translation component of the matrix
Vector2 Matrix2::getTranslation() const
{
	return Vector2(m3, m4);
}
