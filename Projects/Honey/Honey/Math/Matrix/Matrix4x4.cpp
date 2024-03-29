#include "Matrix4x4.h"

#include "Honey/Math/Quaternion.h"

using namespace Honey::Math;

Matrix4x4::Matrix4x4()
{
	// Set all the elements to 0
	for (UInt i = 0; i < 16; i++)
		elements[i] = 0;
}

Matrix4x4::Matrix4x4(Float diagonal) : Matrix4x4()
{
	// Set diagonal
	elements[0 + 0 * 4] = diagonal;
	elements[1 + 1 * 4] = diagonal;
	elements[2 + 2 * 4] = diagonal;
	elements[3 + 3 * 4] = diagonal;
}

/*
Matrix4x4::Matrix4x4(float* elements)
{
	memcpy(this->Elements, elements, 4 * 4 * sizeof(float));
}
*/

Matrix4x4::Matrix4x4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3)
{
	// Assign rows
	rows[0] = row0;
	rows[1] = row1;
	rows[2] = row2;
	rows[3] = row3;
}

Matrix4x4::Matrix4x4(const std::array<Vector4, 4>& rows)
{
	// Assign rows
	this->rows[0] = rows[0];
	this->rows[1] = rows[1];
	this->rows[2] = rows[2];
	this->rows[3] = rows[3];
}

const Matrix4x4& Matrix4x4::zero()
{
	static const Matrix4x4 zero = Matrix4x4();
	return zero;
}

const Matrix4x4& Matrix4x4::identity()
{
	static const Matrix4x4 identity = Matrix4x4(1.0f);
	return identity;
}

Matrix4x4& Matrix4x4::invert()
{
	*this = inverse();
	return *this;
}

void Matrix4x4::setColumn(UInt index, const Vector4& column)
{
	elements[index + 0 * 4] = column.x;
	elements[index + 1 * 4] = column.y;
	elements[index + 2 * 4] = column.z;
	elements[index + 3 * 4] = column.w;
}

Matrix4x4 Matrix4x4::inverse() const
{
	Matrix4x4 out;

	out.elements[0] = elements[5] * elements[10] * elements[15] -
		elements[5] * elements[11] * elements[14] -
		elements[9] * elements[6] * elements[15] +
		elements[9] * elements[7] * elements[14] +
		elements[13] * elements[6] * elements[11] -
		elements[13] * elements[7] * elements[10];

	out.elements[4] = -elements[4] * elements[10] * elements[15] +
		elements[4] * elements[11] * elements[14] +
		elements[8] * elements[6] * elements[15] -
		elements[8] * elements[7] * elements[14] -
		elements[12] * elements[6] * elements[11] +
		elements[12] * elements[7] * elements[10];

	out.elements[8] = elements[4] * elements[9] * elements[15] -
		elements[4] * elements[11] * elements[13] -
		elements[8] * elements[5] * elements[15] +
		elements[8] * elements[7] * elements[13] +
		elements[12] * elements[5] * elements[11] -
		elements[12] * elements[7] * elements[9];

	out.elements[12] = -elements[4] * elements[9] * elements[14] +
		elements[4] * elements[10] * elements[13] +
		elements[8] * elements[5] * elements[14] -
		elements[8] * elements[6] * elements[13] -
		elements[12] * elements[5] * elements[10] +
		elements[12] * elements[6] * elements[9];

	out.elements[1] = -elements[1] * elements[10] * elements[15] +
		elements[1] * elements[11] * elements[14] +
		elements[9] * elements[2] * elements[15] -
		elements[9] * elements[3] * elements[14] -
		elements[13] * elements[2] * elements[11] +
		elements[13] * elements[3] * elements[10];

	out.elements[5] = elements[0] * elements[10] * elements[15] -
		elements[0] * elements[11] * elements[14] -
		elements[8] * elements[2] * elements[15] +
		elements[8] * elements[3] * elements[14] +
		elements[12] * elements[2] * elements[11] -
		elements[12] * elements[3] * elements[10];

	out.elements[9] = -elements[0] * elements[9] * elements[15] +
		elements[0] * elements[11] * elements[13] +
		elements[8] * elements[1] * elements[15] -
		elements[8] * elements[3] * elements[13] -
		elements[12] * elements[1] * elements[11] +
		elements[12] * elements[3] * elements[9];

	out.elements[13] = elements[0] * elements[9] * elements[14] -
		elements[0] * elements[10] * elements[13] -
		elements[8] * elements[1] * elements[14] +
		elements[8] * elements[2] * elements[13] +
		elements[12] * elements[1] * elements[10] -
		elements[12] * elements[2] * elements[9];

	out.elements[2] = elements[1] * elements[6] * elements[15] -
		elements[1] * elements[7] * elements[14] -
		elements[5] * elements[2] * elements[15] +
		elements[5] * elements[3] * elements[14] +
		elements[13] * elements[2] * elements[7] -
		elements[13] * elements[3] * elements[6];

	out.elements[6] = -elements[0] * elements[6] * elements[15] +
		elements[0] * elements[7] * elements[14] +
		elements[4] * elements[2] * elements[15] -
		elements[4] * elements[3] * elements[14] -
		elements[12] * elements[2] * elements[7] +
		elements[12] * elements[3] * elements[6];

	out.elements[10] = elements[0] * elements[5] * elements[15] -
		elements[0] * elements[7] * elements[13] -
		elements[4] * elements[1] * elements[15] +
		elements[4] * elements[3] * elements[13] +
		elements[12] * elements[1] * elements[7] -
		elements[12] * elements[3] * elements[5];

	out.elements[14] = -elements[0] * elements[5] * elements[14] +
		elements[0] * elements[6] * elements[13] +
		elements[4] * elements[1] * elements[14] -
		elements[4] * elements[2] * elements[13] -
		elements[12] * elements[1] * elements[6] +
		elements[12] * elements[2] * elements[5];

	out.elements[3] = -elements[1] * elements[6] * elements[11] +
		elements[1] * elements[7] * elements[10] +
		elements[5] * elements[2] * elements[11] -
		elements[5] * elements[3] * elements[10] -
		elements[9] * elements[2] * elements[7] +
		elements[9] * elements[3] * elements[6];

	out.elements[7] = elements[0] * elements[6] * elements[11] -
		elements[0] * elements[7] * elements[10] -
		elements[4] * elements[2] * elements[11] +
		elements[4] * elements[3] * elements[10] +
		elements[8] * elements[2] * elements[7] -
		elements[8] * elements[3] * elements[6];

	out.elements[11] = -elements[0] * elements[5] * elements[11] +
		elements[0] * elements[7] * elements[9] +
		elements[4] * elements[1] * elements[11] -
		elements[4] * elements[3] * elements[9] -
		elements[8] * elements[1] * elements[7] +
		elements[8] * elements[3] * elements[5];

	out.elements[15] = elements[0] * elements[5] * elements[10] -
		elements[0] * elements[6] * elements[9] -
		elements[4] * elements[1] * elements[10] +
		elements[4] * elements[2] * elements[9] +
		elements[8] * elements[1] * elements[6] -
		elements[8] * elements[2] * elements[5];

	Float determinant = elements[0] * out.elements[0] +
		elements[1] * out.elements[4] + 
		elements[2] * out.elements[8] + 
		elements[3] * out.elements[12];

	determinant = 1.0f / determinant;

	for (UInt i = 0; i < 4 * 4; i++)
		out.elements[i] *= determinant;

	return out;
}

