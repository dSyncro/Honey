#pragma once

#include <Honey/Core/Assertion.h>

namespace Honey {

	enum class ShaderDataType : uint8_t {
		None = 0,
		Float,
		Vector2,
		Vector3,
		Vector4,
		Int,
		Vector2Int,
		Vector3Int,
		Vector4Int,
		Matrix3,
		Matrix4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:
			case ShaderDataType::Int:
				return 4;

			case ShaderDataType::Vector2:
			case ShaderDataType::Vector2Int:
				return 8;

			case ShaderDataType::Vector3:
			case ShaderDataType::Vector3Int:
				return 12;

			case ShaderDataType::Vector4:
			case ShaderDataType::Vector4Int:
				return 16;

			case ShaderDataType::Matrix3: return 36;

			case ShaderDataType::Matrix4: return 64;

			case ShaderDataType::Bool: return 1;

			default: break;
		}

		HNY_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

}
