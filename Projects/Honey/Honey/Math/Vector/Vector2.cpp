#include "Vector2.h"

#include <Honey/Math/MathFunctions.h>

#include "Vector3.h"
#include "Vector4.h"

using namespace Honey::Math;

const Vector2& Vector2::left()
{
	static constexpr Vector2 left = Vector2(-1.0f, 0.0f);
	return left;
}

const Vector2& Vector2::right()
{
	static constexpr Vector2 right = Vector2(1.0f, 0.0f);
	return right;
}

const Vector2& Vector2::up()
{
	static constexpr Vector2 up = Vector2(0.0f, 1.0f);
	return up;
}

const Vector2& Vector2::down()
{
	static constexpr Vector2 down = Vector2(0.0f, -1.0f);
	return down;
}

const Vector2& Vector2::zero()
{
	static constexpr Vector2 zero = Vector2(0.0f);
	return zero;
}

const Vector2& Vector2::one()
{
	static constexpr Vector2 one = Vector2(1.0f);
	return one;
}

const Vector2& Vector2::infinity()
{
	static constexpr Vector2 inf = Vector2(Mathf::infinity());
	return inf;
}

const Vector2& Vector2::negativeInfinity()
{
	static constexpr Vector2 negInf = Vector2(Mathf::negativeInfinity());
	return negInf;
}

Vector2& Vector2::normalize()
{
	float magnitude = getMagnitude();
	return *this /= magnitude;
}

Vector2& Vector2::round()
{
	x = Mathf::Round(x);
	y = Mathf::Round(y);
	return *this;
}

Vector2& Vector2::set(float x, float y)
{
	this->x = x;
	this->y = y;
	return *this;
}

bool Vector2::exactlyEquals(const Vector2& other) const { return x == other.x && y == other.y; }
bool Vector2::essentiallyEquals(const Vector2& other) const { return *this == other; }

float Vector2::getMagnitude() const { return Mathf::Sqrt(getSquaredMagnitude()); }
float Vector2::getSquaredMagnitude() const { return x * x + y * y; }

Vector2 Vector2::normalized() const
{
	float magnitude = getMagnitude();
	return (*this) / magnitude;
}

Vector2 Vector2::rounded() const
{
	return Vector2(Mathf::Round(x), Mathf::Round(y));
}

float Vector2::angle(const Vector2& a, const Vector2& b)
{
	float dot = Vector2::dot(a, b);
	float theta = Mathf::Acos(dot / (a.getMagnitude() * b.getMagnitude()));
	return theta;
}

float Vector2::dot(const Vector2& a, const Vector2& b)
{
	Vector2 scaled = a * b;
	return scaled.x + scaled.y;
}

float Vector2::distance(const Vector2& a, const Vector2& b)
{
	Vector2 diff = Vector2(a.x - b.x, a.y - b.y);
	return diff.getMagnitude();
}

float Vector2::squaredDistance(const Vector2& a, const Vector2& b)
{
	Vector2 diff = Vector2(a.x - b.x, a.y - b.y);
	return diff.getSquaredMagnitude();
}

Vector2 Vector2::abs(const Vector2& vector)
{
	Vector2 abs = Vector2(Mathf::Abs(vector.x), Mathf::Abs(vector.y));
	return abs;
}

Vector2 Vector2::sign(const Vector2& vector)
{
	Vector2 sign = Vector2(Mathf::Sign(vector.x), Mathf::Sign(vector.y));
	return sign;
}

Vector2 Vector2::perpendicularClockwise(const Vector2& vector)
{
	return Vector2(vector.y, -vector.x);
}

Vector2 Vector2::perpendicularCounterClockwise(const Vector2& vector)
{
	return Vector2(-vector.y, vector.x);
}

Vector2 Vector2::clampMagnitude(const Vector2& vector, float magnitude)
{
	float oldMagnitude = vector.getMagnitude();
	return oldMagnitude < magnitude ?
		vector :
		vector * (magnitude / oldMagnitude);
}

Vector2 Vector2::rotate(const Vector2& vector, float angle)
{
	float x = vector.x * Mathf::Cos(angle) - vector.y * Mathf::Sin(angle);
	float y = vector.x * Mathf::Sin(angle) + vector.y * Mathf::Cos(angle);
	return Vector2(x, y);
}

Vector2 Vector2::max(const Vector2& a, const Vector2& b)
{
	Vector2 max = Vector2(Mathf::Max(a.x, b.x), Mathf::Max(a.y, b.y));
	return max;
}

Vector2 Vector2::min(const Vector2& a, const Vector2& b)
{
	Vector2 min = Vector2(Mathf::Min(a.x, b.x), Mathf::Min(a.y, b.y));
	return min;
}

Vector2 Vector2::scale(const Vector2& a, const Vector2& b)
{
	Vector2 scaled = Vector2(a.x * b.x, a.y * b.y);
	return scaled;
}

Vector2 Vector2::reflect(const Vector2& vector, const Vector2& normal)
{
	return vector - 2 * Vector2::dot(vector, normal) * normal;
}

Vector2 Vector2::lerp(const Vector2& a, const Vector2& b, float t)
{
	return a + (b - a) * t;
}

Vector2 Vector2::lerpClamped(const Vector2& a, const Vector2& b, float t)
{
	t = Mathf::Clamp01(t);
	return lerp(a, b, t);
}

Vector2 Vector2::moveTowards(const Vector2& a, const Vector2& b, float distance)
{
	Vector2 dir = b - a;
	float magnitude = dir.getMagnitude();

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

Vector2& Vector2::operator *=(const Vector2& other)
{
	*this = *this * other;
	return *this;
}

Vector2& Vector2::operator /=(float scalar)
{
	*this = *this / scalar;
	return *this;
}

Vector2& Vector2::operator /=(const Vector2& other)
{
	*this = *this / other;
	return *this;
}
