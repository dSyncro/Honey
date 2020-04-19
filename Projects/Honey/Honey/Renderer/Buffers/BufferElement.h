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
			: Name(name), Type(type), IsNormalized(normalized), Size(ShaderDataTypeSize(type)), Offset(0)
		{

		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case Honey::ShaderDataType::Bool:
				case Honey::ShaderDataType::Float:
				case Honey::ShaderDataType::Int:
					return 1;

				case Honey::ShaderDataType::Float2:
				case Honey::ShaderDataType::Int2:
					return 2;

				case Honey::ShaderDataType::Float3:
				case Honey::ShaderDataType::Int3:
					return 3;

				case Honey::ShaderDataType::Float4:
				case Honey::ShaderDataType::Int4:
					return 4;

				case Honey::ShaderDataType::Mat3:
					return 9;

				case Honey::ShaderDataType::Mat4:
					return 16;
			}

			HNY_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

}