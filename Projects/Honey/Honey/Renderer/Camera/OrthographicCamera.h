#pragma once

#include <Honey/Math/Math.h>

namespace Honey {

	/**
	 * @brief Engine orthographic camera.
	*/
	class OrthographicCamera {

	public:

		/**
		 * @brief Construct camera from projection components.
		 * @param left Projection left.
		 * @param right Projection right.
		 * @param bottom Projection bottom.
		 * @param top Projection top.
		*/
		OrthographicCamera(Float left, Float right, Float bottom, Float top);

		/**
		 * @brief Set new projection.
		 * @param left Projection left.
		 * @param right Projection right.
		 * @param bottom Projection bottom.
		 * @param top Projection top.
		*/
		void setProjection(Float left, Float right, Float bottom, Float top);

		/**
		 * @brief Get camera position.
		 * @return Camera position.
		*/
		const Math::Vector3& getPosition() const { return _position; }

		/**
		 * @brief Set camera position.
		 * @param position New position.
		*/
		void setPosition(const Math::Vector3& position);

		/**
		 * @brief Get camera rotation.
		 * @return Camera rotation.
		*/
		Float getRotation() const { return _rotation; }

		/**
		 * @brief Set camera rotation.
		 * @param rotation New rotation.
		*/
		void setRotation(Float rotation);

		/**
		 * @brief Get camera view matrix.
		 * @return Camera projection matrix.
		*/
		const Math::Matrix4x4& getViewMatrix() const { return _viewMatrix; }

		/**
		 * @brief Get camera view matrix.
		 * @return Camera projection matrix.
		*/
		const Math::Matrix4x4& getProjectionMatrix() const { return _projectionMatrix; }

		/**
		 * @brief Get camera view-projection matrix.
		 * @return Camera view-projection matrix.
		*/
		const Math::Matrix4x4& getViewProjectionMatrix() const { return _viewProjectionMatrix; }

	private:

		void recalculateViewMatrix();

		Math::Matrix4x4 _viewMatrix;
		Math::Matrix4x4 _projectionMatrix;
		Math::Matrix4x4 _viewProjectionMatrix;

		Math::Vector3 _position = { .0f, .0f, .0f };
		Float _rotation = 0;
	};

}
