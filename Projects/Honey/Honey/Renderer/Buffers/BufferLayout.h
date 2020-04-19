#pragma once

#include <string>
#include <vector>

#include "BufferElement.h"

namespace Honey {

	class BufferLayout {

	public:

		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferElement>& elements) : _elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return _stride; }
		inline const std::vector<BufferElement>& GetElements() const { return _elements; }

		inline std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
		inline std::vector<BufferElement>::iterator end() { return _elements.end(); }
		inline std::vector<BufferElement>::reverse_iterator rbegin() { return _elements.rbegin(); }
		inline std::vector<BufferElement>::reverse_iterator rend() { return _elements.rend(); }

		inline std::vector<BufferElement>::const_iterator begin() const { return _elements.begin(); }
		inline std::vector<BufferElement>::const_iterator end() const { return _elements.end(); }
		inline std::vector<BufferElement>::const_reverse_iterator rbegin() const { return _elements.rbegin(); }
		inline std::vector<BufferElement>::const_reverse_iterator rend() const { return _elements.rend(); }

	private:

		void CalculateOffsetsAndStride()
		{
			_stride = 0;
			for (BufferElement& e : _elements)
			{
				e.Offset = _stride;
				_stride += e.Size;
			}
		}

		std::vector<BufferElement> _elements;
		uint32_t _stride;
	};

}