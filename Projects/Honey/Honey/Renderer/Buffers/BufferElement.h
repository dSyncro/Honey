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

				case ShaderDataType::Float2:
				case ShaderDataType::Int2:
					return 2;

				case ShaderDataType::Float3:
				case ShaderDataType::Int3:
					return 3;

				case ShaderDataType::Float4:
				case ShaderDataType::Int4:
					return 4;

				case ShaderDataType::Mat3:
					return 9;

				case ShaderDataType::Mat4:
					return 16;
			}

			HNY_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

}
