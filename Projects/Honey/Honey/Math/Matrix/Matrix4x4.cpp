#include "Matrix4x4.h"

#include "Honey/Math/Quaternion.h"

using namespace Honey::Math;

Matrix4x4::Matrix4x4()
{
	memset(Elements, 0, 4 * 4 * sizeof(float));
}

Matrix4x4::Matrix4x4(float diagonal) : Matrix4x4()
{
	Elements[0 + 0 * 4] = diagonal;
	Elements[1 + 1 * 4] = diagonal;
	Elements[2 + 2 * 4] = diagonal;
	Elements[3 + 3 * 4] = diagonal;
}

/*
Matrix4x4::Matrix4x4(float* elements)
{
	memcpy(this->Elements, elements, 4 * 4 * sizeof(float));
}
*/

Matrix4x4::Matrix4x4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3)
{
	Rows[0] = row0;
	Rows[1] = row1;
	Rows[2] = row2;
	Rows[3] = row3;
}

const Matrix4x4 Matrix4x4::Zero     = Matrix4x4();
const Matrix4x4 Matrix4x4::Identity = Matrix4x4(1.0f);

Matrix4x4& Matrix4x4::Invert()
{
	*this = Inverse();
	return *this;
}

void Matrix4x4::SetColumn(unsigned int index, const Vector4& column)
{
	Elements[index + 0 * 4] = column.X;
	Elements[index + 1 * 4] = column.Y;
	Elements[index + 2 * 4] = column.Z;
	Elements[index + 3 * 4] = column.W;
}

Matrix4x4 Matrix4x4::Inverse() const
{
	Matrix4x4 out;

	out.Elements[0] = Elements[5] * Elements[10] * Elements[15] -
		Elements[5] * Elements[11] * Elements[14] -
		Elements[9] * Elements[6] * Elements[15] +
		Elements[9] * Elements[7] * Elements[14] +
		Elements[13] * Elements[6] * Elements[11] -
		Elements[13] * Elements[7] * Elements[10];

	out.Elements[4] = -Elements[4] * Elements[10] * Elements[15] +
		Elements[4] * Elements[11] * Elements[14] +
		Elements[8] * Elements[6] * Elements[15] -
		Elements[8] * Elements[7] * Elements[14] -
		Elements[12] * Elements[6] * Elements[11] +
		Elements[12] * Elements[7] * Elements[10];

	out.Elements[8] = Elements[4] * Elements[9] * Elements[15] -
		Elements[4] * Elements[11] * Elements[13] -
		Elements[8] * Elements[5] * Elements[15] +
		Elements[8] * Elements[7] * Elements[13] +
		Elements[12] * Elements[5] * Elements[11] -
		Elements[12] * Elements[7] * Elements[9];

	out.Elements[12] = -Elements[4] * Elements[9] * Elements[14] +
		Elements[4] * Elements[10] * Elements[13] +
		Elements[8] * Elements[5] * Elements[14] -
		Elements[8] * Elements[6] * Elements[13] -
		Elements[12] * Elements[5] * Elements[10] +
		Elements[12] * Elements[6] * Elements[9];

	out.Elements[1] = -Elements[1] * Elements[10] * Elements[15] +
		Elements[1] * Elements[11] * Elements[14] +
		Elements[9] * Elements[2] * Elements[15] -
		Elements[9] * Elements[3] * Elements[14] -
		Elements[13] * Elements[2] * Elements[11] +
		Elements[13] * Elements[3] * Elements[10];

	out.Elements[5] = Elements[0] * Elements[10] * Elements[15] -
		Elements[0] * Elements[11] * Elements[14] -
		Elements[8] * Elements[2] * Elements[15] +
		Elements[8] * Elements[3] * Elements[14] +
		Elements[12] * Elements[2] * Elements[11] -
		Elements[12] * Elements[3] * Elements[10];

	out.Elements[9] = -Elements[0] * Elements[9] * Elements[15] +
		Elements[0] * Elements[11] * Elements[13] +
		Elements[8] * Elements[1] * Elements[15] -
		Elements[8] * Elements[3] * Elements[13] -
		Elements[12] * Elements[1] * Elements[11] +
		Elements[12] * Elements[3] * Elements[9];

	out.Elements[13] = Elements[0] * Elements[9] * Elements[14] -
		Elements[0] * Elements[10] * Elements[13] -
		Elements[8] * Elements[1] * Elements[14] +
		Elements[8] * Elements[2] * Elements[13] +
		Elements[12] * Elements[1] * Elements[10] -
		Elements[12] * Elements[2] * Elements[9];

	out.Elements[2] = Elements[1] * Elements[6] * Elements[15] -
		Elements[1] * Elements[7] * Elements[14] -
		Elements[5] * Elements[2] * Elements[15] +
		Elements[5] * Elements[3] * Elements[14] +
		Elements[13] * Elements[2] * Elements[7] -
		Elements[13] * Elements[3] * Elements[6];

	out.Elements[6] = -Elements[0] * Elements[6] * Elements[15] +
		Elements[0] * Elements[7] * Elements[14] +
		Elements[4] * Elements[2] * Elements[15] -
		Elements[4] * Elements[3] * Elements[14] -
		Elements[12] * Elements[2] * Elements[7] +
		Elements[12] * Elements[3] * Elements[6];

	out.Elements[10] = Elements[0] * Elements[5] * Elements[15] -
		Elements[0] * Elements[7] * Elements[13] -
		Elements[4] * Elements[1] * Elements[15] +
		Elements[4] * Elements[3] * Elements[13] +
		Elements[12] * Elements[1] * Elements[7] -
		Elements[12] * Elements[3] * Elements[5];

	out.Elements[14] = -Elements[0] * Elements[5] * Elements[14] +
		Elements[0] * Elements[6] * Elements[13] +
		Elements[4] * Elements[1] * Elements[14] -
		Elements[4] * Elements[2] * Elements[13] -
		Elements[12] * Elements[1] * Elements[6] +
		Elements[12] * Elements[2] * Elements[5];

	out.Elements[3] = -Elements[1] * Elements[6] * Elements[11] +
		Elements[1] * Elements[7] * Elements[10] +
		Elements[5] * Elements[2] * Elements[11] -
		Elements[5] * Elements[3] * Elements[10] -
		Elements[9] * Elements[2] * Elements[7] +
		Elements[9] * Elements[3] * Elements[6];

	out.Elements[7] = Elements[0] * Elements[6] * Elements[11] -
		Elements[0] * Elements[7] * Elements[10] -
		Elements[4] * Elements[2] * Elements[11] +
		Elements[4] * Elements[3] * Elements[10] +
		Elements[8] * Elements[2] * Elements[7] -
		Elements[8] * Elements[3] * Elements[6];

	out.Elements[11] = -Elements[0] * Elements[5] * Elements[11] +
		Elements[0] * Elements[7] * Elements[9] +
		Elements[4] * Elements[1] * Elements[11] -
		Elements[4] * Elements[3] * Elements[9] -
		Elements[8] * Elements[1] * Elements[7] +
		Elements[8] * Elements[3] * Elements[5];

	out.Elements[15] = Elements[0] * Elements[5] * Elements[10] -
		Elements[0] * Elements[6] * Elements[9] -
		Elements[4] * Elements[1] * Elements[10] +
		Elements[4] * Elements[2] * Elements[9] +
		Elements[8] * Elements[1] * Elements[6] -
		Elements[8] * Elements[2] * Elements[5];

	float determinant = Elements[0] * out.Elements[0] + 
		Elements[1] * out.Elements[4] + 
		Elements[2] * out.Elements[8] + 
		Elements[3] * out.Elements[12];

	determinant = 1.0f / determinant;

	for (int i = 0; i < 4 * 4; i++)
		out.Elements[i] *= determinant;

	return out;
}

