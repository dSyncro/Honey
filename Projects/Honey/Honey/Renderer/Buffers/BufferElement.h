#pragma once

#include <string>

#include <Honey/Renderer/ShaderDataType.h>

namespace Honey {

	/**
	 * @brief Vertex buffer layout element.
	*/
	struct BufferElement {

		ShaderDataType type;
		std::string name;
		bool isNormalized;
		UInt size;
		UInt offset;

		BufferElement() = default;

		/**
		 * @brief Construct BufferElement.
		 * @param type Datatype.
		 * @param name Element name.
		 * @param isNormalized Is data meant to be normalized?
		*/
		BufferElement(ShaderDataType type, const std::string& name, bool isNormalized = false)
			: name(name), type(type), isNormalized(isNormalized), size(getShaderDataTypeSize(type)), offset(0) { }

		/**
		 * @brief Get component count from data type.
		 * @return Component count.
		*/
		UInt getComponentCount() const
		{
			switch (type)
			{
				case ShaderDataType::Bool:
				case ShaderDataType::Float:
				case ShaderDataType::Int:
					return 1;

				case ShaderDataType::Vector2:
				case ShaderDataType::Vector2Int:
					return 2;

				case ShaderDataType::Vector3:
				case ShaderDataType::Vector3Int:
					return 3;

				case ShaderDataType::Vector4:
				case ShaderDataType::Vector4Int:
					return 4;

				case ShaderDataType::Matrix3:
					return 9;

				case ShaderDataType::Matrix4:
					return 16;
			}

			HNY_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

}
