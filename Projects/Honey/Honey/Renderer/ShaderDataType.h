#pragma once

#include <Honey/Core/Assertion.h>

namespace Honey {

	/**
	 * @brief Datatypes for shaders.
	*/
	enum class ShaderDataType : Byte {
		None = 0,
		Float, /** @brief Float type. */
		Vector2, /** @brief 2 components vector type. */
		Vector3, /** @brief 3 components vector type. */
		Vector4, /** @brief 4 components vector type. */
		Int, /** @brief Int type. */
		Vector2Int, /** @brief Int 2 components vector type. */
		Vector3Int, /** @brief Int 3 components vector type. */
		Vector4Int, /** @brief Int 4 components vector type. */
		Matrix3, /** @brief Matrix 3x3 type. */
		Matrix4, /** @brief Matrix 4x4 type. */
		Bool /** @brief Boolean type. */
	};

	/**
	 * @brief Get shader datatype size in byte.
	 * @param type The datatype.
	 * @return Size in byte of type.
	*/
	static UInt getShaderDataTypeSize(ShaderDataType type)
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
