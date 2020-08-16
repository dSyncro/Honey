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
			Vector4 Columns[4];
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

		// Shorthands

		static const Matrix4x4 Zero; //!< @brief Zero 4x4 Matrix
		static const Matrix4x4 Identity; //!< @brief Identity 4x4 Matrix

		// Methods

		/**
		 * @brief Invert this matrix.
		 */
		Matrix4x4& Invert();

		/**
		 * @brief Set column at index.
		 * @param index -> Index of the column to change.
		 * @param column -> New value.
		 */
		void SetColumn(unsigned int index, const Vector4& column);

		/**
		 * @brief Set position in a TRS matrix.
		 * @param position -> New position.
		 */
		inline void SetPosition(const Vector3& position) { SetColumn(3, Vector4(position, 1.0f)); }

		// Const Methods

		/**
		 * @brief Get inverse of this matrix.
		 */
		Matrix4x4 Inverse() const;

		/**
		 * @brief Get column at index.
		 * @param index -> Index of column.
		 */
		Vector4 GetColumn(int index) const;

		/**
		 * @brief Get position in a TRS matrix.
		 * @return The position.
		 */
		inline Vector3 GetPosition() const { return Vector3(GetColumn(3)); }

		// Static Methods

		/**
		 * @brief Generate orthographic projection matrix.
		 * @param left -> Left side x-coordinate.
		 * @param right -> Right side x-coordinate.
		 * @param bottom -> Bottom y-coordinate.
		 * @param top -> Top y-coordinate.
		 * @param near -> Near clipping plane depth.
		 * @param far -> Far clipping plane depth.
		 * @return Orthograpic projection matrix.
		 */
		static Matrix4x4 Orthographic(float left, float right, float bottom, float top, float zNear, float zFar);

		/**
		 * @brief Generate perspective projection matrix.
		 * @param fov -> Field of View (in degrees).
		 * @param aspectRatio -> Aspect ratio.
		 * @param near -> Near clipping plane depth.
		 * @param far -> Far clipping plane depth.
		 * @return Perspective projection matrix.
		*/
		static Matrix4x4 Perspective(float fov, float aspectRatio, float zNear, float zFar);

		/**
		 * @brief Create a "look at" matrix.
		 * Given a source point, a target point, and an up vector, 
		 * computes a transformation matrix that corresponds to a camera viewing the target from the source, 
		 * such that the right-hand vector is perpendicular to the up vector.
		 * @param source -> Source position.
		 * @param target -> Target position.
		 * @param up -> Up direction.
		 * @return 
		 */
		static Matrix4x4 LookAt(const Vector3& source, const Vector3& target, const Vector3& up);

		/**
		 * @brief Create a translation matrix.
		 * @param translation -> The translation.
		 */
		static Matrix4x4 Translate(const Vector3& translation);

		/**
		 * @brief Create a rotation matrix.
		 * @param angle -> Angle of the rotation (in radians).
		 * @param axis -> Axis of the rotation.
		 */
		static Matrix4x4 Rotate(float angle, const Vector3& axis);

		/**
		 * @brief Create a rotation matrix.
		 * @param quaternion -> Quaternion representing the rotation.
		 * @overload
		 */
		static Matrix4x4 Rotate(const Quaternion& quaternion);

		/**
		 * @brief Create a scaling matrix.
		 * @param scale -> Scale of the matrix.
		 */
		static Matrix4x4 Scale(const Vector3& scale);

		/**
		 * @brief Get transposed matrix (column exchanged with rows).
		 * @param matrix -> The matrix.
		 * @return The transpose of `matrix`.
		 */
		static Matrix4x4 Transpose(const Matrix4x4& matrix);

		// Arithmetic operators

		Vector3 operator *(const Vector3& vector) const { return vector * (*this); }
		Vector4 operator *(const Vector4& vector) const { return vector * (*this); }

		/**
		 * @brief Multiply operator.
		 * @param other -> Matrix to multiply by.
		 */
		Matrix4x4 operator *(const Matrix4x4& other) const;

		// Assignment operators

		/**
		 * @brief Multiply-Self operator.
		 * @param other -> Matrix to multiply this one by.
		 */
		Matrix4x4& operator *=(const Matrix4x4& other);

		std::string ToString() const 
		{
			std::stringstream stream;
			stream << "Row 1: " << Elements[0] << ", " << Elements[1] << ", " << Elements[2] << ", " << Elements[3] << '\n';
			stream << "Row 2: " << Elements[4] << ", " << Elements[5] << ", " << Elements[6] << ", " << Elements[7] << '\n';
			stream << "Row 3: " << Elements[8] << ", " << Elements[9] << ", " << Elements[10] << ", " << Elements[11] << '\n';
			stream << "Row 4: " << Elements[12] << ", " << Elements[13] << ", " << Elements[14] << ", " << Elements[15] << '\n';
			return stream.str();
		}
	};

}