Vector4 Matrix4x4::getColumn(UInt index) const
{
	return Vector4(
		elements[index + 0 * 4],
		elements[index + 1 * 4],
		elements[index + 2 * 4],
		elements[index + 3 * 4]
	);
}

Matrix4x4 Matrix4x4::orthographic(Float left, Float right, Float bottom, Float top, Float zNear, Float zFar)
{
	Matrix4x4 result(1.0f);

	result.elements[0 + 0 * 4] = 2.0f / (right - left);
	result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
	result.elements[2 + 2 * 4] = 2.0f / (zNear - zFar);

	result.elements[3 + 0 * 4] = (left + right) / (left - right);
	result.elements[3 + 1 * 4] = (bottom + top) / (bottom - top);
	result.elements[3 + 2 * 4] = (zFar + zNear) / (zFar - zNear);

	return result;
}

Matrix4x4 Matrix4x4::perspective(Float fov, Float aspectRatio, Float zNear, Float zFar)
{
	Matrix4x4 result = zero();

	Float q = 1.0f / Mathf::tan(Mathf::degrees2Radians() * 0.5f * fov);

	Float a = q / aspectRatio;
	Float b = (zNear + zFar) / (zNear - zFar);
	Float c = (2.0f * zNear * zFar) / (zNear - zFar);

	result.elements[0 + 0 * 4] = a;
	result.elements[1 + 1 * 4] = q;
	result.elements[2 + 2 * 4] = b;
	result.elements[2 + 3 * 4] = -1.0f;
	result.elements[3 + 2 * 4] = c;

	return result;
}

Matrix4x4 Matrix4x4::lookAt(const Vector3& camera, const Vector3& object, const Vector3& up)
{
	Matrix4x4 result = identity();
	Vector3 f = (object - camera).normalize();
	Vector3 s = Vector3::cross(f, up.normalized());
	Vector3 u = Vector3::cross(s, f);

	result.elements[0 + 0 * 4] = s.x;
	result.elements[0 + 1 * 4] = s.y;
	result.elements[0 + 2 * 4] = s.z;

	result.elements[1 + 0 * 4] = u.x;
	result.elements[1 + 1 * 4] = u.y;
	result.elements[1 + 2 * 4] = u.z;

	result.elements[2 + 0 * 4] = -f.x;
	result.elements[2 + 1 * 4] = -f.y;
	result.elements[2 + 2 * 4] = -f.z;

	return result * translate(-camera);
}

