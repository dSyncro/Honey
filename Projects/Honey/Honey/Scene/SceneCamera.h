#pragma once

#include <Honey/Renderer/Camera/Camera.h>

namespace Honey {

	class SceneCamera : public Camera {

	public:

		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOrthographic(float size, float nearClip, float farClip);
		void SetViewportSize(uint32_t width, uint32_t height);

	private:

		void RecalculateProjection();

	private:

		float _aspectRatio = 1.0f;

		float _orthoSize = 10.0f;
		float _orthoNear = -1.0f; float _orthoFar = 1.0f;
	};

}
