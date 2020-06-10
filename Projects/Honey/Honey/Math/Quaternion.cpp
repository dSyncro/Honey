#include "Quaternion.h"

#include <Honey/Math/MathFunctions.h>

using namespace Honey::Math;

const Quaternion Quaternion::Identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

Quaternion::Quaternion() : X(0), Y(0), Z(0), W(1) {}

Quaternion::Quaternion(float value) : X(value), Y(value), Z(value), W(value) { }

Quaternion::Quaternion(const Vector3& xyz, float w) 
	: X(xyz.X), Y(xyz.Y), Z(xyz.Z), W(w) {}

Quaternion::Quaternion(const Vector4& vector)
	: X(vector.X), Y(vector.Y), Z(vector.Z), W(vector.W) { }

Quaternion::Quaternion(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

Quaternion::Quaternion(const Quaternion& quaternion) 
	: X(quaternion.X), Y(quaternion.Y), Z(quaternion.Z), W(quaternion.W) { }

Quaternion& Quaternion::SetXYZ(const Vector3& vector)
{
	SetXYZ(vector.X, vector.Y, vector.Z);
	return *this;
}

Quaternion& Quaternion::SetXYZ(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
	return *this;
}

Quaternion& Quaternion::Set(const Vector4& vector)
{
	Set(vector.X, vector.Y, vector.Z, vector.W);
	return *this;
}

Quaternion& Quaternion::Set(float x, float y, float z, float w)
{
	X = x;
	Y = y;
	Z = z;
	W = w;
	return *this;
}

Quaternion& Quaternion::Normalize()
{
	*this /= GetMagnitude();
	return *this;
}

Quaternion Quaternion::Conjugate() const
{
	return Quaternion(-X, -Y, -Z, W);
}

Vector3 Quaternion::GetAxis() const
{
	float X = 1.0f - W * W;
	if (X < Mathf::Epsilon) // Divide by zero safety check
		return Vector3::Right;

	float x2 = X * X;
	return GetXYZ() / x2;
}

Vector3 Quaternion::ToEulerAngles() const
{
	return Vector3(
		Mathf::Atan2(2 * X * W - 2 * Y * Z, 1 - 2 * X * X - 2 * Z * Z),
		Mathf::Atan2(2 * Y * W - 2 * X * Z, 1 - 2 * Y * Y - 2 * Z * Z),
		Mathf::Sin(2 * X * Y + 2 * Z * W));
}

float Quaternion::GetMagnitude() const
{
	return Mathf::Sqrt(GetSquaredMagnitude());
}

float Quaternion::GetSquaredMagnitude() const
{
	return X * X + Y * Y + Z * Z + W * W;
}

Quaternion Quaternion::Normalized() const
{
	return *this / GetMagnitude();
}

Quaternion Quaternion::operator -() const
{
	return Quaternion(-X, -Y, -Z, -W);
}

Quaternion Quaternion::operator +(const Quaternion& quaternion) const
{
	return Quaternion(X + quaternion.X, Y + quaternion.Y, Z + quaternion.Z, W + quaternion.W);
}

Quaternion Quaternion::operator -(const Quaternion& quaternion) const
{
	return Quaternion(X - quaternion.X, Y - quaternion.Y, Z - quaternion.Z, W - quaternion.W);
}

Quaternion Quaternion::operator *(const Quaternion& quaternion) const
{
	float x = W * quaternion.X + X * quaternion.W + Y * quaternion.Z - Z * quaternion.Y;
	float y = W * quaternion.Y + Y * quaternion.W + Z * quaternion.X - X * quaternion.Z;
	float z = W * quaternion.Z + Z * quaternion.W + X * quaternion.Y - Y * quaternion.X;
	float w = W * quaternion.W - X * quaternion.X - Y * quaternion.Y - Z * quaternion.Z;

	return Quaternion(x, y, z, w).Normalize();
}

Quaternion Quaternion::operator *(float scalar) const
{
	return Quaternion(X * scalar, Y * scalar, Z * scalar, W * scalar);
}

Quaternion Quaternion::operator /(float scalar) const
{
	return Quaternion(X / scalar, Y / scalar, Z / scalar, W / scalar);
}

bool Quaternion::operator ==(const Quaternion& other) const
{
	return
		Mathf::ApproximatelyEquals(X, other.X) &&
		Mathf::ApproximatelyEquals(Y, other.Y) &&
		Mathf::ApproximatelyEquals(Z, other.Z) &&
		Mathf::ApproximatelyEquals(W, other.W);
}

bool Quaternion::operator !=(const Quaternion& other) const
{
	return !(*this == other);
}

float Quaternion::operator [](int index)
{
	if (index < 0) return Components[0];
	return Quaternion::operator[]((unsigned int)index);
}

float Quaternion::operator [](int index) const
{
	if (index < 0) return Components[0];
	return Quaternion::operator[]((unsigned int)index);
}

float Quaternion::operator [](unsigned int index)
{
	if (index > 3) return Components[3];
	return Components[index];
}

float Quaternion::operator [](unsigned int index) const
{
	if (index > 3) return Components[3];
	return Components[index];
}

Quaternion Quaternion::FromEulerAngles(const Vector3& angles)
{
	Quaternion pitch(Vector3(1.0, 0.0, 0.0), angles.X);
	Quaternion yaw(Vector3(0.0, 1.0, 0.0), angles.Y);
	Quaternion roll(Vector3(0.0, 0.0, 1.0), angles.Z);
	return pitch * yaw * roll;
}

Quaternion Quaternion::FromToRotation(const Vector3& a, const Vector3& b)
{
	float onePlusDot = 1.0f + Vector3::Dot(a, b);
	float cosHalfAngleX2 = Mathf::Sqrt(2.0f * onePlusDot);
	float recipCosHalfAngleX2 = 1.0f / cosHalfAngleX2;

	return Quaternion(Vector3::Cross(a, b) * recipCosHalfAngleX2, cosHalfAngleX2 * 0.5f);
}

Quaternion Quaternion::UnitVectorRotation(float radians, const Vector3& unitVec)
{
	float angle = radians * 0.5f;
	return Quaternion(unitVec * Mathf::Sin(angle), Mathf::Cos(angle));
}

Vector3 Quaternion::Rotate(const Quaternion& quaternion, const Vector3& vector)
{
	Vector4 temp;

	temp.X = quaternion.W * vector.X + quaternion.Y * vector.Z - quaternion.Z * vector.Y;
	temp.Y = quaternion.W * vector.Y + quaternion.Z * vector.Z - quaternion.X * vector.Z;
	temp.Z = quaternion.W * vector.Z + quaternion.X * vector.Y - quaternion.Y * vector.X;
	temp.W = quaternion.X * vector.X + quaternion.Y * vector.Y + quaternion.Z * vector.Z;

	float x = temp.W * quaternion.X + temp.X * quaternion.W - temp.Y * quaternion.Z + temp.Z * quaternion.Y;
	float y = temp.W * quaternion.Y + temp.Y * quaternion.W - temp.Z * quaternion.X + temp.X * quaternion.Z;
	float z = temp.W * quaternion.Z + temp.Z * quaternion.W - temp.X * quaternion.Y + temp.Y * quaternion.X;

	return Vector3(x, y, z);
}

Quaternion Quaternion::RotationX(float radians)
{
	float angle = radians * 0.5f;
	return Quaternion(Mathf::Sin(angle), 0.0f, 0.0f, Mathf::Cos(angle));
}

Quaternion Quaternion::RotationY(float radians)
{
	float angle = radians * 0.5f;
	return Quaternion(0.0f, Mathf::Sin(angle), 0.0f, Mathf::Cos(angle));
}

Quaternion Quaternion::RotationZ(float radians)
{
	float angle = radians * 0.5f;
	return Quaternion(0.0f, 0.0f, Mathf::Sin(angle), Mathf::Cos(angle));
}

float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
{
	float dot = a.X * b.X + a.Y * b.Y + a.Z * b.Z + a.W * b.W;
	return dot;
}
