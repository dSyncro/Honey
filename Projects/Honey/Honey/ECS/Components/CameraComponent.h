#pragma once

#include <Honey/Renderer/Camera/Camera.h>

namespace Honey {

	struct CameraComponent {

		CameraComponent() : Camera(glm::mat4(1.0f)) {}
		~CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const glm::mat4& projectionMatrix)
			: Camera(projectionMatrix) { }

		Honey::Camera Camera;
	};

}
