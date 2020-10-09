#pragma once

#include <Honey/Core.h>
#include <Honey/Core/IBindable.h>

namespace Honey {

	/**
	 * @brief Index buffer implementation.
	*/
	class IndexBuffer : public IBindable {

	public:

		virtual ~IndexBuffer() = default;

		/**
		 * @brief Get indices count.
		 * @return Indices count.
		*/
		virtual UInt getCount() const = 0;

		/**
		 * @brief Create a new index buffer.
		 * @param indices Indices.
		 * @param count Indices count.
		 * @return A new memory managed index buffer.
		*/
		static Reference<IndexBuffer> create(UInt* indices, UInt count);
	};

}
