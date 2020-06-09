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

Quaternion& Quaternion::operator =(const Quaternion& quaternion)
{
	Set(quaternion.X, quaternion.Y, quaternion.Z, quaternion.W);
	return *this;
}

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

Quaternion Quaternion::FromEulerAngles(const Vector3& angles)
{
	Quaternion pitch(Vector3(1.0, 0.0, 0.0), angles.X);
	Quaternion yaw(Vector3(0.0, 1.0, 0.0), angles.Y);
	Quaternion roll(Vector3(0.0, 0.0, 1.0), angles.Z);
	return pitch * yaw * roll;
}


Vector3 Quaternion::GetXYZ() const
{
	return Vector3(X, Y, Z);
}

float Quaternion::operator [](int index) const
{
	if (index > 3) return Components[3];
	if (index < 0) return Components[0];
	return Components[index];
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

Quaternion Quaternion::operator +(const Quaternion& quaternion) const
{
	return Quaternion(X + quaternion.X, Y + quaternion.Y, Z + quaternion.Z, W + quaternion.W);
}

Quaternion Quaternion::operator -(const Quaternion& quaternion) const
{
	return Quaternion(X - quaternion.X, Y - quaternion.Y, Z - quaternion.Z, W - quaternion.W);
}

Quaternion Quaternion::operator*(float scalar) const
{
	return Quaternion(X * scalar, Y * scalar, Z * scalar, W * scalar);
}

Quaternion Quaternion::operator/(float scalar) const
{
	return Quaternion(X / scalar, Y / scalar, Z / scalar, W / scalar);
}

Quaternion Quaternion::operator -() const
{
	return Quaternion(-X, -Y, -Z, -W);
}

bool Quaternion::operator ==(const Quaternion& Quaternion) const
{
	return 
		Mathf::ApproximatelyEquals(X, Quaternion.X) && 
		Mathf::ApproximatelyEquals(Y, Quaternion.Y) &&
		Mathf::ApproximatelyEquals(Z, Quaternion.Z) &&
		Mathf::ApproximatelyEquals(W, Quaternion.W);
}

bool Quaternion::operator !=(const Quaternion& Quaternion) const
{
	return !(*this == Quaternion);
}

float Norm(const Quaternion& quaternion)
{
	float result;
	result = quaternion.X * quaternion.X;
	result += quaternion.Y * quaternion.Y;
	result += quaternion.Z * quaternion.Z;
	result += quaternion.W * quaternion.W;
	return result;
}

float Length(const Quaternion& quaternion)
{
	return sqrt(Norm(quaternion));
}

Quaternion Normalize(const Quaternion& quaternion)
{
	float lenSqr, lenInv;
	lenSqr = Norm(quaternion);
	lenInv = 1 / Honey::Mathf::Sqrt(lenSqr);
	return quaternion * lenInv;
}

Quaternion Quaternion::Rotation(const Vector3& unitVec0, const Vector3& unitVec1)
{
	float cosHalfAngleX2, recipCosHalfAngleX2;
	cosHalfAngleX2 = Mathf::Sqrt(2.0f * (1.0f + Vector3::Dot(unitVec0, unitVec1)));
	recipCosHalfAngleX2 = (1.0f / cosHalfAngleX2);
	return Quaternion(Vector3::Cross(unitVec0, unitVec1) * recipCosHalfAngleX2, (cosHalfAngleX2 * 0.5f));
}

Quaternion Quaternion::Rotation(float radians, const Vector3& unitVec)
{
	float angle = radians * 0.5f;
	return Quaternion((unitVec * sin(angle)), cos(angle));
}

Quaternion Quaternion::operator *(const Quaternion& quat) const
{
	float x = W * quat.X + X * quat.W + Y * quat.Z - Z * quat.Y;
	float y = W * quat.Y + Y * quat.W + Z * quat.X - X * quat.Z;
	float z = W * quat.Z + Z * quat.W + X * quat.Y - Y * quat.X;
	float w = W * quat.W - X * quat.X - Y * quat.Y - Z * quat.Z;

	return Normalize(Quaternion(x, y, z, w));
}

Vector3 Quaternion::Rotate(const Quaternion& quat, const Vector3& vec)
{
	Vector4 temp;

	temp.X = quat.W * vec.X + quat.Y * vec.Z - quat.Z * vec.Y;
	temp.Y = quat.W * vec.Y + quat.Z * vec.Z - quat.X * vec.Z;
	temp.Z = quat.W * vec.Z + quat.X * vec.Y - quat.Y * vec.X;
	temp.W = quat.X * vec.X + quat.Y * vec.Y + quat.Z * vec.Z;

	float x = temp.W * quat.X + temp.X * quat.W - temp.Y * quat.Z + temp.Z * quat.Y;
	float y = temp.W * quat.Y + temp.Y * quat.W - temp.Z * quat.X + temp.X * quat.Z;
	float z = temp.W * quat.Z + temp.Z * quat.W - temp.X * quat.Y + temp.Y * quat.X;

	return Vector3(x, y, z);
}

Quaternion Quaternion::Conjugate() const
{
	return Quaternion(-X, -Y, -Z, W);
}

const Quaternion Select(const Quaternion& quat0, const Quaternion& quat1, bool select1)
{
	return Quaternion(select1 ? quat1.X : quat0.X, select1 ? quat1.Y : quat0.Y, select1 ? quat1.Z : quat0.Z, select1 ? quat1.W : quat0.W);
}

float Quaternion::Dot(const Quaternion& other) const
{
	float dot = X * other.X + Y * other.Y + Z * other.Z + W * other.W;
	return dot;
}