Vector4 Matrix4x4::GetColumn(int index) const
{
	return Vector4(Elements[index + 0 * 4], Elements[index + 1 * 4], Elements[index + 2 * 4], Elements[index + 3 * 4]);
}

Matrix4x4 Matrix4x4::Orthographic(float left, float right, float bottom, float top, float near, float far)
{
	Matrix4x4 result(1.0f);

	result.Elements[0 + 0 * 4] = 2.0f / (right - left);
	result.Elements[1 + 1 * 4] = 2.0f / (top - bottom);
	result.Elements[2 + 2 * 4] = 2.0f / (near - far);

	result.Elements[3 + 0 * 4] = (left + right) / (left - right);
	result.Elements[3 + 1 * 4] = (bottom + top) / (bottom - top);
	result.Elements[3 + 2 * 4] = (far + near) / (far - near);

	return result;
}

Matrix4x4 Matrix4x4::Perspective(float fov, float aspectRatio, float near, float far)
{
	Matrix4x4 result = Identity;

	float q = 1.0f / Mathf::Tan(Mathf::Degrees2Radians * 0.5f * fov);

	float a = q / aspectRatio;
	float b = (near + far) / (near - far);
	float c = (2.0f * near * far) / (near - far);

	result.Elements[0 + 0 * 4] = a;
	result.Elements[1 + 1 * 4] = q;
	result.Elements[2 + 2 * 4] = b;
	result.Elements[2 + 3 * 4] = -1.0f;
	result.Elements[3 + 2 * 4] = c;

	return result;
}

