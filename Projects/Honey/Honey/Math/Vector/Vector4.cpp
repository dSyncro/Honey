#include "Vector4.h"

#include <Honey/Math/MathFunctions.h>
#include <Honey/Math/Matrix/Matrix4x4.h>

#include "Vector2.h"
#include "Vector3.h"

using namespace Honey;
using namespace Honey::Math;

const Vector4& Vector4::zero()
{
	static constexpr Vector4 zero = Vector4(0.0f);
	return zero;
}

const Vector4& Vector4::one()
{
	static constexpr Vector4 one = Vector4(1.0f);
	return one;
}

const Vector4& Vector4::infinity()
{
	static constexpr Vector4 inf = Vector4(Mathf::infinity());
	return inf;
}

const Vector4& Vector4::negativeInfinity()
{
	static constexpr Vector4 negInf = Vector4(Mathf::negativeInfinity());
	return negInf;
}

Vector4& Vector4::normalize()
{
	Float magnitude = getMagnitude();
	return *this /= magnitude;
}

Vector4& Vector4::round()
{
	x = Mathf::round(x);
	y = Mathf::round(y);
	z = Mathf::round(z);
	w = Mathf::round(w);
	return *this;
}

Vector4& Vector4::set(Float x, Float y, Float z, Float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	return *this;
}

bool Vector4::exactlyEquals(const Vector4& other) { return x == other.x && y == other.y && z == other.z && w == other.w; }
bool Vector4::essentiallyEquals(const Vector4& other) { return *this == other; }

Float Vector4::getMagnitude() const { return Mathf::sqrt(getSquaredMagnitude()); }
Float Vector4::getSquaredMagnitude() const { return x * x + y * y + z * z + w * w; }

Vector4 Vector4::normalized() const
{
	Float magnitude = getMagnitude();
	return (*this) / magnitude;
}

Vector4 Vector4::rounded() const
{
	return Vector4(Mathf::round(x), Mathf::round(y), Mathf::round(z), Mathf::round(w));
}

Float Vector4::dot(const Vector4& a, const Vector4& b)
{
	Vector4 scaled = a * b;
	return scaled.x + scaled.y + scaled.z + scaled.w;
}

Float Vector4::distance(const Vector4& a, const Vector4& b)
{
	Vector4 diff = Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	return diff.getMagnitude();
}

Float Vector4::squaredDistance(const Vector4& a, const Vector4& b)
{
	Vector4 diff = Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	return diff.getSquaredMagnitude();
}

Vector4 Vector4::abs(const Vector4& vector)
{
	Vector4 abs = Vector4(Mathf::abs(vector.x), Mathf::abs(vector.y), Mathf::abs(vector.z), Mathf::abs(vector.w));
	return abs;
}

Vector4 Vector4::sign(const Vector4& vector)
{
	Vector4 sign = Vector4(Mathf::sign(vector.x), Mathf::sign(vector.y), Mathf::sign(vector.z), Mathf::sign(vector.w));
	return sign;
}

Vector4 Vector4::clampMagnitude(const Vector4& vector, Float magnitude)
{
	Float oldMagnitude = vector.getMagnitude();
	if (oldMagnitude <= magnitude) return vector;
	return vector * (magnitude / oldMagnitude);	
}

Vector4 Vector4::max(const Vector4& a, const Vector4& b)
{
	Vector4 max = Vector4(Mathf::max(a.x, b.x), Mathf::max(a.y, b.y), Mathf::max(a.z, b.z), Mathf::max(a.w, b.w));
	return max;
}

Vector4 Vector4::min(const Vector4& a, const Vector4& b)
{
	Vector4 min = Vector4(Mathf::min(a.x, b.x), Mathf::min(a.y, b.y), Mathf::min(a.z, b.z), Mathf::min(a.w, b.w));
	return min;
}

Vector4 Vector4::scale(const Vector4& a, const Vector4& b)
{
	Vector4 scaled = Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	return scaled;
}

Vector4 Vector4::project(const Vector4& vector, const Vector4& normal)
{
	Float c = Vector4::dot(vector, normal) / normal.getSquaredMagnitude();
	return normal * c;
}

Vector4 Vector4::lerp(const Vector4& a, const Vector4& b, Float t)
{
	return a + (b - a) * t;
}

Vector4 Vector4::lerpClamped(const Vector4& a, const Vector4& b, Float t)
{
	t = Mathf::clamp01(t);
	return lerp(a, b, t);
}

Vector4 Vector4::moveTowards(const Vector4& a, const Vector4& b, Float distance)
{
	Vector4 dir = b - a;
	Float magnitude = dir.getMagnitude();

	if (magnitude <= distance) return b;
	return a + dir * (distance / magnitude);
}

bool Vector4::operator ==(const Vector4& other)
{
	return Mathf::approximatelyEquals(x, other.x)
		&& Mathf::approximatelyEquals(y, other.y)
		&& Mathf::approximatelyEquals(z, other.z)
		&& Mathf::approximatelyEquals(w, other.w);
}

Vector4 Vector4::operator *(const Matrix4x4& matrix) const
{
	return Vector4(
		matrix.rows[0].x * x + matrix.rows[0].y * y + matrix.rows[0].z * z + matrix.rows[0].w * w,
		matrix.rows[1].x * x + matrix.rows[1].y * y + matrix.rows[1].z * z + matrix.rows[1].w * w,
		matrix.rows[2].x * x + matrix.rows[2].y * y + matrix.rows[2].z * z + matrix.rows[2].w * w,
		matrix.rows[3].x * x + matrix.rows[3].y * y + matrix.rows[3].z * z + matrix.rows[3].w * w
	);
}

Vector4& Vector4::operator +=(const Vector4& other)
{
	*this = *this + other;
	return *this;
}

Vector4& Vector4::operator -=(const Vector4& other)
{
	*this = *this - other;
	return *this;
}

Vector4& Vector4::operator *=(Float scalar)
{
	*this = *this * scalar;
	return *this;
}

Vector4& Vector4::operator *=(const Vector4& vector)
{
	*this = *this * vector;
	return *this;
}

Vector4& Vector4::operator /=(Float scalar)
{
	*this = *this / scalar;
	return *this;
}

Vector4& Vector4::operator /=(const Vector4& vector)
{
	*this = *this / vector;
	return *this;
}

Float& Vector4::operator [](Int index)
{
	return operator[](static_cast<Axis>(index));
}

Float Vector4::operator [](Int index) const
{
	return operator[](static_cast<Axis>(index));
}

Float& Vector4::operator [](Axis axis)
{
	switch (axis)
	{
		case Axis::X: return x;
		case Axis::Y: return y;
		case Axis::Z: return z;
		case Axis::W:
		default: return w;
	}
}

Float Vector4::operator [](Axis axis) const
{
	switch (axis)
	{
		case Axis::X: return x;
		case Axis::Y: return y;
		case Axis::Z: return z;
		case Axis::W:
		default: return w;
	}
}
