#pragma once

#include <glm/glm.hpp>

#include <Honey/Math/MathFunctions.h>

namespace Honey::Math {

	struct Vector3;
	struct Vector4;

	/** 
	 * @struct Vector2
	 * @brief 2-Components Vector of `float` type. 
	 */
	struct Vector2 {

		/** @brief  Axes of the Vector. */
		enum class Axis {
			X = 0, //!< @brief X Axis
			Y = 1  //!< @brief Y Axis
		};

		// Constructors

		/**
		 * @brief Construct Vector2 from a single value.
		 * @param value -> The value used to initialize all components of the vector. (optional)
		 */
		Vector2(float value = 0.0f) : X(value), Y(value) {}

		/**
		 * @brief Construct Vector2 from two values.
		 * @param x -> X component of the vector.
		 * @param y -> Y component of the vector.
		 * @overload
		 */
		Vector2(float x, float y) : X(x), Y(y) {}

		/**
		 * @brief Construct Vector2 from a Vector3.
		 * @param vector -> The vector.
		 * @overload
		 */
		explicit Vector2(const Vector3& vector);

		/**
		 * @brief Construct Vector2 from a Vector4.
		 * @param vector -> The vector.
		 * @overload
		 */
		explicit Vector2(const Vector4& vector);

		// Shorthands
		
		static const Vector2 Left;             //!< @brief Vector2(-1.0f, 0.0f)
		static const Vector2 Right;            //!< @brief Vector2(1.0f, 0.0f)
		static const Vector2 Up;               //!< @brief Vector2(0.0f, 1.0f)
		static const Vector2 Down;             //!< @brief Vector2(0.0f, -1.0f)
		static const Vector2 Zero;             //!< @brief Vector2(0.0f, 0.0f)
		static const Vector2 One;              //!< @brief Vector2(1.0f, 1.0f)
		static const Vector2 Infinity;         //!< @brief Vector2(+Infinity, +Infinity)
		static const Vector2 NegativeInfinity; //!< @brief Vector2(-Infinity, -Infinity)

		// Cast operators

		// Temporary
		operator glm::vec2() const { return glm::vec2(X, Y); }

		/** @brief Convert this vector to a Vector3. */
		explicit operator Vector3() const;
		/** @brief Convert this vector to a Vector4. */
		explicit operator Vector4() const;

		// Methods

		/**
		 * @brief Normalize this vector.
		 * It means that the vector will be converted to a vector
		 * with same direction and magnitude equal to one.
		 */
		Vector2& Normalize();

		/** @brief Round the components of this vector. */
		Vector2& Round();

		/**
		 * @brief Set the components of this vector.
		 * @param x -> `X` component of the vector.
		 * @param y -> `Y` component of the vector.
		 */
		Vector2& Set(float x, float y);

		/**
		 * @brief Check if all the components of the vector are exactly equal to the ones of another vector.
		 * @param other -> The vector to check equality with.
		 */
		bool ExactlyEquals(const Vector2& other);

		/**
		 * @brief Check if all the components of the vector are almost equal to the ones of another vector.
		 * @param other -> The vector to check equality with.
		 */
		bool EssentiallyEquals(const Vector2& other);

		// Const methods

		/** @brief Get the magnitude of this vector */
		float GetMagnitude() const;

		/** @brief Get the squared magnitude of this vector */
		float GetSquaredMagnitude() const;

		/**
		 * @brief Get a normalized copy of this vector
		 * @see Normalize
		 */
		Vector2 Normalized() const;

		/** @brief Get a copy of this vector with all its components rounded */
		Vector2 Rounded() const;

		// Static Methods

		/**
		 * @brief Get the angle between two vectors.
		 * @param a -> first vector.
		 * @param b -> second vector.
		 * @return Angle in radians between `a` and `b`.
		 */
		static float Angle(const Vector2& a, const Vector2& b);

		/**
		 * @brief Get the dot product of two vectors.
		 * @param a -> first vector.
		 * @param b -> second vector.
		 * @return `a` dot `b`.
		 */
		static float Dot(const Vector2& a, const Vector2& b);

		/**
		 * @brief Get the distance between two vectors.
		 * @param a -> first vector.
		 * @param b -> second vector.
		 * @return Distance between `a` and `b`.
		 */
		static float Distance(const Vector2& a, const Vector2& b);

