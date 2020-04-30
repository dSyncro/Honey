#pragma once

#include <Honey/Events/MouseEvents.h>
#include <Honey/Events/WindowEvents.h>
#include <Honey/Renderer/Camera/OrthographicCamera.h>

namespace Honey {

	class OrthographicCameraController {

	public:

		OrthographicCameraController(float aspectRatio);
		OrthographicCameraController(float width, float height);

		void OnUpdate();
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return _camera; }
		const OrthographicCamera& GetCamera() const { return _camera; }

	private:

		float _aspectRatio;
		float _zoomLevel = 1.0f;

		OrthographicCamera _camera;

		float _rotation = 0.0f;
		glm::vec3 _position = glm::vec3(0, 0, 0);

		float _moveSpeed = 1.0f;
		float _rotationSpeed = 1.0f;

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};

}