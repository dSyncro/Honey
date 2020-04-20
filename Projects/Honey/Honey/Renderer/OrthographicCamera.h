#pragma once

#include <glm/glm.hpp>

namespace Honey {

	class OrthographicCamera {

	public:

		OrthographicCamera(float left, float right, float bottom, float top);

		inline const glm::vec3& GetPosition() const { return _position; }
		void SetPosition(const glm::vec3& position);

		inline float GetRotation() const { return _rotation; }
		void SetRotation(float rotation);

		inline const glm::mat4& GetViewMatrix() const { return _viewMatrix; }
		inline const glm::mat4& GetProjectionMatrix() const { return _projectionMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return _viewProjectionMatrix; }

	private:

		void RecalculateViewMatrix();

		glm::mat4 _viewMatrix;
		glm::mat4 _projectionMatrix;
		glm::mat4 _viewProjectionMatrix;

		glm::vec3 _position = { .0f, .0f, .0f };
		float _rotation = 0;
	};

}