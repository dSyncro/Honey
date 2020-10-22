#pragma once

#include <Honey/Math/Math.h>

namespace Honey {

	/**
	 * @brief Entity transform.
	 * It defines translation, rotation and scale of
	 * a certain entity.
	*/
	struct TransformComponent {

		/**
		 * @brief Construct TransformComponent from its components.
		 * @param position Position.
		 * @param rotation Rotation.
		 * @param scale Scale.
		*/
		TransformComponent(
			const Math::Vector3& position = Math::Vector3::zero(), 
			const Math::Vector3& rotation = Math::Vector3::zero(),
			const Math::Vector3& scale = Math::Vector3::one()
		) : position(position), rotation(rotation), scale(scale) { }

		~TransformComponent() = default;

		TransformComponent(const TransformComponent&) = default;

		Math::Vector3 position; /** @brief Transform position. */
		Math::Vector3 rotation; /** @brief Transform rotation. */
		Math::Vector3 scale; /** @brief Transform scale. */

		/**
		 * @brief Get the translation-rotation-scale matrix relative to this transformation.
		 * @return the TRS matrix relative to this transformation.
		*/
		Math::Matrix4x4 GetTRSMatrix() const
		{
			return Math::Matrix4x4::translate(position) *
				Math::Matrix4x4::rotate(rotation.x, { 1, 0, 0 }) *
				Math::Matrix4x4::rotate(rotation.y, { 0, 1, 0 }) *
				Math::Matrix4x4::rotate(rotation.z, { 0, 0, 1 }) *
				Math::Matrix4x4::scale(scale);
		}
	};

}
