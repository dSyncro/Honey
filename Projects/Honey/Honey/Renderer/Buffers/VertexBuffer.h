#pragma once

#include <cstdint>

#include <Honey/Core.h>
#include <Honey/Renderer/Buffers/BufferLayout.h>

namespace Honey {

	class VertexBuffer {

	public:

		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		static Reference<VertexBuffer> Create(uint32_t size);
		static Reference<VertexBuffer> Create(float* vertices, uint32_t size);
	};

}