Matrix4x4 Matrix4x4::translate(const Vector3& translation)
{
	Matrix4x4 result = identity();

	result.elements[3 + 0 * 4] = translation.x;
	result.elements[3 + 1 * 4] = translation.y;
	result.elements[3 + 2 * 4] = translation.z;

	return result;
}

Matrix4x4 Matrix4x4::rotate(Float angle, const Vector3& axis)
{
	Matrix4x4 result = identity();

	Float r = angle;
	Float c = Mathf::cos(r);
	Float s = Mathf::sin(r);
	Float omc = 1.0f - c;

	Float x = axis.x;
	Float y = axis.y;
	Float z = axis.z;

	result.elements[0 + 0 * 4] = x * x * omc + c;
	result.elements[0 + 1 * 4] = y * x * omc + z * s;
	result.elements[0 + 2 * 4] = x * z * omc - y * s;

	result.elements[1 + 0 * 4] = x * y * omc - z * s;
	result.elements[1 + 1 * 4] = y * y * omc + c;
	result.elements[1 + 2 * 4] = y * z * omc + x * s;

	result.elements[2 + 0 * 4] = x * z * omc + y * s;
	result.elements[2 + 1 * 4] = y * z * omc - x * s;
	result.elements[2 + 2 * 4] = z * z * omc + c;

	return result;
}

Matrix4x4 Matrix4x4::rotate(const Quaternion& quaternion)
{
	Matrix4x4 result = identity();

	Float qx, qy, qz, qw, qx2, qy2, qz2, qxqx2, qyqy2, qzqz2, qxqy2, qyqz2, qzqw2, qxqz2, qyqw2, qxqw2;

	qx = quaternion.x;
	qy = quaternion.y;
	qz = quaternion.z;
	qw = quaternion.w;

	qx2 = (qx + qx);
	qy2 = (qy + qy);
	qz2 = (qz + qz);

	qxqx2 = (qx * qx2);
	qxqy2 = (qx * qy2);
	qxqz2 = (qx * qz2);

	qxqw2 = (qw * qx2);
	qyqy2 = (qy * qy2);
	qyqz2 = (qy * qz2);

	qyqw2 = (qw * qy2);
	qzqz2 = (qz * qz2);
	qzqw2 = (qw * qz2);

	result.rows[0] = Vector4(((1.0f - qyqy2) - qzqz2), (qxqy2 - qzqw2), (qxqz2 + qyqw2), 0.0f);
	result.rows[1] = Vector4((qxqy2 + qzqw2), ((1.0f - qxqx2) - qzqz2), (qyqz2 - qxqw2), 0.0f);
	result.rows[2] = Vector4((qxqz2 - qyqw2), (qyqz2 + qxqw2), ((1.0f - qxqx2) - qyqy2), 0.0f);

	return result;
}

Matrix4x4 Matrix4x4::scale(const Vector3& scale)
{
	Matrix4x4 result(1.0f);

	result.elements[0 + 0 * 4] = scale.x;
	result.elements[1 + 1 * 4] = scale.y;
	result.elements[2 + 2 * 4] = scale.z;

	return result;
}

Matrix4x4 Matrix4x4::transpose(const Matrix4x4& matrix)
{
	return Matrix4x4(
		Vector4(matrix.rows[0].x, matrix.rows[1].x, matrix.rows[2].x, matrix.rows[3].x),
		Vector4(matrix.rows[0].y, matrix.rows[1].y, matrix.rows[2].y, matrix.rows[3].y),
		Vector4(matrix.rows[0].z, matrix.rows[1].z, matrix.rows[2].z, matrix.rows[3].z),
		Vector4(matrix.rows[0].w, matrix.rows[1].w, matrix.rows[2].w, matrix.rows[3].w)
	);
}

Matrix4x4 Matrix4x4::operator *(const Matrix4x4& other) const
{
	Matrix4x4 data;

	for (UInt row = 0; row < 4; row++)
	{
		for (UInt col = 0; col < 4; col++)
		{
			Float sum = 0.0f;

			for (UInt e = 0; e < 4; e++)
				sum += elements[e + row * 4] * other.elements[col + e * 4];

			data.elements[col + row * 4] = sum;
		}
	}

	return data;
}

Matrix4x4& Matrix4x4::operator *=(const Matrix4x4& other)
{
	*this = *this * other;
	return *this;
}
