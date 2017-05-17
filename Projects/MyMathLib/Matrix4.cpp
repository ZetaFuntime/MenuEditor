#include "Matrix4.h"

#include <memory.h>
#include <math.h>

#if 1

Matrix4::~Matrix4()
{
}

Matrix4::Matrix4()
{
	set(1.f,0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}

void  Matrix4::set(float *a_ptr)
{
}

void  Matrix4::set(float a_m1, float a_m2, float a_m3, float a_m4, 
	float a_m5, float a_m6, float a_m7, float a_m8, 
	float a_m9, float a_m10, float a_m11, float a_m12,
	float a_m13, float a_m14, float a_m15, float a_m16)
{
	m1 = a_m1; m2 = a_m2; m3 = a_m3; m4 = a_m4; 
	m5 = a_m5; m6 = a_m6; m7 = a_m7; m8 = a_m8; 
	m9 = a_m9; m10 = a_m10; m11 = a_m11; m12 = a_m12;
	m13 = a_m13; m14 = a_m14; m15 = a_m15; m16 = a_m16;
}


Matrix4::Matrix4(float *a_ptr) :
	m1(a_ptr[0]), m2(a_ptr[1]), m3(a_ptr[2]),
	m4(a_ptr[3]), m5(a_ptr[4]), m6(a_ptr[5]),
	m7(a_ptr[6]), m8(a_ptr[7]), m9(a_ptr[8])
{
}

Matrix4::Matrix4(float a_m1, float a_m2, float a_m3, float a_m4, float a_m5, float a_m6, float a_m7, float a_m8, float a_m9, float a_m10, float a_m11, float a_m12,
	float a_m13, float a_m14, float a_m15, float a_m16) :
	m1 ( a_m1), m2 (a_m2),  m3 (a_m3),  m4 (a_m4), 
	m5 ( a_m5), m6 (a_m6),  m7 (a_m7),  m8 (a_m8), 
	m9 ( a_m9), m10(a_m10), m11(a_m11), m12(a_m12),
	m13(a_m13), m14(a_m14), m15(a_m15), m16(a_m16)
{
}

Vector4 Matrix4::operator * (const Vector4 &a_vec) const
{
	return Vector4(
		v[0].x * a_vec.x + v[1].x * a_vec.y + v[2].x * a_vec.z + v[3].x * a_vec.w,
		v[0].y * a_vec.x + v[1].y * a_vec.y + v[2].y * a_vec.z + v[3].y * a_vec.w,
		v[0].z * a_vec.x + v[1].z * a_vec.y + v[2].z * a_vec.z + v[3].z * a_vec.w,
		v[0].w * a_vec.x + v[1].w * a_vec.y + v[2].w * a_vec.z + v[3].w * a_vec.w);
}

Matrix4  Matrix4::operator *(const Matrix4 &a_rhs) const
{
	return Matrix4(
		m1 * a_rhs.m1 + m5 * a_rhs.m2 + m9 * a_rhs.m3 + m13 * a_rhs.m4,
		m2 * a_rhs.m1 + m6 * a_rhs.m2 + m10 * a_rhs.m3 + m14 * a_rhs.m4,
		m3 * a_rhs.m1 + m7 * a_rhs.m2 + m11 * a_rhs.m3 + m15* a_rhs.m4,
		m4 * a_rhs.m1 + m8 * a_rhs.m2 + m12 * a_rhs.m3 + m16* a_rhs.m4,

		m1 * a_rhs.m5 + m5 * a_rhs.m6 + m9 * a_rhs.m7 + m13 * a_rhs.m8,
		m2 * a_rhs.m5 + m6 * a_rhs.m6 + m10 * a_rhs.m7 + m14 * a_rhs.m8,
		m3 * a_rhs.m5 + m7 * a_rhs.m6 + m11 * a_rhs.m7 + m15 * a_rhs.m8,
		m4 * a_rhs.m5 + m8 * a_rhs.m6 + m12 * a_rhs.m7 + m16 * a_rhs.m8,
		
		m1 * a_rhs.m9 + m5 * a_rhs.m10 + m9 * a_rhs.m11 + m13 * a_rhs.m12,
		m2 * a_rhs.m9 + m6 * a_rhs.m10 + m10 * a_rhs.m11 + m14 * a_rhs.m12,
		m3 * a_rhs.m9 + m7 * a_rhs.m10 + m11 * a_rhs.m11 + m15 * a_rhs.m12,
		m4 * a_rhs.m9 + m8 * a_rhs.m10 + m12 * a_rhs.m11 + m16 * a_rhs.m12,

		m1 * a_rhs.m13 + m5 * a_rhs.m14 + m9 * a_rhs.m15 + m13 * a_rhs.m16,
		m2 * a_rhs.m13 + m6 * a_rhs.m14 + m10 * a_rhs.m15 + m14 * a_rhs.m16,
		m3 * a_rhs.m13 + m7 * a_rhs.m14 + m11 * a_rhs.m15 + m15 * a_rhs.m16,			 
		m4 * a_rhs.m13 + m8 * a_rhs.m14 + m12 * a_rhs.m15 + m16 * a_rhs.m16
	);
}

void Matrix4::setRotateX(float a_rot)
{
	m6 = cosf(a_rot);
	m7 = sinf(a_rot);
	m10 = -sinf(a_rot);
	m11 = cosf(a_rot);
}

void Matrix4::setRotateY(float a_rot)
{
	m1 = cosf(a_rot);
	m3 = -sinf(a_rot);
	m9 = sinf(a_rot);
	m11 = cosf(a_rot);
}

void Matrix4::setRotateZ(float a_rot)
{
	m1 = cosf(a_rot);
	m2 = sinf(a_rot);
	m5 = -sinf(a_rot);
	m6 = cosf(a_rot);
}

#endif