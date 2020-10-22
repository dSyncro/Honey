#include "Vector2Int.h"

using namespace Honey;
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

Vector2Int& Vector2Int::set(Int x, Int y)
{
	// Set components
	this->x = x;
	this->y = y;
	return *this;
}

Vector2Int& Vector2Int::clamp(const Vector2Int& min, const Vector2Int& max)
{
	// Get clamped components
	Int x = Mathf::clamp(this->x, min.x, max.x);
	Int y = Mathf::clamp(this->y, min.y, max.y);

	return set(x, y); // Set clamped components
}

bool Vector2Int::equals(const Vector2Int& other) const { return *this == other; }

Float Vector2Int::getMagnitude() const
{
	Float sqrMagnitude = static_cast<Float>(getSquaredMagnitude());
	return Mathf::sqrt(sqrMagnitude);
}

Int Vector2Int::getSquaredMagnitude() const
{
	return x * x + y * y;
}

Vector2Int Vector2Int::abs(const Vector2Int& vector)
{
	return Vector2Int(Mathf::abs(vector.x), Mathf::abs(vector.y));
}

Vector2Int Vector2Int::sign(const Vector2Int& vector)
{
	return Vector2Int(Mathf::sign(vector.x), Mathf::sign(vector.y));
}

Vector2Int Vector2Int::ceilToInt(const Vector2& vector) 
{ 
	return Vector2Int(Mathf::ceilToInt(vector.x), Mathf::ceilToInt(vector.y)); 
}

Vector2Int Vector2Int::floorToInt(const Vector2& vector) 
{ 
	return Vector2Int(Mathf::floorToInt(vector.x), Mathf::floorToInt(vector.y)); 
}

Vector2Int Vector2Int::roundToInt(const Vector2& vector) 
{ 
	return Vector2Int(Mathf::roundToInt(vector.x), Mathf::roundToInt(vector.y)); 
}

Vector2Int Vector2Int::max(const Vector2Int& a, const Vector2Int& b) 
{ 
	return Vector2Int(Mathf::max(a.x, b.x), Mathf::max(a.y, b.y)); 
}

Vector2Int Vector2Int::min(const Vector2Int& a, const Vector2Int& b) 
{ 
	return Vector2Int(Mathf::min(a.x, b.x), Mathf::min(a.y, b.y)); 
}

Vector2Int Vector2Int::scale(const Vector2Int& a, const Vector2Int& b)
{
	// To scale two vectors we just need to multiply them together
	return a * b;
}

Float Vector2Int::distance(const Vector2Int& a, const Vector2Int& b)
{
	// Distance is the magnitude of the vector from a to b.
	Vector2Int diff = Vector2Int(a.x - b.x, a.y - b.y);
	return diff.getMagnitude();
}

Int Vector2Int::squaredDistance(const Vector2Int& a, const Vector2Int& b)
{
	// Squared distance is the squared magnitude of the vector from a to b.
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

Vector2Int& Honey::Math::Vector2Int::operator *=(Int scalar)
{
	*this = *this * scalar;
	return *this;
}

Vector2Int& Vector2Int::operator *=(const Vector2Int& other)
{
	*this = *this * other;
	return *this;
}

Vector2Int& Vector2Int::operator/=(Int scalar)
{
	*this = *this / scalar;
	return *this;
}

Vector2Int& Vector2Int::operator/=(const Vector2Int& other)
{
	*this = *this / other;
	return *this;
}
