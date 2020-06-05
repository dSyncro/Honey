#include "Vector2.h"

#include "Vector3.h"

using namespace Honey::Math;

Vector2::Vector2(const Vector3& vector) : X(vector.X), Y(vector.Y) {}

const Vector2 Vector2::Left  = Vector2(-1.0f,  0.0f);
const Vector2 Vector2::Right = Vector2( 1.0f,  0.0f);
const Vector2 Vector2::Up    = Vector2( 0.0f,  1.0f);
const Vector2 Vector2::Down  = Vector2( 0.0f, -1.0f);

const Vector2 Vector2::Zero = Vector2(0.0f);
const Vector2 Vector2::One  = Vector2(1.0f);

Vector2::operator Vector3() const { return Vector3(*this); }

float Vector2::GetMagnitude() const { return Mathf::Sqrt(GetSquaredMagnitude()); }
float Vector2::GetSquaredMagnitude() const { return X * X + Y * Y; }

Vector2 Vector2::Normalized() const
{
	float magnitude = GetMagnitude();
	return (*this) / magnitude;
}

void Vector2::Normalize()
{
	float magnitude = GetMagnitude();
	X /= magnitude;
	Y /= magnitude;
}

void Vector2::Set(float x, float y)
{
	X = x;
	Y = y;
}

bool Vector2::ExactlyEquals(const Vector2& other) { return X == other.X && Y == other.Y; }
bool Vector2::EssentiallyEquals(const Vector2& other) { return *this == other; }

float Vector2::Dot(const Vector2& a, const Vector2& b)
{
	Vector2 scaled = Vector2::Scale(a, b);
	return scaled.X + scaled.Y;
}

float Vector2::Distance(const Vector2& a, const Vector2& b)
{
	Vector2 diff = Vector2(a.X - b.X, a.Y - b.Y);
	return diff.GetMagnitude();
}

float Vector2::SquaredDistance(const Vector2& a, const Vector2& b)
{
	Vector2 diff = Vector2(a.X - b.X, a.Y - b.Y);
	return diff.GetSquaredMagnitude();
}

Vector2 Vector2::Max(const Vector2& a, const Vector2& b)
{
	Vector2 max = Vector2(Mathf::Max(a.X, b.X), Mathf::Max(a.Y, b.Y));
	return max;
}

Vector2 Vector2::Min(const Vector2& a, const Vector2& b)
{
	Vector2 min = Vector2(Mathf::Min(a.X, b.X), Mathf::Min(a.Y, b.Y));
	return min;
}

Vector2 Vector2::Scale(const Vector2& a, const Vector2& b)
{
	Vector2 scaled = Vector2(a.X * b.X, a.Y * b.Y);
	return scaled;
}