Matrix4x4 Matrix4x4::LookAt(const Vector3& camera, const Vector3& object, const Vector3& up)
{
	Matrix4x4 result = Identity;
	Vector3 f = (object - camera).Normalize();
	Vector3 s = Vector3::Cross(f, up.Normalized());
	Vector3 u = Vector3::Cross(s, f);

	result.Elements[0 + 0 * 4] = s.X;
	result.Elements[0 + 1 * 4] = s.Y;
	result.Elements[0 + 2 * 4] = s.Z;

	result.Elements[1 + 0 * 4] = u.X;
	result.Elements[1 + 1 * 4] = u.Y;
	result.Elements[1 + 2 * 4] = u.Z;

	result.Elements[2 + 0 * 4] = -f.X;
	result.Elements[2 + 1 * 4] = -f.Y;
	result.Elements[2 + 2 * 4] = -f.Z;

	return result * Translate(-camera);
}

Matrix4x4 Matrix4x4::Translate(const Vector3& translation)
{
	Matrix4x4 result = Identity;

	result.Elements[3 + 0 * 4] = translation.X;
	result.Elements[3 + 1 * 4] = translation.Y;
	result.Elements[3 + 2 * 4] = translation.Z;

	return result;
}

Matrix4x4 Matrix4x4::Rotate(float angle, const Vector3& axis)
{
	Matrix4x4 result = Identity;

	float r = angle;
	float c = Mathf::Cos(r);
	float s = Mathf::Sin(r);
	float omc = 1.0f - c;

	float x = axis.X;
	float y = axis.Y;
	float z = axis.Z;

	result.Elements[0 + 0 * 4] = x * x * omc + c;
	result.Elements[0 + 1 * 4] = y * x * omc + z * s;
	result.Elements[0 + 2 * 4] = x * z * omc - y * s;

	result.Elements[1 + 0 * 4] = x * y * omc - z * s;
	result.Elements[1 + 1 * 4] = y * y * omc + c;
	result.Elements[1 + 2 * 4] = y * z * omc + x * s;

	result.Elements[2 + 0 * 4] = x * z * omc + y * s;
	result.Elements[2 + 1 * 4] = y * z * omc - x * s;
	result.Elements[2 + 2 * 4] = z * z * omc + c;

	return result;
}

Matrix4x4 Matrix4x4::Rotate(const Quaternion& quaternion)
{
	Matrix4x4 result = Identity;

	float qx, qy, qz, qw, qx2, qy2, qz2, qxqx2, qyqy2, qzqz2, qxqy2, qyqz2, qzqw2, qxqz2, qyqw2, qxqw2;

	qx = quaternion.X;
	qy = quaternion.Y;
	qz = quaternion.Z;
	qw = quaternion.W;

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

	result.Rows[0] = Vector4(((1.0f - qyqy2) - qzqz2), (qxqy2 - qzqw2), (qxqz2 + qyqw2), 0.0f);
	result.Rows[1] = Vector4((qxqy2 + qzqw2), ((1.0f - qxqx2) - qzqz2), (qyqz2 - qxqw2), 0.0f);
	result.Rows[2] = Vector4((qxqz2 - qyqw2), (qyqz2 + qxqw2), ((1.0f - qxqx2) - qyqy2), 0.0f);

	return result;
}

Matrix4x4 Matrix4x4::Scale(const Vector3& scale)
{
	Matrix4x4 result(1.0f);

	result.Elements[0 + 0 * 4] = scale.X;
	result.Elements[1 + 1 * 4] = scale.Y;
	result.Elements[2 + 2 * 4] = scale.Z;

	return result;
}

Matrix4x4 Matrix4x4::Transpose(const Matrix4x4& matrix)
{
	return Matrix4x4(
		Vector4(matrix.Rows[0].X, matrix.Rows[1].X, matrix.Rows[2].X, matrix.Rows[3].X),
		Vector4(matrix.Rows[0].Y, matrix.Rows[1].Y, matrix.Rows[2].Y, matrix.Rows[3].Y),
		Vector4(matrix.Rows[0].Z, matrix.Rows[1].Z, matrix.Rows[2].Z, matrix.Rows[3].Z),
		Vector4(matrix.Rows[0].W, matrix.Rows[1].W, matrix.Rows[2].W, matrix.Rows[3].W)
	);
}

Matrix4x4 Matrix4x4::operator *(const Matrix4x4& other) const
{
	Matrix4x4 data;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			float sum = 0.0f;

			for (int e = 0; e < 4; e++)
				sum += Elements[e + row * 4] * other.Elements[col + e * 4];

			data.Elements[col + row * 4] = sum;
		}
	}

	return data;
}

Matrix4x4& Matrix4x4::operator *=(const Matrix4x4& other)
{
	*this = *this * other;
	return *this;
}