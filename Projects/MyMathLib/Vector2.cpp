#include "Vector2.h"
#include <math.h> 


Vector2::Vector2() : x(0), y(0)
{
}

Vector2::Vector2(float a_x, float a_y) : x(a_x), y(a_y)
{
}

Vector2::Vector2(const Vector2 & a_other) : x(a_other.x), y(a_other.y)
{
}

Vector2 Vector2::operator + (const Vector2& a_rhs) const
{
	return Vector2(x + a_rhs.x, y + a_rhs.y);
}

Vector2 Vector2::operator - (const Vector2& a_rhs) const
{
	return Vector2(x - a_rhs.x, y - a_rhs.y);
}

Vector2& Vector2::operator += (const Vector2& a_other)
{
	x += a_other.x;
	y += a_other.y;
	return *this;
}

Vector2& Vector2::operator -= (const Vector2& a_other)
{
	x -= a_other.x;
	y -= a_other.y;
	return *this;
}

Vector2& Vector2::operator = (const Vector2& a_other)
{
	x = a_other.x;
	y = a_other.y;
	return *this;
}

Vector2 Vector2::operator * (float a_scalar) const
{
	return Vector2(x * a_scalar, y * a_scalar);
}

Vector2 operator * (float a_scalar, const Vector2& a_other)
{
	return Vector2(a_other.x * a_scalar, a_other.y * a_scalar);
}

Vector2& Vector2::operator *= (float a_scalar)
{
	x *= a_scalar;
	y *= a_scalar;
	return *this;
}

float Vector2::magnitude()
{
	float f = cosf(30);
	return sqrtf(x*x + y*y);
}

void Vector2::normalise()
{
	float mag = magnitude();
	if (mag == 0) return;
	x /= mag;
	y /= mag;
}

Vector2 Vector2::normal()
{
	float mag = magnitude();
	if (mag = 0) return Vector2(x,y);

	return Vector2(x / mag, y / mag);
}

float Vector2::dot(const Vector2& a_rhs)
{
	return x * a_rhs.x + y * a_rhs.y;
}

