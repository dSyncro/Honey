#pragma once

#include <Honey/Math/Vector/Vector3.h>
#include <Honey/Math/Vector/Vector4.h>
#include <Honey/Math/MathFunctions.h>

namespace Honey::Math {

	struct Quaternion;

	/**
	 * @brief Implementation of a Matrix4x4.
	 * That is a matrix made up of 4 rows and 4 columns.
	*/
	struct Matrix4x4
	{
		union
		{
			// [row + col * 4]
			Float elements[4 * 4];
			Vector4 rows[4];
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
		Matrix4x4(Float diagonal);

		// Unsafe: Matrix4x4(float* elements);

		/**
		 * @brief Construct Matrix4x4 using its rows.
		 * @param row0 -> First row.
		 * @param row1 -> Second row.
		 * @param row2 -> Third row.
		 * @param row3 -> Fourth row.
		 */
		Matrix4x4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3);

		/**
		 * @brief Construct Matrix4x4 using its rows.
		 * @param rows -> The rows.
		 */
		Matrix4x4(const std::array<Vector4, 4>& rows);

		// Shorthands

		/** @brief Zero Matrix4x4 */
		static const Matrix4x4& zero(); 

		/** @brief Identity Matrix4x4 */
		static const Matrix4x4& identity(); 

		// Methods

		/**
		 * @brief Invert this matrix.
		 */
		Matrix4x4& invert();

		/**
		 * @brief Set column at index.
		 * @param index -> Index of the column to change.
		 * @param column -> New value.
		 */
		void setColumn(UInt index, const Vector4& column);

		/**
		 * @brief Set position in a TRS matrix.
		 * @param position -> New position.
		 */
		void setPosition(const Vector3& position) { setColumn(3, Vector4(position, 1.0f)); }

		// Const Methods

		/**
		 * @brief Get inverse of this matrix.
		 */
		Matrix4x4 inverse() const;

		/**
		 * @brief Get column at index.
		 * @param index -> Index of the column to get.
		 * @return The column.
		*/
		Vector4 getColumn(UInt index) const;

		/**
		 * @brief Get position in a TRS matrix.
		 * @return The position.
		 */
		Vector3 getPosition() const { return Vector3(getColumn(3)); }

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
		static Matrix4x4 orthographic(Float left, Float right, Float bottom, Float top, Float zNear, Float zFar);

		/**
		 * @brief Generate perspective projection matrix.
		 * @param fov -> Field of View (in degrees).
		 * @param aspectRatio -> Aspect ratio.
		 * @param near -> Near clipping plane depth.
		 * @param far -> Far clipping plane depth.
		 * @return Perspective projection matrix.
		*/
		static Matrix4x4 perspective(Float fov, Float aspectRatio, Float zNear, Float zFar);

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
		static Matrix4x4 lookAt(const Vector3& source, const Vector3& target, const Vector3& up);

		/**
		 * @brief Create a translation matrix.
		 * @param translation -> The translation.
		 */
		static Matrix4x4 translate(const Vector3& translation);

		/**
		 * @brief Create a rotation matrix.
		 * @param angle -> Angle of the rotation (in radians).
		 * @param axis -> Axis of the rotation.
		 */
		static Matrix4x4 rotate(Float angle, const Vector3& axis);

		/**
		 * @brief Create a rotation matrix.
		 * @param quaternion -> Quaternion representing the rotation.
		 * @overload
		 */
		static Matrix4x4 rotate(const Quaternion& quaternion);

		/**
		 * @brief Create a scaling matrix.
		 * @param scale -> Scale of the matrix.
		 */
		static Matrix4x4 scale(const Vector3& scale);

		/**
		 * @brief Get transposed matrix (column exchanged with rows).
		 * @param matrix -> The matrix.
		 * @return The transpose of `matrix`.
		 */
		static Matrix4x4 transpose(const Matrix4x4& matrix);

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

		/**
		 * @brief Get matrix information in a nicely formatted string.
		 * @return Matrix information in string format.
		*/
		std::string toString() const 
		{
			std::stringstream stream;
			stream << "Row 1: " << elements[0] << ", " << elements[1] << ", " << elements[2] << ", " << elements[3] << '\n';
			stream << "Row 2: " << elements[4] << ", " << elements[5] << ", " << elements[6] << ", " << elements[7] << '\n';
			stream << "Row 3: " << elements[8] << ", " << elements[9] << ", " << elements[10] << ", " << elements[11] << '\n';
			stream << "Row 4: " << elements[12] << ", " << elements[13] << ", " << elements[14] << ", " << elements[15] << '\n';
			return stream.str();
		}
	};

}
