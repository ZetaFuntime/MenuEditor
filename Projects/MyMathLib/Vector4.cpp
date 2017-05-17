#include "Vector4.h"
#include <math.h>



Vector4::Vector4() : x(0), y(0), z(0), w(0)
{
}

Vector4::Vector4(float a_x, float a_y, float a_z, float a_w) : x(a_x), y(a_y), z(a_z), w(a_w)
{
}

void Vector4::get(float& a_x, float& a_y, float& a_z, float& a_w) const
{
	a_x = x;
	a_y = y;
	a_z = z;
	a_w = w;
	return;
}

void Vector4::set(const float& a_x, const float& a_y, const float& a_z, const float& a_w)
{
	x = a_x;
	y = a_y;
	z = a_z;
	w = a_w;
	return;
}

Vector4 Vector4::operator + (const Vector4 &a_rhs) const
{
	return Vector4(x + a_rhs.x, y + a_rhs.y, z + a_rhs.z, w + a_rhs.w);
}

Vector4 Vector4::operator - (const Vector4 &a_rhs) const
{
	return Vector4(x - a_rhs.x, y - a_rhs.y, z - a_rhs.z, w - a_rhs.w);
}

Vector4 Vector4::operator * (const Vector4 &a_rhs) const
{
	return Vector4(x * a_rhs.x, y * a_rhs.y, z * a_rhs.z, w * a_rhs.w);
}

Vector4 Vector4::operator / (const Vector4 &a_rhs) const
{
	return Vector4(x / a_rhs.x, y / a_rhs.y, z / a_rhs.z, w / a_rhs.w);
}

Vector4 Vector4::operator * (const float a_rhs) const
{
	return Vector4(x * a_rhs, y * a_rhs, z * a_rhs, w * a_rhs);
}

Vector4 Vector4::operator / (const float a_rhs) const
{
	return Vector4(x / a_rhs, y / a_rhs, z / a_rhs, w / a_rhs);
}

Vector4& Vector4::operator += (const Vector4 &a_rhs)
{
	x += a_rhs.x;
	y += a_rhs.y;
	z += a_rhs.z;
	w += a_rhs.w;
	return *this;
}

Vector4& Vector4::operator -= (const Vector4 &a_rhs)
{
	x -= a_rhs.x;
	y -= a_rhs.y;
	z -= a_rhs.z;
	w -= a_rhs.w;
	return *this;
}

Vector4& Vector4::operator *= (const Vector4 &a_rhs)
{
	x *= a_rhs.x;
	y *= a_rhs.y;
	z *= a_rhs.z;
	w *= a_rhs.w;
	return *this;
}

Vector4& Vector4::operator /= (const Vector4 &a_rhs)
{
	x /= a_rhs.x;
	y /= a_rhs.y;
	z /= a_rhs.z;
	w /= a_rhs.w;
	return *this;
}
Vector4& Vector4::operator *= (const float a_rhs)
{
	x *= a_rhs;
	y *= a_rhs;
	z *= a_rhs;
	w *= a_rhs;
	return *this;
}

Vector4& Vector4::operator /= (const float a_rhs)
{
	x /= a_rhs;
	y /= a_rhs;
	z /= a_rhs;
	w /= a_rhs;
	return *this;
}

bool Vector4::operator == (const Vector4 &a_rhs) const
{
	return (x == x, y == y, z == z, w == w);
}

bool Vector4::operator != (const Vector4 &a_rhs) const
{
	return (x != x, y != y, z != z, w != w);
}

Vector4 Vector4::operator -() const
{
	return Vector4(-x, -y, -z, -w);
}

float Vector4::magnitude() const
{
	return sqrtf(x*x + y*y + z*z + w*w);
}

float Vector4::dot(const Vector4 &a_rhs) const
{
	return x * a_rhs.x + y * a_rhs.y + z * a_rhs.z + w * a_rhs.w;
}

Vector4 Vector4::cross(const Vector4 &a_rhs) const
{
	return Vector4(y * a_rhs.z - z * a_rhs.y, z * a_rhs.x - x* a_rhs.z, x * a_rhs.y - y * a_rhs.x, w);
}

Vector4& Vector4::normalise()
{
	*this /= magnitude();
	return *this;
}
Vector4 Vector4::getNormalised()
{
	return (*this / magnitude());
}

Vector4 operator * (float a_scalar, const Vector4& a_other)
{
	return Vector4(a_other.x * a_scalar, a_other.y* a_scalar, a_other.z * a_scalar, a_other.w * a_scalar);
}
