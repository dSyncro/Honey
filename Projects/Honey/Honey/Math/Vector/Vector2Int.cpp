#include "Vector2Int.h"

using namespace Honey::Math;

const Vector2Int& Vector2Int::left()
{
	static constexpr Vector2Int left = Vector2Int(-1, 0);
	return left;
}

const Vector2Int& Vector2Int::right()
{
	static constexpr Vector2Int right = Vector2Int(1, 0);
	return right;
}

const Vector2Int& Vector2Int::up()
{
	static constexpr Vector2Int up = Vector2Int(0, 1);
	return up;
}

const Vector2Int& Vector2Int::down()
{
	static constexpr Vector2Int down = Vector2Int(0, -1);
	return down;
}

const Vector2Int& Vector2Int::zero()
{
	static constexpr Vector2Int zero = Vector2Int(0);
	return zero;
}

const Vector2Int& Vector2Int::one()
{
	static constexpr Vector2Int one = Vector2Int(1);
	return one;
}

Vector2Int& Vector2Int::set(int x, int y)
{
	this->x = x;
	this->y = y;
	return *this;
}

Vector2Int& Vector2Int::clamp(const Vector2Int& min, const Vector2Int& max)
{
	int x = (int)Mathf::Clamp(x, min.x, max.x);
	int y = (int)Mathf::Clamp(y, min.y, max.y);
	return set(x, y);
}

bool Vector2Int::equals(const Vector2Int& other) const { return *this == other; }

float Vector2Int::getMagnitude() const
{
	return x * x + y * y;
}

float Vector2Int::getSquaredMagnitude() const
{
	return Mathf::Sqrt(getMagnitude());
}

Vector2Int Vector2Int::abs(const Vector2Int& vector)
{
	return Vector2Int(Mathf::Abs(vector.x), Mathf::Abs(vector.y));
}

Vector2Int Vector2Int::sign(const Vector2Int& vector)
{
	return Vector2Int(Mathf::Sign(vector.x), Mathf::Sign(vector.y));
}

Vector2Int Vector2Int::ceilToInt(const Vector2& vector) 
{ 
	return Vector2Int(Mathf::CeilToInt(vector.x), Mathf::CeilToInt(vector.y)); 
}

Vector2Int Vector2Int::floorToInt(const Vector2& vector) 
{ 
	return Vector2Int(Mathf::FloorToInt(vector.x), Mathf::FloorToInt(vector.y)); 
}

Vector2Int Vector2Int::roundToInt(const Vector2& vector) 
{ 
	return Vector2Int(Mathf::RoundToInt(vector.x), Mathf::RoundToInt(vector.y)); 
}

Vector2Int Vector2Int::max(const Vector2Int& a, const Vector2Int& b) 
{ 
	return Vector2Int(Mathf::Max(a.x, b.x), Mathf::Max(a.y, b.y)); 
}

Vector2Int Vector2Int::min(const Vector2Int& a, const Vector2Int& b) 
{ 
	return Vector2Int(Mathf::Min(a.x, b.x), Mathf::Max(a.y, b.y)); 
}

Vector2Int Vector2Int::scale(const Vector2Int& a, const Vector2Int& b)
{
	return a * b;
}

float Vector2Int::distance(const Vector2Int& a, const Vector2Int& b)
{
	Vector2Int diff = Vector2Int(a.x - b.x, a.y - b.y);
	return diff.getMagnitude();
}

float Vector2Int::squaredDistance(const Vector2Int& a, const Vector2Int& b)
{
	Vector2Int diff = Vector2Int(a.x - b.x, a.y - b.y);
	return diff.getSquaredMagnitude();
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
