#pragma once

#include <cmath>

#if !defined(HNY_BYTE_TYPE)
#	define HNY_BYTE_TYPE uint8_t
#endif

#if !defined(HNY_SHORT_TYPE)
#	define HNY_SHORT_TYPE int16_t
#endif

#if !defined(HNY_INT_TYPE)
#	define HNY_INT_TYPE int32_t
#endif

#if !defined(HNY_LONG_TYPE)
#	define HNY_LONG_TYPE int64_t
#endif

#if !defined(HNY_USHORT_TYPE)
#	define HNY_USHORT_TYPE uint16_t
#endif

#if !defined(HNY_UINT_TYPE)
#	define HNY_UINT_TYPE uint32_t
#endif

#if !defined(HNY_ULONG_TYPE)
#	define HNY_ULONG_TYPE uint64_t
#endif

#if !defined(HNY_FLOAT_TYPE)
#	define HNY_FLOAT_TYPE float_t
#endif

#if !defined(HNY_DOUBLE_TYPE)
#	define HNY_DOUBLE_TYPE double_t
#endif

namespace Honey {

	/** @brief Byte type. Usually 8-bit. */
	using Byte = HNY_BYTE_TYPE;

	/** @brief Short type. Usually 16-bit. */
	using Short = HNY_SHORT_TYPE;

	/** @brief Int type. Usually 32-bit. */
	using Int = HNY_INT_TYPE;

	/** @brief Long type. Usually 64-bit. */
	using Long = HNY_LONG_TYPE;

	/** @brief Unsigned short type. Usually 16-bit. */
	using UShort = HNY_USHORT_TYPE;

	/** @brief Unsigned int type. Usually 32-bit. */
	using UInt = HNY_UINT_TYPE;

	/** @brief Unsigned long type. Usually 64-bit. */
	using ULong = HNY_ULONG_TYPE;

	/** @brief Float type. Usually 32-bit. */
	using Float = HNY_FLOAT_TYPE;

	/** @brief Double type. Usually 64-bit. */
	using Double = HNY_DOUBLE_TYPE;

	/**
	 * @brief Enable type if it is unsigned.
	 * @tparam T The type.
	*/
	template <typename T>
	using EnableIfSigned = std::enable_if_t<std::is_signed_v<T>, T>;

	/**
	 * @brief Enable type if it is unsigned.
	 * @tparam T The type.
	*/
	template <typename T>
	using EnableIfUnsigned = std::enable_if_t<!std::is_signed_v<T>, T>;

	/**
	 * @brief Enable type if it is an integral.
	 * @tparam T The type.
	*/
	template <typename T>
	using EnableIfIntegral = std::enable_if_t<std::is_integral_v<T>, T>;

	/**
	 * @brief Enable type if it is a floating point type.
	 * @tparam T The type.
	*/
	template <typename T>
	using EnableIfFloatingPoint = std::enable_if_t<std::is_floating_point_v<T>, T>;

	/**
	 * @brief Enable type if it is a signed integer.
	 * @tparam T The type.
	*/
	template <typename T>
	using EnableIfSignedInt = std::enable_if_t<std::is_signed_v<T>&& std::is_integral_v<T>, T>;

	/**
	 * @brief Enable type if it is an unsigned integer.
	 * @tparam T The type.
	*/
	template <typename T>
	using EnableIfUnsignedInt = std::enable_if_t<!std::is_signed_v<T>&& std::is_integral_v<T>, T>;

	/**
	 * @brief Enable type if it is arithmetic.
	 * @tparam T The type.
	*/
	template <typename T>
	using EnableIfArithmetic = std::enable_if_t<std::is_arithmetic_v<T>, T>;
	
	/**
	 * @brief Number minimum value.
	 * @tparam T Number type.
	 * @return Minimum value.
	*/
	template <typename T>
	constexpr EnableIfArithmetic<T> minValue() noexcept { return std::numeric_limits<T>::min(); }

	/**
	 * @brief Number maximum value.
	 * @tparam T Number type.
	 * @return Maximum value.
	*/
	template <typename T>
	constexpr EnableIfArithmetic<T> maxValue() noexcept { return std::numeric_limits<T>::max(); }
}
