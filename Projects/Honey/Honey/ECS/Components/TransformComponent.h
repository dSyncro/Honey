#pragma once

#include <Honey/Math/Math.h>

namespace Honey {

	struct TransformComponent {

		TransformComponent() 
			: Position(Math::Vector3::Zero), Rotation(Math::Quaternion::Identity), Scale(Math::Vector3::One) {}

		~TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(
			const Math::Vector3& position, 
			const Math::Quaternion& rotation = Math::Quaternion::Identity,
			const Math::Vector3& scale = Math::Vector3::One
		) : Position(position), Rotation(rotation), Scale(scale) { }

		Math::Vector3 Position;
		Math::Quaternion Rotation;
		Math::Vector3 Scale;

		Math::Matrix4x4 GetTRSMatrix() const
		{
			return Math::Matrix4x4::Translate(Position) *
				Math::Matrix4x4::Rotate(Rotation) *
				Math::Matrix4x4::Scale(Scale);
		}
	};

}
