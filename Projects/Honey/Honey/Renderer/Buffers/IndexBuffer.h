#pragma once

#include <Honey/Core/IBindable.h>
#include <Honey/Core/MemoryManagement.h>

namespace Honey {

	class IndexBuffer : public IBindable {

	public:

		virtual ~IndexBuffer() = default;

		virtual uint32_t GetCount() const = 0;

		static Reference<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};

}
