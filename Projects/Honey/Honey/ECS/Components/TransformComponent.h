#pragma once

#include <Honey/Math/Math.h>

namespace Honey {

	/**
	 * @brief Entity transform.
	 * It defines translation, rotation and scale of
	 * a certain entity.
	*/
	struct TransformComponent {

		TransformComponent() 
			: position(Math::Vector3::Zero), rotation(Math::Quaternion::Identity), scale(Math::Vector3::One) {}

		~TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(
			const Math::Vector3& position, 
			const Math::Quaternion& rotation = Math::Quaternion::Identity,
			const Math::Vector3& scale = Math::Vector3::One
		) : position(position), rotation(rotation), scale(scale) { }

		Math::Vector3 position;
		Math::Quaternion rotation;
		Math::Vector3 scale;

		/**
		 * @brief Get the translation-rotation-scale matrix relative to this transformation.
		 * @return the TRS matrix relative to this transformation.
		*/
		Math::Matrix4x4 GetTRSMatrix() const
		{
			return Math::Matrix4x4::translate(position) *
				Math::Matrix4x4::rotate(rotation) *
				Math::Matrix4x4::scale(scale);
		}
	};

}
