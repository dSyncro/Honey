#include "Vector4.h"

#include <Honey/Math/MathFunctions.h>
#include <Honey/Math/Matrix/Matrix4x4.h>

#include "Vector2.h"
#include "Vector3.h"

using namespace Honey::Math;

const Vector4 Vector4::Zero = Vector4(0.0f);
const Vector4 Vector4::One  = Vector4(1.0f);

const Vector4 Vector4::Infinity         = Vector4(Mathf::Infinity);
const Vector4 Vector4::NegativeInfinity = Vector4(Mathf::NegativeInfinity);

Vector4& Vector4::Normalize()
{
	float magnitude = GetMagnitude();
	return *this /= magnitude;
}

Vector4& Vector4::Round()
{
	X = Mathf::Round(X);
	Y = Mathf::Round(Y);
	Z = Mathf::Round(Z);
	W = Mathf::Round(W);
	return *this;
}

Vector4& Vector4::Set(float x, float y, float z, float w)
{
	X = x;
	Y = y;
	Z = z;
	W = w;
	return *this;
}

bool Vector4::ExactlyEquals(const Vector4& other) { return X == other.X && Y == other.Y && Z == other.Z && W == other.W; }
bool Vector4::EssentiallyEquals(const Vector4& other) { return *this == other; }

float Vector4::GetMagnitude() const { return Mathf::Sqrt(GetSquaredMagnitude()); }
float Vector4::GetSquaredMagnitude() const { return X * X + Y * Y + Z * Z + W * W; }

Vector4 Vector4::Normalized() const
{
	float magnitude = GetMagnitude();
	return (*this) / magnitude;
}

Vector4 Vector4::Rounded() const
{
	return Vector4(Mathf::Round(X), Mathf::Round(Y), Mathf::Round(Z), Mathf::Round(W));
}

float Vector4::Dot(const Vector4& a, const Vector4& b)
{
	Vector4 scaled = a * b;
	return scaled.X + scaled.Y + scaled.Z + scaled.W;
}

float Vector4::Distance(const Vector4& a, const Vector4& b)
{
	Vector4 diff = Vector4(a.X - b.X, a.Y - b.Y, a.Z - b.Z, a.W - b.W);
	return diff.GetMagnitude();
}

float Vector4::SquaredDistance(const Vector4& a, const Vector4& b)
{
	Vector4 diff = Vector4(a.X - b.X, a.Y - b.Y, a.Z - b.Z, a.W - b.W);
	return diff.GetSquaredMagnitude();
}

Vector4 Vector4::Abs(const Vector4& vector)
{
	Vector4 abs = Vector4(Mathf::Abs(vector.X), Mathf::Abs(vector.Y), Mathf::Abs(vector.Z), Mathf::Abs(vector.W));
	return abs;
}

Vector4 Vector4::Sign(const Vector4& vector)
{
	Vector4 sign = Vector4(Mathf::Sign(vector.X), Mathf::Sign(vector.Y), Mathf::Sign(vector.Z), Mathf::Sign(vector.W));
	return sign;
}

Vector4 Vector4::ClampMagnitude(const Vector4& vector, float magnitude)
{
	float oldMagnitude = vector.GetMagnitude();
	return oldMagnitude < magnitude ?
		vector :
		vector * (magnitude / oldMagnitude);
}

Vector4 Vector4::Max(const Vector4& a, const Vector4& b)
{
	Vector4 max = Vector4(Mathf::Max(a.X, b.X), Mathf::Max(a.Y, b.Y), Mathf::Max(a.Z, b.Z), Mathf::Max(a.W, b.W));
	return max;
}

Vector4 Vector4::Min(const Vector4& a, const Vector4& b)
{
	Vector4 min = Vector4(Mathf::Min(a.X, b.X), Mathf::Min(a.Y, b.Y), Mathf::Min(a.Z, b.Z), Mathf::Min(a.W, b.W));
	return min;
}

Vector4 Vector4::Scale(const Vector4& a, const Vector4& b)
{
	Vector4 scaled = Vector4(a.X * b.X, a.Y * b.Y, a.Z * b.Z, a.W * b.W);
	return scaled;
}

Vector4 Vector4::Project(const Vector4& vector, const Vector4& normal)
{
	float c = Vector4::Dot(vector, normal) / normal.GetSquaredMagnitude();
	return normal * c;
}

Vector4 Vector4::Lerp(const Vector4& a, const Vector4& b, float t)
{
	return a + (b - a) * t;
}

Vector4 Vector4::LerpClamped(const Vector4& a, const Vector4& b, float t)
{
	t = Mathf::Clamp01(t);
	return Lerp(a, b, t);
}

Vector4 Vector4::MoveTowards(const Vector4& a, const Vector4& b, float distance)
{
	Vector4 dir = b - a;
	float magnitude = dir.GetMagnitude();

	if (magnitude <= distance) return b;
	return a + dir * (distance / magnitude);
}

bool Vector4::operator ==(const Vector4& other)
{
	return Mathf::ApproximatelyEquals(X, other.X)
		&& Mathf::ApproximatelyEquals(Y, other.Y)
		&& Mathf::ApproximatelyEquals(Z, other.Z)
		&& Mathf::ApproximatelyEquals(W, other.W);
}

Vector4 Vector4::operator *(const Matrix4x4& matrix) const
{
	return Vector4(
		matrix.Columns[0].X * X + matrix.Columns[0].Y * Y + matrix.Columns[0].Z * Z + matrix.Columns[0].W * W,
		matrix.Columns[1].X * X + matrix.Columns[1].Y * Y + matrix.Columns[1].Z * Z + matrix.Columns[1].W * W,
		matrix.Columns[2].X * X + matrix.Columns[2].Y * Y + matrix.Columns[2].Z * Z + matrix.Columns[2].W * W,
		matrix.Columns[3].X * X + matrix.Columns[3].Y * Y + matrix.Columns[3].Z * Z + matrix.Columns[3].W * W
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

Vector4& Vector4::operator *=(float scalar)
{
	*this = *this * scalar;
	return *this;
}

Vector4& Vector4::operator *=(const Vector4& vector)
{
	*this = *this * vector;
	return *this;
}

Vector4& Vector4::operator /=(float scalar)
{
	*this = *this / scalar;
	return *this;
}

Vector4& Vector4::operator /=(const Vector4& vector)
{
	*this = *this / vector;
	return *this;
}

float& Vector4::operator [](int index)
{
	return operator[]((Axis)index);
}

float Vector4::operator [](int index) const
{
	return operator[]((Axis)index);
}

float& Vector4::operator [](Axis axis)
{
	switch (axis)
	{
		case Axis::X: return X;
		case Axis::Y: return Y;
		case Axis::Z: return Z;
		case Axis::W:
		default: return W;
	}
}

float Vector4::operator [](Axis axis) const
{
	switch (axis)
	{
		case Axis::X: return X;
		case Axis::Y: return Y;
		case Axis::Z: return Z;
		case Axis::W:
		default: return W;
	}
}
