/**
 * @file MemoryManagement.h
 * @brief Manage memory easily.
 */

#pragma once

#include <memory>

namespace Honey {

	template<typename T>
	using Reference = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Reference<T> CreateReference(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Unique = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Unique<T> CreateUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

}