#pragma once

#include <Honey/Math/Vector/Vector3.h>
#include <Honey/Math/Vector/Vector4.h>
#include <Honey/Math/MathFunctions.h>

namespace Honey::Math {

	struct Quaternion;

	struct Matrix4x4
	{
		union
		{
			// [row + col * 4]
			float Elements[4 * 4];
			Vector4 Rows[4];
		};

		// Constructors

		/**
		 * @brief Construct an Identity Matrix4x4
		 */
		Matrix4x4();

		/**
		 * @brief Construct Matrix4x4 with a single value.
		 * @param diagonal -> Diagonal value.
		 */
		Matrix4x4(float diagonal);

		// Unsafe: Matrix4x4(float* elements);

		/**
		 * @brief Construct Matrix4x4 using its rows.
		 * @param row0 -> First row.
		 * @param row1 -> Second row.
		 * @param row2 -> Third row.
		 * @param row3 -> Fourth row.
		 */
		Matrix4x4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3);

		static const Matrix4x4 Identity;

		Matrix4x4& Multiply(const Matrix4x4& other);
		Matrix4x4& operator *=(const Matrix4x4& other);
		friend Matrix4x4 operator *(Matrix4x4 left, const Matrix4x4& right);

		Vector3 Multiply(const Vector3& other) const;
		Vector4 Multiply(const Vector4& other) const;

		//Vector3 operator *(const Matrix4x4& left, const Vector3& right);
		//Vector4 operator *(const Matrix4x4& left, const Vector4& right);

		Matrix4x4& Invert();

		Vector4 GetColumn(int index) const;
		void SetColumn(unsigned int index, const Vector4& column);
		inline Vector3 GetPosition() const { return Vector3(GetColumn(3)); }
		inline void SetPosition(const Vector3& position) { SetColumn(3, Vector4(position, 1.0f)); }

		static Matrix4x4 Orthographic(float left, float right, float bottom, float top, float near, float far);
		static Matrix4x4 Perspective(float fov, float aspectRatio, float near, float far);
		static Matrix4x4 LookAt(const Vector3& camera, const Vector3& object, const Vector3& up);

		static Matrix4x4 Translate(const Vector3& translation);
		static Matrix4x4 Rotate(float angle, const Vector3& axis);
		static Matrix4x4 Rotate(const Quaternion& quat);
		static Matrix4x4 Scale(const Vector3& scale);
		static Matrix4x4 Invert(const Matrix4x4& matrix);

		static Matrix4x4 Transpose(const Matrix4x4& matrix);
	};

}