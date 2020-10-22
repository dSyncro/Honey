#include "Vector3.h"

#include <Honey/Math/MathFunctions.h>
#include <Honey/Math/Matrix/Matrix4x4.h>

#include "Vector2.h"

using namespace Honey;
using namespace Honey::Math;

const Vector3& Vector3::left()
{
	static constexpr Vector3 left = Vector3(-1.0f,  0.0f,  0.0f);
	return left;
}

const Vector3& Vector3::right()
{
	static constexpr Vector3 right = Vector3(1.0f, 0.0f, 0.0f);
	return right;
}

const Vector3& Vector3::up()
{
	static constexpr Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	return up;
}

const Vector3& Vector3::down()
{
	static constexpr Vector3 down = Vector3(0.0f, -1.0f, 0.0f);
	return down;
}

const Vector3& Vector3::forward()
{
	static constexpr Vector3 forward = Vector3(0.0f, 0.0f, 1.0f);
	return forward;
}

const Vector3& Vector3::back()
{
	static constexpr Vector3 back = Vector3(0.0f, 0.0f, -1.0f);
	return back;
}

const Vector3& Vector3::zero()
{
	static constexpr Vector3 zero = Vector3(0.0f);
	return zero;
}

const Vector3& Vector3::one()
{
	static constexpr Vector3 one = Vector3(1.0f);
	return one;
}

const Vector3& Vector3::infinity()
{
	static constexpr Vector3 inf = Vector3(Mathf::infinity());
	return inf;
}

const Vector3& Vector3::negativeInfinity()
{
	static constexpr Vector3 negInf = Vector3(Mathf::negativeInfinity());
	return negInf;
}

Vector3& Vector3::normalize()
{
	Float magnitude = getMagnitude();
	return *this /= magnitude;
}

Vector3& Vector3::round()
{
	x = Mathf::round(x);
	y = Mathf::round(y);
	z = Mathf::round(z);
	return *this;
}

