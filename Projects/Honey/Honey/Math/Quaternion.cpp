#include "Quaternion.h"

#include <Honey/Math/MathFunctions.h>

using namespace Honey::Math;

const Quaternion Quaternion::Identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

Quaternion::Quaternion() : x(0), y(0), z(0), w(1) {}

Quaternion::Quaternion(float value) : x(value), y(value), z(value), w(value) { }

Quaternion::Quaternion(const Vector3& xyz, float w) 
	: x(xyz.X), y(xyz.Y), z(xyz.Z), w(w) {}

Quaternion::Quaternion(const Vector4& vector)
	: x(vector.X), y(vector.Y), z(vector.Z), w(vector.W) { }

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Quaternion::Quaternion(const Quaternion& quaternion) 
	: x(quaternion.x), y(quaternion.y), z(quaternion.z), w(quaternion.w) { }

Quaternion& Quaternion::SetXYZ(const Vector3& vector)
{
	SetXYZ(vector.X, vector.Y, vector.Z);
	return *this;
}

Quaternion& Quaternion::SetXYZ(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

Quaternion& Quaternion::Set(const Vector4& vector)
{
	Set(vector.X, vector.Y, vector.Z, vector.W);
	return *this;
}

Quaternion& Quaternion::Set(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	return *this;
}

Quaternion& Quaternion::Normalize()
{
	*this /= GetMagnitude();
	return *this;
}

Quaternion Quaternion::Conjugate() const
{
	return Quaternion(-x, -y, -z, w);
}

Vector3 Quaternion::GetAxis() const
{
	float X = 1.0f - w * w;
	if (X < Mathf::Epsilon) // Divide by zero safety check
		return Vector3::Right;

	float x2 = X * X;
	return GetXYZ() / x2;
}

Vector3 Quaternion::ToEulerAngles() const
{
	return Vector3(
		atan2(2 * x * w - 2 * y * z, 1 - 2 * x * x - 2 * z * z),
		atan2(2 * y * w - 2 * x * z, 1 - 2 * y * y - 2 * z * z),
		asin(2 * x * y + 2 * z * w));
	/*return Vector3(
		Mathf::Atan2(2 * X * W - 2 * Y * Z, 1 - 2 * X * X - 2 * Z * Z),
		Mathf::Atan2(2 * Y * W - 2 * X * Z, 1 - 2 * Y * Y - 2 * Z * Z),
		Mathf::Asin(2 * X * Y + 2 * Z * W)
	);*/
}

float Quaternion::GetMagnitude() const
{
	return Mathf::Sqrt(GetSquaredMagnitude());
}

float Quaternion::GetSquaredMagnitude() const
{
	return x * x + y * y + z * z + w * w;
}

Quaternion Quaternion::Normalized() const
{
	return *this / GetMagnitude();
}

Quaternion Quaternion::operator -() const
{
	return Quaternion(-x, -y, -z, -w);
}

Quaternion Quaternion::operator +(const Quaternion& quaternion) const
{
	return Quaternion(x + quaternion.x, y + quaternion.y, z + quaternion.z, w + quaternion.w);
}

Quaternion Quaternion::operator -(const Quaternion& quaternion) const
{
	return Quaternion(x - quaternion.x, y - quaternion.y, z - quaternion.z, w - quaternion.w);
}

Quaternion Quaternion::operator *(const Quaternion& quaternion) const
{
	float x = this->w * quaternion.x + this->x * quaternion.w + this->y * quaternion.z - this->z * quaternion.y;
	float y = this->w * quaternion.y + this->y * quaternion.w + this->z * quaternion.x - this->x * quaternion.z;
	float z = this->w * quaternion.z + this->z * quaternion.w + this->x * quaternion.y - this->y * quaternion.x;
	float w = this->w * quaternion.w - this->x * quaternion.x - this->y * quaternion.y - this->z * quaternion.z;

	return Quaternion(x, y, z, w).Normalize();
}

Quaternion Quaternion::operator *(float scalar) const
{
	return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
}

Quaternion Quaternion::operator /(float scalar) const
{
	return Quaternion(x / scalar, y / scalar, z / scalar, w / scalar);
}

bool Quaternion::operator ==(const Quaternion& other) const
{
	return
		Mathf::ApproximatelyEquals(x, other.x) &&
		Mathf::ApproximatelyEquals(y, other.y) &&
		Mathf::ApproximatelyEquals(z, other.z) &&
		Mathf::ApproximatelyEquals(w, other.w);
}

bool Quaternion::operator !=(const Quaternion& other) const
{
	return !(*this == other);
}

float Quaternion::operator [](int index)
{
	if (index < 0) return components[0];
	return Quaternion::operator[]((unsigned int)index);
}

float Quaternion::operator [](int index) const
{
	if (index < 0) return components[0];
	return Quaternion::operator[]((unsigned int)index);
}

float Quaternion::operator [](unsigned int index)
{
	if (index > 3) return components[3];
	return components[index];
}

float Quaternion::operator [](unsigned int index) const
{
	if (index > 3) return components[3];
	return components[index];
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

	temp.X = quaternion.w * vector.X + quaternion.y * vector.Z - quaternion.z * vector.Y;
	temp.Y = quaternion.w * vector.Y + quaternion.z * vector.Z - quaternion.x * vector.Z;
	temp.Z = quaternion.w * vector.Z + quaternion.x * vector.Y - quaternion.y * vector.X;
	temp.W = quaternion.x * vector.X + quaternion.y * vector.Y + quaternion.z * vector.Z;

	float x = temp.W * quaternion.x + temp.X * quaternion.w - temp.Y * quaternion.z + temp.Z * quaternion.y;
	float y = temp.W * quaternion.y + temp.Y * quaternion.w - temp.Z * quaternion.x + temp.X * quaternion.z;
	float z = temp.W * quaternion.z + temp.Z * quaternion.w - temp.X * quaternion.y + temp.Y * quaternion.x;

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
	float dot = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return dot;
}