		/**
		 * @brief Get the squared distance between two vectors.
		 * @param a -> first vector.
		 * @param b -> second vector.
		 * @return Squared distance between `a` and `b`.
		 */
		static float SquaredDistance(const Vector2& a, const Vector2& b);

		/**
		 * @brief Get the abs vector of `vector`.
		 * @param vector -> the vector.
		 * @return A vector made up of the absolute value of each component of `vector`.
		 */
		static Vector2 Abs(const Vector2& vector);

		/**
		 * @brief Get the signed vector of `vector`.
		 * @param vector -> the vector.
		 * @return A vector representing the sign vector of `vector`.
		 */
		static Vector2 Sign(const Vector2& vector);

		/**
		 * @brief Get perpendicular vector.
		 * @param vector -> the vector.
		 * @return The vector perpendicular (clockwise) to `vector`.
		 */
		static Vector2 PerpendicularClockwise(const Vector2& vector);

		/**
		 * @brief Get perpendicular vector.
		 * @param vector -> the vector.
		 * @return The vector perpendicular (counter-clockwise) to `vector`.
		 */
		static Vector2 PerpendicularCounterClockwise(const Vector2& vector);

		/**
		 * @brief Get a copy of the vector clamped to a certain magnitude.
		 * @param vector -> the vector.
		 * @param magnitude -> new magnitude.
		 * @return A copy of `vector` with magnitude clamped to `magnitude`.
		 */
		static Vector2 ClampMagnitude(const Vector2& vector, float magnitude);

		/**
		 * @brief Get a copy of the vector rotated by a certain angle.
		 * @param vector -> the vector.
		 * @param angle -> rotation angle (in radians).
		 * @return A copy of `vector` rotated by `angle`.
		 */
		static Vector2 Rotate(const Vector2& vector, float angle);

		/**
		 * @brief Get the maximum vector.
		 * @param a -> first vector.
		 * @param b -> second vector.
		 * @return A vector made up of the maximum of each component of two vectors.
		 */
		static Vector2 Max(const Vector2& a, const Vector2& b);

		/**
		 * @brief Get the minimum vector.
		 * @param a -> first vector.
		 * @param b -> second vector.
		 * @return A vector made up of the minimum of each component of two vectors.
		 */
		static Vector2 Min(const Vector2& a, const Vector2& b);

		/**
		 * @brief Get scaled vector.
		 * @param a -> first vector.
		 * @param b -> second vector.
		 * @return A vector made up of the component-wise multiplication of `a` and `b`.
		 */
		static Vector2 Scale(const Vector2& a, const Vector2& b);

		/**
		 * @brief Reflect vector over a normal.
		 * @param vector -> the vector to reflect.
		 * @param normal -> normal vector.
		 * @return The vector reflected over the normal.
		 */
		static Vector2 Reflect(const Vector2& vector, const Vector2& normal);

		/**
		 * @brief Linear interpolate from a to b.
		 * @param a -> first vector.
		 * @param b -> second vector.
		 * @param t -> percentage of the interpolation (0.0f corresponds to  `a` and 1.0f corresponds to `b`).
		 * @return A vector at `t` between `a` and `b`.
		 */
		static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);

		/**
		 * @brief Linear interpolate from a to b, t is clamped in range 0 to 1.
		 * @param a -> first vector.
		 * @param b -> second vector.
		 * @param t -> percentage of the interpolation (0.0f corresponds to  `a` and 1.0f corresponds to `b`).
		 * @return A vector at `t` between `a` and `b`.
		 */
		static Vector2 LerpClamped(const Vector2& a, const Vector2& b, float t);

		/**
		 * @brief Move by distance from a vector to another.
		 * @param a -> first vector.
		 * @param b -> second vector.
		 * @param distance -> maximum distance of translation.
		 * @return A vector moved by `distance` from `a` trying to reach `b`.
		 */
		static Vector2 MoveTowards(const Vector2& a, const Vector2& b, float distance);

		// Comparison operators

		/**
		 * @brief Check if two vectors are approximately equal to each other.
		 * @param other -> The vector to perform the comparison with.
		 */
		bool operator ==(const Vector2& other) { return Mathf::ApproximatelyEquals(X, other.X) && Mathf::ApproximatelyEquals(Y, other.Y); }

