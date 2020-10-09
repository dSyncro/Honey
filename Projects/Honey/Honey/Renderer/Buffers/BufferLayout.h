#pragma once

#include <string>
#include <vector>

#include "BufferElement.h"

namespace Honey {

	/**
	 * @brief Vertex buffer layout.
	*/
	class BufferLayout {

	public:

		BufferLayout() = default;

		/**
		 * @brief Construct BufferLayout from initializer list.
		 * @param elements List of elements.
		*/
		BufferLayout(const std::initializer_list<BufferElement>& elements) : _elements(elements)
		{
			calculateOffsetsAndStride();
		}

		/**
		 * @brief Get layout stride.
		 * @return Layout stride.
		*/
		UInt getStride() const { return _stride; }

		/**
		 * @brief Get layout elements.
		 * @return Layout elements.
		*/
		const std::vector<BufferElement>& getElements() const { return _elements; }

		// Iterators

		std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
		std::vector<BufferElement>::iterator end() { return _elements.end(); }
		std::vector<BufferElement>::reverse_iterator rbegin() { return _elements.rbegin(); }
		std::vector<BufferElement>::reverse_iterator rend() { return _elements.rend(); }

		std::vector<BufferElement>::const_iterator begin() const { return _elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return _elements.end(); }
		std::vector<BufferElement>::const_reverse_iterator rbegin() const { return _elements.rbegin(); }
		std::vector<BufferElement>::const_reverse_iterator rend() const { return _elements.rend(); }

	private:

		void calculateOffsetsAndStride()
		{
			_stride = 0;
			for (BufferElement& e : _elements)
			{
				e.offset = _stride;
				_stride += e.size;
			}
		}

		std::vector<BufferElement> _elements;
		UInt _stride;
	};

}
