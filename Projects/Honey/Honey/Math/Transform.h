#pragma once

#include <Honey/Math/Vector/Vector3.h>
#include <Honey/Math/Matrix/Matrix4x4.h>
#include <Honey/Math/Quaternion.h>

namespace Honey {

	struct Transform {

		Math::Vector3 Position = Math::Vector3::Zero;
		Math::Quaternion Rotation = Math::Quaternion::Identity;
		Math::Vector3 Scale = Math::Vector3::One;

		Math::Matrix4x4 GetMatrix() const
		{ 
			return Math::Matrix4x4::Translate(Position) *
			Math::Matrix4x4::Rotate(Rotation) *
			Math::Matrix4x4::Scale(Scale);
		}

	};

}
