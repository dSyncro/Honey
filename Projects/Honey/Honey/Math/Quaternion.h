#pragma once

#include <Honey/Core.h>
#include <Honey/Math/Vector/Vector3.h>
#include <Honey/Math/Vector/Vector4.h>

namespace Honey::Math {

	/**
	 * @struct Quaternion
	 * @brief Quaternions represent rotations.
	 * They do not suffer from gimbal lock.
	 */
	struct Quaternion
	{
		// Data

		union {
			struct { float X, Y, Z, W; };
			float Components[4]; //!< @brief Components of the Quaternion.
		};

		// Shorthands

		static const Quaternion Identity; //!< @brief Quaternion(0.0f, 0.0f, 0.0f, 1.0f)

		/**
		 * @brief Construct an Identity quaternion.
		 */
		Quaternion();

		/**
		 * @brief Construct quaternion from a single value.
		 * @param value -> The value.
		 */
		Quaternion(float value);

		/**
		 * @brief Constuct quaternion from a Vector3 and a `W` value.
		 * @param xyz -> Vector3 representing `X`, `Y` and `Z` components.
		 * @param w -> `W` component.
		 */
		Quaternion(const Vector3& xyz, float w);

		/**
		 * @brief Construct quaternion from a Vector4
		 * @param vector -> Vector4 representing components.
		 */
		Quaternion(const Vector4& vector);

		/**
		 * @brief Construct quaternion from components.
		 * @param x -> `X` component.
		 * @param y -> `Y` component.
		 * @param z -> `Z` component.
		 * @param w -> `W` component.
		 */
		Quaternion(float x, float y, float z, float w);

		/**
		 * @brief Construct quaternion from another quaternion.
		 * @param quaternion -> Quaternion to copy.
		 */
		Quaternion(const Quaternion& quaternion);

		// Methods

		/**
		 * @brief Normalize this quaternion.
		 * @return Reference to this quaternion after being normalized.
		 */
		Quaternion& Normalize();

		/**
		 * @brief Set X, Y and Z components from Vector3.
		 * @param vector -> Vector3 representing `X`, `Y` and `Z` components.
		 * @return Reference to this quaternion with components updated.
		 */
		Quaternion& SetXYZ(const Vector3& vector);

		/**
		 * @brief Set X, Y and Z components.
		 * @param x -> `X` component.
		 * @param y -> `Y` component.
		 * @param z -> `Z` component.
		 * @return Reference to this quaternion with components updated.
		 * @ overload
		 */
		Quaternion& SetXYZ(float x, float y, float z);

		/**
		 * @brief Set components of this quaternion from Vector4.
		 * @param vector -> Vector4 representing new components.
		 * @return Reference to this quaternion with components updated.
		 */
		Quaternion& Set(const Vector4& vector);

		/**
		 * @brief Set components of this quaternion.
		 * @param x -> `X` component.
		 * @param y -> `Y` component.
		 * @param z -> `Z` component.
		 * @param w -> `W` component.
		 * @return Reference to this quaternion with components updated.
		 * @overload
		 */
		Quaternion& Set(float x, float y, float z, float w);

		// Const methods

		/**
		 * @brief Get conjugate quaternion.
		 */
		Quaternion Conjugate() const;
		
		/**
		 * @brief Get `X`, `Y` and `Z` of this quaternion.
		 * @return A Vector3 representing `X`, `Y` and `Z` components.
		 */
		HNY_ALWAYS_INLINE Vector3 GetXYZ() const { return Vector3(X, Y, Z); }

		Vector3 GetAxis() const;

		/**
		 * @brief Converts quaternion to euler angles.
		 * @return A Vector3 representing euler angles rotation.
		 */
		Vector3 ToEulerAngles() const;

		/**
		 * @brief Get magnitude of this quaternion.
		 * @return Magnitude of this quaternion.
		 */
		float GetMagnitude() const;

		/**
		 * @brief Get squared magnitude of this quaternion.
		 * @return Squared magnitude of this quaternion.
		 */
		float GetSquaredMagnitude() const;

		/**
		 * @brief Get a normalized copy of this quaternion.
		 * @return A normalized copy of this quaternion.
		*/
		Quaternion Normalized() const;

		// Static Methods

		/**
		 * @brief Get quaternion from euler angles.
		 * @param angles -> Vector3 representing euler rotation.
		 * @return Quaternion corresponding to `angles`.
		 */
		static Quaternion FromEulerAngles(const Vector3& angles);	

		/**
		 * @brief Create rotation from `a` to `b`.
		 * @param a -> First vector.
		 * @param b -> Second vector.
		 * @return Quaternion representing the rotation from `a` to `b`
		 */
		static Quaternion FromToRotation(const Vector3& a, const Vector3& b);

		/**
		 * @brief Get rotation of a unit vector rotate by a certain angle.
		 * @param radians -> Angle in radians.
		 * @param unitVec -> Unit vector.
		 * @return Quaternion representing rotation of `unitVec` rotated by `radians`.
		*/
		static Quaternion UnitVectorRotation(float radians, const Vector3& unitVec);

