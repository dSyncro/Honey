#pragma once

#include <Honey/Core/Assertion.h>

namespace Honey {

	enum class ShaderDataType : uint8_t {
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Int2,
		Int3,
		Int4,
		Mat3,
		Mat4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:
			case ShaderDataType::Int:
				return 4;

			case ShaderDataType::Float2:
			case ShaderDataType::Int2:
				return 8;

			case ShaderDataType::Float3:
			case ShaderDataType::Int3:
				return 12;

			case ShaderDataType::Float4:
			case ShaderDataType::Int4:
				return 16;

			case ShaderDataType::Mat3: return 36;

			case ShaderDataType::Mat4: return 64;

			case ShaderDataType::Bool: return 1;

			default: break;
		}

		HNY_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

}