Vector3& Vector3::set(Float x, Float y, Float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

bool Vector3::exactlyEquals(const Vector3& other) { return x == other.x && y == other.y && z == other.z; }
bool Vector3::essentiallyEquals(const Vector3& other) { return *this == other; }

Float Vector3::getMagnitude() const { return Mathf::sqrt(getSquaredMagnitude()); }
Float Vector3::getSquaredMagnitude() const { return x * x + y * y + z * z; }

Vector3 Vector3::normalized() const
{
	Float magnitude = getMagnitude();
	return *this / magnitude;
}

Vector3 Vector3::rounded() const
{
	return Vector3(Mathf::round(x), Mathf::round(y), Mathf::round(z));
}

std::string Vector3::toString() const
{
	std::string out = "Vector3(" +
		std::to_string(x) + "; " +
		std::to_string(y) + "; " +
		std::to_string(z) + ")";

	return out;
}

float Vector3::angle(const Vector3& a, const Vector3& b)
{
	Float dot = Vector3::dot(a, b);
	Float theta = Mathf::acos(dot / (a.getMagnitude() * b.getMagnitude()));
	return theta;
}

float Vector3::dot(const Vector3& a, const Vector3& b)
{
	Vector3 scaled = a * b;
	return scaled.x + scaled.y + scaled.z;
}

float Vector3::distance(const Vector3& a, const Vector3& b)
{
	Vector3 diff = Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	return diff.getMagnitude();
}

float Vector3::squaredDistance(const Vector3& a, const Vector3& b)
{
	Vector3 diff = Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	return diff.getSquaredMagnitude();
}

Vector3 Vector3::abs(const Vector3& vector)
{
	Vector3 abs = Vector3(Mathf::abs(vector.x), Mathf::abs(vector.y), Mathf::abs(vector.z));
	return abs;
}

Vector3 Vector3::sign(const Vector3& vector)
{
	Vector3 sign = Vector3(Mathf::sign(vector.x), Mathf::sign(vector.y), Mathf::sign(vector.z));
	return sign;
}

Vector3 Vector3::clampMagnitude(const Vector3& vector, Float magnitude)
{
	Float oldMagnitude = vector.getMagnitude();

	if (oldMagnitude <= magnitude) return vector;

	return vector * (magnitude / oldMagnitude);
}

Vector3 Vector3::cross(const Vector3& a, const Vector3& b)
{
	Float x = a.y * b.z - a.z * b.y;
	Float y = a.z * b.x - a.x * b.z;
	Float z = a.x * b.y - a.y * b.x;
	return Vector3(x, y, z);
}

Vector3 Vector3::max(const Vector3& a, const Vector3& b)
{
	Vector3 max = Vector3(Mathf::max(a.x, b.x), Mathf::max(a.y, b.y), Mathf::max(a.z, b.z));
	return max;
}

Vector3 Vector3::min(const Vector3& a, const Vector3& b)
{
	Vector3 min = Vector3(Mathf::min(a.x, b.x), Mathf::min(a.y, b.y), Mathf::min(a.z, b.z));
	return min;
}

Vector3 Vector3::scale(const Vector3& a, const Vector3& b)
{
	Vector3 scaled = Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
	return scaled;
}

Vector3 Vector3::project(const Vector3& vector, const Vector3& normal)
{
	Float c = Vector3::dot(vector, normal) / normal.getSquaredMagnitude();
	return normal * c;
}

Vector3 Vector3::projectOnPlane(const Vector3& vector, const Vector3& planeNormal)
{
	Vector3 projection = Vector3::project(vector, planeNormal);
	return vector - projection;
}

Vector3 Vector3::reflect(const Vector3& vector, const Vector3& normal)
{
	return vector - 2 * Vector3::dot(vector, normal) * normal;
}

Vector3 Vector3::lerp(const Vector3& a, const Vector3& b, Float t)
{
	return a + (b - a) * t;
}

Vector3 Vector3::lerpClamped(const Vector3& a, const Vector3& b, Float t)
{
	t = Mathf::clamp01(t);
	return lerp(a, b, t);
}

Vector3 Vector3::moveTowards(const Vector3& a, const Vector3& b, Float distance)
{
	Vector3 dir = b - a;
	Float magnitude = dir.getMagnitude();

	if (magnitude <= distance) return b;
	return a + dir * (distance / magnitude);
}

bool Vector3::operator ==(const Vector3& other)
{
	return Mathf::approximatelyEquals(x, other.x)
		&& Mathf::approximatelyEquals(y, other.y)
		&& Mathf::approximatelyEquals(z, other.z);
}

Vector3 Vector3::operator *(const Matrix4x4& matrix) const
{
	return Vector3(
		matrix.rows[0].x * x + matrix.rows[0].y * y + matrix.rows[0].z * z + matrix.rows[0].w,
		matrix.rows[1].x * x + matrix.rows[1].y * y + matrix.rows[1].z * z + matrix.rows[1].w,
		matrix.rows[2].x * x + matrix.rows[2].y * y + matrix.rows[2].z * z + matrix.rows[2].w
	);
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

Vector3& Vector3::operator *=(Float scalar)
{
	*this = *this * scalar;
	return *this;
}

Vector3& Vector3::operator *=(const Vector3& vector)
{
	*this = *this * vector;
	return *this;
}

Vector3& Vector3::operator /=(Float scalar)
{
	*this = *this / scalar;
	return *this;
}

Vector3& Vector3::operator /=(const Vector3& vector)
{
	*this = *this / vector;
	return *this;
}

Float& Vector3::operator [](Int index)
{
	return operator[](static_cast<Axis>(index));
}

Float Vector3::operator [](Int index) const
{
	return operator[](static_cast<Axis>(index));
}

Float& Vector3::operator [](Axis axis)
{
	switch (axis)
	{
		case Axis::X: return x;
		case Axis::Y: return y;
		case Axis::Z:
		default: return z;
	}
}

Float Vector3::operator [](Axis axis) const
{
	switch (axis)
	{
		case Axis::X: return x;
		case Axis::Y: return y;
		case Axis::Z:
		default: return z;
	}
}