		/**
		 * @brief Rotate Vector3 by a quaternion.
		 * @param quaternion -> Rotation quaternion.
		 * @param vector -> Vector3 to rotate.
		 * @return Rotated `vector`.
		 */
		static Vector3 Rotate(const Quaternion& quaternion, const Vector3& vector);

		/**
		 * @brief Get rotation on X axis.
		 * @param radians -> Angle in radians.
		 * @return Quaternion representing rotation of X axis by `radians`.
		 */
		static Quaternion RotationX(float radians);

		/**
		 * @brief Get rotation on Y axis.
		 * @param radians -> Angle in radians.
		 * @return Quaternion representing rotation of Y axis by `radians`.
		 */
		static Quaternion RotationY(float radians);

		/**
		 * @brief Get rotation on Z axis.
		 * @param radians -> Angle in radians.
		 * @return Quaternion representing rotation of Z axis by `radians`.
		 */
		static Quaternion RotationZ(float radians);

		/**
		 * @brief Dot product of two quaternions.
		 * @param a -> First quaternion.
		 * @param b -> Second quaternion.
		 * @return The dot product of `a` and `b`.
		 */
		static float Dot(const Quaternion& a, const Quaternion& b);

		// Arithmetic operators

		/**
		 * @brief Negation operator.
		 * @return A copy of this quaternion with opposite components.
		 */
		Quaternion operator -() const;

		/**
		 * @brief Add operator.
		 * @param quaternion -> Quaternion to add.
		 * @return A quaternion made up of the sum of each components.
		 */
		Quaternion operator +(const Quaternion& quaternion) const;

		/**
		 * @brief Subtract operator
		 * @param quaternion -> Quaternion to subtract
		 * @return A quaternion made up of the difference of each components.
		 */
		Quaternion operator -(const Quaternion& quaternion) const;

		/**
		 * @brief Multiply operator.
		 * @param quaternion -> Quaternion to multiply by.
		 * @return Result of multiplication between the two quaternions.
		 */
		Quaternion operator *(const Quaternion& quaternion) const;

		/**
		 * @brief Multiply operator.
		 * @param scalar -> Value to multiply by.
		 * @return Result of multiplication between the quaternion and `scalar`.
		 */
		Quaternion operator *(float scalar) const;

		/**
		 * @brief Division operator.
		 * @param scalar -> Value to divide by.
		 * @return Result of division between the quaternion and `scalar`.
		 */
		Quaternion operator /(float scalar) const;

		// Assignment operators

		/**
		 * @brief Assignment operator.
		 * @param quaternion -> Quaternion to assign.
		 * @return Reference to this quaternion.
		 */
		Quaternion& Quaternion::operator =(const Quaternion& quaternion)
		{
			Set(quaternion.X, quaternion.Y, quaternion.Z, quaternion.W);
			return *this;
		}

		/**
		 * @brief Add-self operator.
		 * @param quaternion -> Quaternion to add.
		 * @return this + `quaternion`.
		 */
		Quaternion& operator +=(const Quaternion& quaternion)
		{
			*this = *this + quaternion;
			return *this;
		}

		/**
		 * @brief Subtract-self operator.
		 * @param quaternion -> Quaternion to subtract.
		 * @return this - `quaternion`.
		 */
		Quaternion& operator -=(const Quaternion& quaternion)
		{
			*this = *this - quaternion;
			return *this;
		}

		/**
		 * @brief Multiply-self operator.
		 * @param quaternion -> Quaternion to multiply by.
		 * @return this * `quaternion`.
		 */
		Quaternion& operator *=(const Quaternion& quaternion)
		{
			*this = *this * quaternion;
			return *this;
		}

		/**
		 * @brief Multiply-self operator.
		 * @param scalar -> Value to multiply by.
		 * @return this * `scalar`.
		 * @overload
		 */
		Quaternion& operator *=(float scalar)
		{
			*this = *this * scalar;
			return *this;
		}

		/**
		 * @brief Divide-self operator.
		 * @param scalar -> Value to divide by.
		 * @return this / `scalar`.
		 */
		Quaternion& operator/=(float scalar)
		{
			*this = *this / scalar;
			return *this;
		}

		// Comparison operators

		/**
		 * @brief Check if two quaternions are approximately equal to each other.
		 * @param other -> The quaternion to perform the comparison with.
		 */
		bool operator ==(const Quaternion& other) const;

		/**
		 * @brief Check if two quaternions are not approximately equal to each other.
		 * @param other -> The quaternion to perform the comparison with.
		 */
		bool operator !=(const Quaternion& other) const;

		// Subscript operator

		/**
		 * @brief Get component at `index`.
		 * @param index -> Index of component.
		 */
		float operator[](int index);

		/**
		 * @brief Get component at `index`. (const version)
		 * @param index -> Index of component.
		 * @oveload
		 */
		float operator[](int index) const;

		/**
		 * @brief Get component at `index`.
		 * @param index -> Index of component.
		 * @oveload
		 */
		float operator[](unsigned int index);

		/**
		 * @brief Get component at `index`. (const version)
		 * @param index -> Index of component.
		 * @oveload
		 */
		float operator[](unsigned int index) const;

	};
}