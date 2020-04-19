#pragma once

#include <cstdint>

#include <Honey/Core.h>

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
			case Honey::ShaderDataType::Float:
			case Honey::ShaderDataType::Int:
				return 4;

			case Honey::ShaderDataType::Float2:
			case Honey::ShaderDataType::Int2:
				return 8;

			case Honey::ShaderDataType::Float3:
			case Honey::ShaderDataType::Int3:
				return 12;

			case Honey::ShaderDataType::Float4:
			case Honey::ShaderDataType::Int4:
				return 16;

			case Honey::ShaderDataType::Mat3: return 36;

			case Honey::ShaderDataType::Mat4: return 64;

			case Honey::ShaderDataType::Bool: return 1;

			default: break;
		}

		HNY_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

}