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

const Vector2 Vector2::Infinity         = Vector2(Mathf::Infinity);
const Vector2 Vector2::NegativeInfinity = Vector2(Mathf::NegativeInfinity);

Vector2::operator Vector3() const { return Vector3(*this); }

void Vector2::Normalize()
{
	float magnitude = GetMagnitude();
	*this /= magnitude;
}

void Vector2::Round()
{
	X = Mathf::Round(X);
	Y = Mathf::Round(Y);
}

void Vector2::Set(float x, float y)
{
	X = x;
	Y = y;
}

bool Vector2::ExactlyEquals(const Vector2& other) { return X == other.X && Y == other.Y; }
bool Vector2::EssentiallyEquals(const Vector2& other) { return *this == other; }

float Vector2::GetMagnitude() const { return Mathf::Sqrt(GetSquaredMagnitude()); }
float Vector2::GetSquaredMagnitude() const { return X * X + Y * Y; }

Vector2 Vector2::Normalized() const
{
	float magnitude = GetMagnitude();
	return (*this) / magnitude;
}

Vector2 Vector2::Rounded() const
{
	return Vector2(Mathf::Round(X), Mathf::Round(Y));
}

float Vector2::Angle(const Vector2& a, const Vector2& b)
{
	float dot = Vector2::Dot(a, b);
	float theta = Mathf::Acos(dot / (a.GetMagnitude() * b.GetMagnitude()));
	return theta;
}

float Vector2::Dot(const Vector2& a, const Vector2& b)
{
	Vector2 scaled = a * b;
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

Vector2 Vector2::Abs(const Vector2& vector)
{
	Vector2 abs = Vector2(Mathf::Abs(vector.X), Mathf::Abs(vector.Y));
	return abs;
}

Vector2 Vector2::Sign(const Vector2& vector)
{
	Vector2 sign = Vector2(Mathf::Sign(vector.X), Mathf::Sign(vector.Y));
	return sign;
}

Vector2 Vector2::PerpendicularClockwise(const Vector2& vector)
{
	return Vector2(vector.Y, -vector.X);
}

Vector2 Vector2::PerpendicularCounterClockwise(const Vector2& vector)
{
	return Vector2(-vector.Y, vector.X);
}

Vector2 Vector2::ClampMagnitude(const Vector2& vector, float magnitude)
{
	float oldMagnitude = vector.GetMagnitude();
	return oldMagnitude < magnitude ?
		vector :
		vector * (magnitude / oldMagnitude);
}

Vector2 Vector2::Rotate(const Vector2& vector, float angle)
{
	float x = vector.X * Mathf::Cos(angle) - vector.Y * Mathf::Sin(angle);
	float y = vector.X * Mathf::Sin(angle) + vector.Y * Mathf::Cos(angle);
	return Vector2(x, y);
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

Vector2 Vector2::Reflect(const Vector2& vector, const Vector2& normal)
{
	return vector - 2 * Vector2::Dot(vector, normal) * normal;
}

Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
{
	return Vector2(
		a.X + (b.X - a.X) * t,
		a.Y + (b.Y - a.Y) * t);
}

Vector2 Vector2::LerpClamped(const Vector2& a, const Vector2& b, float t)
{
	t = Mathf::Clamp01(t);
	return Lerp(a, b, t);
}

Vector2 Vector2::MoveTowards(const Vector2& a, const Vector2& b, float distance)
{
	Vector2 dir = b - a;
	float magnitude = dir.GetMagnitude();

	if (magnitude <= distance) return b;
	return a + dir * (distance / magnitude);
}

Vector2& Vector2::operator +=(const Vector2& other)
{
	*this = *this + other;
	return *this;
}

Vector2& Vector2::operator -=(const Vector2& other)
{
	*this = *this - other;
	return *this;
}

Vector2& Vector2::operator *=(float scalar)
{
	*this = *this * scalar;
	return *this;
}

Vector2& Vector2::operator *=(const Vector2& vector)
{
	*this = *this * vector;
	return *this;
}

Vector2& Vector2::operator /=(float scalar)
{
	*this = *this / scalar;
	return *this;
}

Vector2& Vector2::operator /=(const Vector2& vector)
{
	*this = *this / vector;
	return *this;
}