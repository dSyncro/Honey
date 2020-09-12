#pragma once

#include <string>

#include <Honey/Renderer/ShaderDataType.h>

namespace Honey {

	struct BufferElement {

		ShaderDataType Type;
		std::string Name;
		bool IsNormalized;
		uint32_t Size;
		uint32_t Offset;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), IsNormalized(normalized), Size(ShaderDataTypeSize(type)), Offset(0) { }

		uint32_t GetComponentCount() const
		{
			switch (Type)
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
