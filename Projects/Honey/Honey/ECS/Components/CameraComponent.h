#pragma once

#include <Honey/Scene/SceneCamera.h>

namespace Honey {

	struct CameraComponent {

		CameraComponent() = default;
		~CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;

		SceneCamera Camera;
		bool HasFixedAspectRatio = false;
	};

}
