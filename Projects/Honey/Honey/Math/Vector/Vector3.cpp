#include "Vector3.h"

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

Vector3::operator Vector2() const { return Vector2(*this); }

float Vector3::GetMagnitude() const { return Mathf::Sqrt(GetSquaredMagnitude()); }
float Vector3::GetSquaredMagnitude() const { return X * X + Y * Y + Z * Z; }

Vector3 Vector3::Normalized() const
{
	float magnitude = GetMagnitude();
	return (*this) / magnitude;
}

void Vector3::Normalize()
{
	float magnitude = GetMagnitude();
	X /= magnitude;
	Y /= magnitude;
	Z /= magnitude;
}

void Vector3::Set(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

bool Vector3::ExactlyEquals(const Vector3& other) { return X == other.X && Y == other.Y && Z == other.Z; }
bool Vector3::EssentiallyEquals(const Vector3& other) { return *this == other; }

float Vector3::Dot(const Vector3& a, const Vector3& b)
{
	Vector3 scaled = Vector3::Scale(a, b);
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