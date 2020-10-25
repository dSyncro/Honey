#pragma once

#define HNY_EXPAND(x) x
#define HNY_STRINGIFY(x) #x
#define HNY_CONCAT(a, b) a##b

#define HNY_PURE_STATIC(type) type() = delete; \
	type(const type&) = delete;               \
	type(type&&) = delete;                    \
	type& operator =(const type&) = delete;  \
	type& operator =(type&&) = delete

// Always inline
#if defined(HNY_COMPILER_GCC)
#	define HNY_ALWAYS_INLINE __attribute__((always_inline)) inline
#elif defined(HNY_COMPILER_MSC)
#	define HNY_ALWAYS_INLINE __forceinline
#else
#	define HNY_ALWAYS_INLINE inline
#endif

// Bitmasking
#define BIT(x) 1 << x

// Event Callback Binding
#define HNY_BIND_EVENT_CALLBACK(callback) [this](auto&&... args) -> decltype(auto) { return this->callback(std::forward<decltype(args)>(args)...); }
