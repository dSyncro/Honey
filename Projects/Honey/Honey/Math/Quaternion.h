#pragma once

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

		/**
		 * @brief Assignment operator.
		 * @param quaternion -> Quaternion to assign.
		 * @return Reference to this quaternion.
		 */
		Quaternion& operator =(const Quaternion& quaternion);

		// Methods

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
		
		Vector3 GetXYZ() const;
		Vector3 GetAxis() const;
		Vector3 ToEulerAngles() const;

		Quaternion operator +(const Quaternion& Quaternion) const;
		Quaternion operator -(const Quaternion& Quaternion) const;
		Quaternion operator *(const Quaternion& Quaternion) const;

		Quaternion operator *(float scalar) const;
		Quaternion operator /(float scalar) const;

		float operator[](int idx) const;

		Quaternion& operator +=(const Quaternion& Quaternion)
		{
			*this = *this + Quaternion;
			return *this;
		}

		Quaternion& operator -=(const Quaternion& Quaternion)
		{
			*this = *this - Quaternion;
			return *this;
		}

		Quaternion& operator *=(const Quaternion& Quaternion)
		{
			*this = *this * Quaternion;
			return *this;
		}

		Quaternion& operator *=(float scalar)
		{
			*this = *this * scalar;
			return *this;
		}

		Quaternion& operator/=(float scalar)
		{
			*this = *this / scalar;
			return *this;
		}

		Quaternion operator -() const;

		bool operator ==(const Quaternion& quaternion) const;
		bool operator !=(const Quaternion& quaternion) const;
		static Quaternion FromEulerAngles(const Vector3& angles);

		static Vector3 Rotate(const Quaternion& quat, const Vector3& vec);

		static Quaternion Rotation(const Vector3& unitVec0, const Vector3& unitVec1);
		static Quaternion Rotation(float radians, const Vector3& unitVec);

		static Quaternion RotationX(float radians)
		{
			float angle = radians * 0.5f;
			return Quaternion(sin(angle), 0.0f, 0.0f, cos(angle));
		}

		static Quaternion RotationY(float radians)
		{
			float angle = radians * 0.5f;
			return Quaternion(0.0f, sin(angle), 0.0f, cos(angle));
		}

		static Quaternion RotationZ(float radians)
		{
			float angle = radians * 0.5f;
			return Quaternion(0.0f, 0.0f, sin(angle), cos(angle));
		}

		float Dot(const Quaternion& other) const;
		Quaternion Conjugate() const;

	};
}