		/**
		 * @brief Check if two vectors are not approximately equal to each other.
		 * @param other -> The vector to perform the comparison with.
		 */
		bool operator !=(const Vector2& other) { return !(*this == other); }

		// Arithmetic operators 
		
		/**
		 * @brief Identity operator.
		 * @return A copy of this vector.
		 */
		Vector2 operator +() const { return *this; }

		/**
		 * @brief Negation operator.
		 * @return A copy of this vector with inverted sign.
		 */
		Vector2 operator -() const { return Vector2(-X, -Y); }

		/**
		 * @brief Add operator.
		 * @param other -> The other vector.
		 * @return this vector + `other`.
		 */
		Vector2 operator +(const Vector2& other) const { return Vector2(X + other.X, Y + other.Y); }

		/**
		 * @brief Subtract operator.
		 * @param other -> The other vector.
		 * @return this vector - `other`.
		 */
		Vector2 operator -(const Vector2& other) const { return Vector2(X * other.X, Y - other.Y); }

		/**
		 * @brief Multiply operator.
		 * @param scalar -> The multiplier.
		 * @return this vector * `scalar`.
		 */
		Vector2 operator *(float scalar) const { return Vector2(X * scalar, Y * scalar); }

		/**
		 * @brief Multiply operator.
		 * @param other -> The other vector.
		 * @return this vector * `other`.
		 * @overload
		 */
		Vector2 operator *(const Vector2& other) const { return Vector2(X * other.X, Y * other.Y); }

		/**
		 * @brief Divide operator.
		 * @param scalar -> The divider.
		 * @return this vector / `scalar`.
		 */
		Vector2 operator /(float scalar) const { return Vector2(X / scalar, Y / scalar); }

		/**
		 * @brief Divide operator.
		 * @param other -> The other vector.
		 * @return this vector / `other`.
		 */
		Vector2 operator /(const Vector2& other) const { return Vector2(X / other.X, Y / other.Y); }

		// Assignment operators

		/**
		 * @brief Add-self operator.
		 * @param other -> The other vector.
		 * @return this vector += `other`.
		 */
		Vector2& operator +=(const Vector2& other);

		/**
		 * @brief Subtract-self operator.
		 * @param other -> The other vector.
		 * @return this vector -= `other`.
		 */
		Vector2& operator -=(const Vector2& other);

		/**
		 * @brief Multiply-self operator.
		 * @param scalar -> The multiplier.
		 * @return this vector *= `scalar`.
		 */
		Vector2& operator *=(float scalar);

		/**
		 * @brief Multiply-self operator.
		 * @param other -> The other vector.
		 * @return this vector *= `other`.
		 * @overload
		 */
		Vector2& operator *=(const Vector2& vector);

		/**
		 * @brief Divide-self operator.
		 * @param scalar -> The divider.
		 * @return this vector /= `scalar`.
		 */
		Vector2& operator /=(float scalar);

		/**
		 * @brief Divide-self operator.
		 * @param other -> The other vector.
		 * @return this vector /= `other`.
		 * @overload
		 */
		Vector2& operator /=(const Vector2& vector);

		// Subscript operator

		/**
		 * @brief Get component by index.
		 * @param index -> Index of component.
		 * @return Component at index. (returns last component if overflown)
		 */
		float operator [](int index) { return (Axis)index == Axis::X ? X : Y; }

		/**
		 * @brief Get component by index. (const version)
		 * @param index -> Index of component.
		 * @return Component at `index`. (returns last component if overflown)
		 */
		float operator [](int index) const { return (Axis)index == Axis::X ? X : Y; }

		/**
		 * @brief Get component by Axis.
		 * @param axis -> Axis of component.
		 * @return Component at `axis`;
		 */
		float operator [](Axis axis) { return axis == Axis::X ? X : Y; }

		/**
		 * @brief Get component by Axis. (const version)
		 * @param axis -> Axis of component.
		 * @return Component at `axis`;
		 */
		float operator [](Axis axis) const { return axis == Axis::X ? X : Y; }

		float X; //!< @brief Y component
		float Y; //!< @brief Y component
	};

	/**
	 * @brief Multiply operator.
	 * @param scalar -> Number to multiply `vector` with.
	 * @param vector -> The vector.
	 * @return scalar * vector [equivalent to vector * scalar]. (used when the scalar preceides the vector)
	 */
	static Vector2 operator *(float scalar, const Vector2& vector) { return vector * scalar; }

}