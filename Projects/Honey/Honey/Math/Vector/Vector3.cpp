#include "Vector3.h"

#include <Honey/Math/MathFunctions.h>

#include "Vector2.h"

using namespace Honey::Math;

Vector3::Vector3(const Vector2& vector) : X(vector.X), Y(vector.Y), Z(0.0f) {}

const Vector3 Vector3::Left    = Vector3(-1.0f,  0.0f,  0.0f);
const Vector3 Vector3::Right   = Vector3( 1.0f,  0.0f,  0.0f);
const Vector3 Vector3::Up      = Vector3( 0.0f,  1.0f,  0.0f);
const Vector3 Vector3::Down    = Vector3( 0.0f, -1.0f,  0.0f);
const Vector3 Vector3::Forward = Vector3( 0.0f,  0.0f,  1.0f);
const Vector3 Vector3::Back    = Vector3( 0.0f,  0.0f, -1.0f);

const Vector3 Vector3::Zero = Vector3(0.0f);
const Vector3 Vector3::One  = Vector3(1.0f);

const Vector3 Vector3::Infinity          = Vector3(Mathf::Infinity);
const Vector3 Vector3::NegativeInfinity  = Vector3(Mathf::NegativeInfinity);

Vector3::operator Vector2() const { return Vector2(*this); }

void Vector3::Normalize()
{
	float magnitude = GetMagnitude();
	*this /= magnitude;
}

void Vector3::Round()
{
	X = Mathf::Round(X);
	Y = Mathf::Round(Y);
	Z = Mathf::Round(Z);
}

void Vector3::Set(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

bool Vector3::ExactlyEquals(const Vector3& other) { return X == other.X && Y == other.Y && Z == other.Z; }
bool Vector3::EssentiallyEquals(const Vector3& other) { return *this == other; }

float Vector3::GetMagnitude() const { return Mathf::Sqrt(GetSquaredMagnitude()); }
float Vector3::GetSquaredMagnitude() const { return X * X + Y * Y + Z * Z; }

Vector3 Vector3::Normalized() const
{
	float magnitude = GetMagnitude();
	return (*this) / magnitude;
}

Vector3 Vector3::Rounded() const
{
	return Vector3(Mathf::Round(X), Mathf::Round(Y), Mathf::Round(Z));
}

float Vector3::Angle(const Vector3& a, const Vector3& b)
{
	float dot = Vector3::Dot(a, b);
	float theta = Mathf::Acos(dot / (a.GetMagnitude() * b.GetMagnitude()));
	return theta;
}

float Vector3::Dot(const Vector3& a, const Vector3& b)
{
	Vector3 scaled = a * b;
	return scaled.X + scaled.Y + scaled.Z;
}

float Vector3::Distance(const Vector3& a, const Vector3& b)
{
	Vector3 diff = Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
	return diff.GetMagnitude();
}

float Vector3::SquaredDistance(const Vector3& a, const Vector3& b)
{
	Vector3 diff = Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
	return diff.GetSquaredMagnitude();
}

Vector3 Vector3::Abs(const Vector3& vector)
{
	Vector3 abs = Vector3(Mathf::Abs(vector.X), Mathf::Abs(vector.Y), Mathf::Abs(vector.Z));
	return abs;
}

Vector3 Vector3::Sign(const Vector3& vector)
{
	Vector3 sign = Vector3(Mathf::Sign(vector.X), Mathf::Sign(vector.Y), Mathf::Sign(vector.Z));
	return sign;
}

Vector3 Vector3::ClampMagnitude(const Vector3& vector, float magnitude)
{
	float oldMagnitude = vector.GetMagnitude();
	return oldMagnitude < magnitude ?
		vector :
		vector * (magnitude / oldMagnitude);
}

Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
{
	float x = a.Y * b.Z - a.Z * b.Y;
	float y = a.Z * b.X - a.X * b.Z;
	float z = a.X * b.Y - a.Y * b.X;
	return Vector3(x, y, z);
}

Vector3 Vector3::Max(const Vector3& a, const Vector3& b)
{
	Vector3 max = Vector3(Mathf::Max(a.X, b.X), Mathf::Max(a.Y, b.Y), Mathf::Max(a.Z, b.Z));
	return max;
}

Vector3 Vector3::Min(const Vector3& a, const Vector3& b)
{
	Vector3 min = Vector3(Mathf::Min(a.X, b.X), Mathf::Min(a.Y, b.Y), Mathf::Min(a.Z, b.Z));
	return min;
}

Vector3 Vector3::Scale(const Vector3& a, const Vector3& b)
{
	Vector3 scaled = Vector3(a.X * b.X, a.Y * b.Y, a.Z * b.Z);
	return scaled;
}

Vector3 Vector3::Project(const Vector3& vector, const Vector3& normal)
{
	float c = Vector3::Dot(vector, normal) / normal.GetSquaredMagnitude();
	return normal * c;
}

Vector3 Vector3::ProjectOnPlane(const Vector3& vector, const Vector3& planeNormal)
{
	Vector3 projection = Vector3::Project(vector, planeNormal);
	return vector - projection;
}

Vector3 Vector3::Reflect(const Vector3& vector, const Vector3& normal)
{
	return vector - 2 * Vector3::Dot(vector, normal) * normal;
}

Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
{
	return Vector3(
		a.X + (b.X - a.X) * t,
		a.Y + (b.Y - a.Y) * t,
		a.Z + (b.Z - a.Z) * t);
}

Vector3 Vector3::LerpClamped(const Vector3& a, const Vector3& b, float t)
{
	t = Mathf::Clamp01(t);
	return Lerp(a, b, t);
}

Vector3 Vector3::MoveTowards(const Vector3& a, const Vector3& b, float distance)
{
	Vector3 dir = b - a;
	float magnitude = dir.GetMagnitude();

	if (magnitude <= distance) return b;
	return a + dir * (distance / magnitude);
}

bool Vector3::operator ==(const Vector3& other)
{
	return Mathf::ApproximatelyEquals(X, other.X)
		&& Mathf::ApproximatelyEquals(Y, other.Y)
		&& Mathf::ApproximatelyEquals(Z, other.Z);
}

Vector3& Vector3::operator +=(const Vector3& other)
{
	*this = *this + other;
	return *this;
}

Vector3& Vector3::operator -=(const Vector3& other)
{
	*this = *this - other;
	return *this;
}

Vector3& Vector3::operator *=(float scalar)
{
	*this = *this * scalar;
	return *this;
}

Vector3& Vector3::operator *=(const Vector3& vector)
{
	*this = *this * vector;
	return *this;
}

Vector3& Vector3::operator /=(float scalar)
{
	*this = *this / scalar;
	return *this;
}

Vector3& Vector3::operator /=(const Vector3& vector)
{
	*this = *this / vector;
	return *this;
}

float Vector3::operator [](int index)
{
	return operator[]((Axis)index);
}

float Vector3::operator [](int index) const
{
	return operator[]((Axis)index);
}

float Vector3::operator [](Axis axis)
{
	switch (axis)
	{
		case Axis::X: return X;
		case Axis::Y: return Y;
		case Axis::Z:
		default: return Z;
	}
}

float Vector3::operator [](Axis axis) const
{
	switch (axis)
	{
		case Axis::X: return X;
		case Axis::Y: return Y;
		case Axis::Z:
		default: return Z;
	}
}