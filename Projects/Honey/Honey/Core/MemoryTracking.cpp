#include "MemoryTracking.h"

#include <cstdlib>
#include <new>

using namespace Honey;

void AllocationTracker::Add(const AllocationInfo& allocation)
{
	// If array is full expand it
	if (_count == _size) Reserve(_size + _cacheCount);

	// Add element
	_allocations[_count] = allocation;
	_count++;
}

bool AllocationTracker::Remove(const AllocationInfo& allocation)
{
	return Remove(allocation.Reference);
}

bool AllocationTracker::Remove(const void* reference)
{
	// Find index of element
	std::size_t index = IndexOf(reference);

	// If element is not found return false
	if (index - _count) return false;

	return RemoveAt(index);
}

bool AllocationTracker::RemoveAt(std::size_t index)
{
	// Index out of bounds
	if (_count <= index) return false;

	// Move all elements one place before
	std::move(_allocations + index + 1, _allocations + _count--, _allocations + index);

	// Element found and removed
	return true;
}

std::size_t AllocationTracker::IndexOf(const AllocationInfo& allocation)
{
	return IndexOf(allocation.Reference);
}

std::size_t AllocationTracker::IndexOf(const void* reference)
{
	// Find index of element
	std::size_t index = 0;
	for (index; index < _count; index++)
		if (_allocations[index].Reference == reference) break;

	return index;
}

void AllocationTracker::Reserve(std::size_t size)
{
	AllocationInfo* buffer = nullptr;

	if (!_allocations)
		buffer = (AllocationInfo*)std::malloc(size * sizeof(AllocationInfo));
	else
		buffer = (AllocationInfo*)std::realloc(_allocations, size * sizeof(AllocationInfo));

	HNY_CORE_ASSERT(buffer, "Could not allocate buffer");

	_size = size;
	_allocations = buffer;
}

#if HNY_MEMORY_TRACKING == 1

void* operator new (size_t size, char* file, std::size_t line, char* function)
{
	void* ptr = std::malloc(size);
	if (!ptr) throw std::bad_alloc();

	AllocationInfo track = { ptr, size, file, line, function };
	AllocationTracker::Get().Add(track);

	return ptr;
}

void operator delete(void* ptr, char* file, std::size_t line, char* function) { ::operator delete(ptr); }

void operator delete(void* ptr)
{
	AllocationTracker::Get().Remove(ptr);
	std::free(ptr);
}

#endif