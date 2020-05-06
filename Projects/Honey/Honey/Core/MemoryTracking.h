#pragma once

#include <cstddef>

#include "FunctionIdentification.h"
#include "Assertion.h"

namespace Honey {

	struct AllocationInfo {

		void* Reference;
		std::size_t Size;
		char* File;
		std::size_t Line;
		char* Function;

		bool operator ==(const AllocationInfo& other) { return Reference == other.Reference; }
		bool operator !=(const AllocationInfo& other) { return Reference != other.Reference; }

	};

	class AllocationTracker {

	public:

		AllocationTracker(const AllocationTracker&) = delete;
		AllocationTracker& operator =(const AllocationTracker&) = delete;

		static AllocationTracker& Get() 
		{ 
			static AllocationTracker instance = AllocationTracker();
			return instance; 
		}

		void Add(const AllocationInfo& allocation);
		bool Remove(const AllocationInfo& allocation);
		bool Remove(const void* reference);
		bool RemoveAt(std::size_t index);

		std::size_t IndexOf(const AllocationInfo& allocation);
		std::size_t IndexOf(const void* allocation);

		void Reserve(std::size_t size);

		std::size_t GetCount() const { return _count; }
		std::size_t GetSize() const { return _size; }
		std::size_t GetSizeInBytes() const { return _size * sizeof(AllocationInfo); }

		void SetCacheCount(std::size_t count) { _cacheCount = count; }
		std::size_t GetCacheCount() { return _cacheCount; }

		AllocationInfo& At(std::size_t index)
		{
			if (_count <= index) HNY_CORE_ASSERT(false, "Index out of bounds!");
			return _allocations[index];
		}

		const AllocationInfo& At(std::size_t index) const
		{
			if (_count <= index) HNY_CORE_ASSERT(false, "Index out of bounds!");
			return _allocations[index];
		}

		AllocationInfo& operator[](int index) { return At(index); }
		const AllocationInfo& operator[](int index) const { return At(index); }

		AllocationInfo& operator[](std::size_t index) { return At(index); }
		const AllocationInfo& operator[](std::size_t index) const { return At(index); }

	private:

		AllocationTracker()
		{
			Reserve(_cacheCount);
		}

		std::size_t _cacheCount = 16;

		std::size_t _count;
		std::size_t _size = 0;
		AllocationInfo* _allocations;
	};

}

#if defined(HNY_DEBUG)
#	define HNY_MEMORY_TRACKING 0
#endif

#if HNY_MEMORY_TRACKING == 1

extern void* operator new(size_t size, char* file, std::size_t line, char* function);
extern void operator delete(void* ptr, char* file, std::size_t line, char* function);
extern void operator delete(void* ptr);

#	define NEW new((char*)__FILE__, __LINE__, HNY_FUNCTION_SIGNATURE)
#else
#	define NEW new
#endif