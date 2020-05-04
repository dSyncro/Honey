#include "MemoryTracking.h"

#include <cstdlib>
#include <new>
#include <vector>

#if HNY_MEMORY_TRACKING == 1

struct AllocationInfo {

	void* Reference;
	std::size_t Size;
	char* File;
	std::size_t Line;
	char* Function;

};

std::vector<AllocationInfo> allocations;

void* operator new (size_t size, char* file, std::size_t line, char* function)
{
	void* ptr = std::malloc(size);
	if (!ptr) throw std::bad_alloc();

	AllocationInfo track = { ptr, size, file, line, function };
	allocations.push_back(track);

	return ptr;
}

void operator delete(void* ptr, char* file, std::size_t line, char* function)
{
	std::vector<AllocationInfo>::const_iterator it;

	if (!allocations.size() == 0)
	{
		for (it = allocations.begin(); it != allocations.end(); it++)
		{
			if (it->Reference != ptr) continue;

			allocations.erase(it);
			break;
		}
	}

	std::free(ptr);
}

void operator delete(void* ptr)
{
	std::vector<AllocationInfo>::const_iterator it;

	if (!allocations.size() == 0)
	{
		for (it = allocations.begin(); it != allocations.end(); it++)
		{
			if (it->Reference != ptr) continue;

			allocations.erase(it);
			break;
		}
	}

	std::free(ptr);
}

#endif