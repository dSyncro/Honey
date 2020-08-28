#include "Vector2Int.h"

using namespace Honey::Math;

const Vector2Int Vector2Int::Left  = Vector2Int(-1,  0);
const Vector2Int Vector2Int::Right = Vector2Int( 1,  0);
const Vector2Int Vector2Int::Up    = Vector2Int( 0,  1);
const Vector2Int Vector2Int::Down  = Vector2Int( 0, -1);
const Vector2Int Vector2Int::Zero  = Vector2Int( 0,  0);
const Vector2Int Vector2Int::One   = Vector2Int( 1,  1);

Vector2Int& Vector2Int::Set(int x, int y)
{
	X = x;
	Y = y;
	return *this;
}

Vector2Int& Vector2Int::Clamp(const Vector2Int& min, const Vector2Int& max)
{
	int x = (int)Mathf::Clamp(X, min.X, max.X);
	int y = (int)Mathf::Clamp(Y, min.Y, max.Y);
	return Set(x, y);
}

bool Vector2Int::Equals(const Vector2Int& other) const { return *this == other; }

float Vector2Int::GetMagnitude() const
{
	return X * X + Y * Y;
}

float Vector2Int::GetSquaredMagnitude() const
{
	return Mathf::Sqrt(GetMagnitude());
}

Vector2Int Vector2Int::Abs(const Vector2Int& vector)
{
	return Vector2Int(Mathf::Abs(vector.X), Mathf::Abs(vector.Y));
}

Vector2Int Vector2Int::Sign(const Vector2Int& vector)
{
	return Vector2Int(Mathf::Sign(vector.X), Mathf::Sign(vector.Y));
}

Vector2Int Vector2Int::CeilToInt(const Vector2& vector) 
{ 
	return Vector2Int(Mathf::CeilToInt(vector.X), Mathf::CeilToInt(vector.Y)); 
}

Vector2Int Vector2Int::FloorToInt(const Vector2& vector) 
{ 
	return Vector2Int(Mathf::FloorToInt(vector.X), Mathf::FloorToInt(vector.Y)); 
}

Vector2Int Vector2Int::RoundToInt(const Vector2& vector) 
{ 
	return Vector2Int(Mathf::RoundToInt(vector.X), Mathf::RoundToInt(vector.Y)); 
}

Vector2Int Vector2Int::Max(const Vector2Int& a, const Vector2Int& b) 
{ 
	return Vector2Int(Mathf::Max(a.X, b.X), Mathf::Max(a.Y, b.Y)); 
}

Vector2Int Vector2Int::Min(const Vector2Int& a, const Vector2Int& b) 
{ 
	return Vector2Int(Mathf::Min(a.X, b.X), Mathf::Max(a.Y, b.Y)); 
}

Vector2Int Vector2Int::Scale(const Vector2Int& a, const Vector2Int& b)
{
	return a * b;
}

float Vector2Int::Distance(const Vector2Int& a, const Vector2Int& b)
{
	Vector2Int diff = Vector2Int(a.X - b.X, a.Y - b.Y);
	return diff.GetMagnitude();
}

float Vector2Int::SquaredDistance(const Vector2Int& a, const Vector2Int& b)
{
	Vector2Int diff = Vector2Int(a.X - b.X, a.Y - b.Y);
	return diff.GetSquaredMagnitude();
}

Vector2Int& Vector2Int::operator +=(const Vector2Int& other)
{
	*this = *this + other;
	return *this;
}

Vector2Int& Vector2Int::operator -=(const Vector2Int& other)
{
	*this = *this - other;
	return *this;
}

Vector2Int& Honey::Math::Vector2Int::operator *=(int scalar)
{
	*this = *this * scalar;
	return *this;
}

Vector2Int& Vector2Int::operator *=(const Vector2Int& other)
{
	*this = *this * other;
	return *this;
}

Vector2Int& Vector2Int::operator/=(int scalar)
{
	*this = *this / scalar;
	return *this;
}

Vector2Int& Vector2Int::operator/=(const Vector2Int& other)
{
	*this = *this / other;
	return *this;
}
