#pragma once

#include <Honey/Events/MouseEvents.h>
#include <Honey/Events/WindowEvents.h>
#include <Honey/Renderer/Camera/OrthographicCamera.h>

namespace Honey {

	/**
	 * @brief Engine orthographic camera controller.
	*/
	class OrthographicCameraController {

	public:

		/**
		 * @brief Construct OrthographicCameraController from its aspect ratio.
		 * @param aspectRatio The aspect ratio.
		*/
		OrthographicCameraController(Float aspectRatio);

		/**
		 * @brief Construct OrthographicCameraController from its width and height.
		 * @param width The width.
		 * @param height The height.
		*/
		OrthographicCameraController(Float width, Float height);

		/**
		 * @brief Called when controller gets updated.
		*/
		void onUpdate();

		/**
		 * @brief Called when controller gets an event.
		 * @param e The event.
		*/
		void onEvent(Event& e);

		/**
		 * @brief Resize controller.
		 * @param width New width.
		 * @param height New height.
		*/
		void resize(UInt width, UInt height);

		/**
		 * @brief Get underlying camera.
		 * @return The camera.
		*/
		OrthographicCamera& getCamera() { return _camera; }

		/**
		 * @brief Get underlying camera (const version).
		 * @return The camera.
		*/
		const OrthographicCamera& getCamera() const { return _camera; }

	private:

		Float _aspectRatio;
		Float _zoomLevel = 1.0f;

		OrthographicCamera _camera;

		Float _rotation = 0.0f;
		Math::Vector3 _position = Math::Vector3(0, 0, 0);

		Float _moveSpeed = 1.0f;
		Float _rotationSpeed = 25.0f;

		bool _doRotate = true;

		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onWindowResize(WindowResizeEvent& e);
	};

}
