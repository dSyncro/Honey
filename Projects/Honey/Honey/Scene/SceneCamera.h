#pragma once

#include <Honey/Renderer/Camera/Camera.h>

namespace Honey {

	/**
	 * @brief Camera extension.
	*/
	class SceneCamera : public Camera {

	public:

		/**
		 * @brief All possible camera projection types.
		*/
		enum class ProjectionType : Byte {
			Perspective = 0, /** @brief Perspective projection. */
			Orthographic = 1 /** @brief Orthographic projection. */
		};

		SceneCamera() = default;
		virtual ~SceneCamera() = default;

		/**
		 * @brief Set orthographic projection.
		 * @param size Orthographic size.
		 * @param nearClip Near clip distance.
		 * @param farClip Far clip distance.
		*/
		void setOrthographic(Float size, Float nearClip, Float farClip);

		/**
		 * @brief Set perspective projection.
		 * @param verticalFOV Vertical FOV.
		 * @param nearClip Near clip distance.
		 * @param farClip Far clip distance.
		*/
		void setPerspective(Float verticalFOV, Float nearClip, Float farClip);

		/**
		 * @brief Set viewport size.
		 * @param width Viewport width.
		 * @param height Viewport height.
		*/
		void setViewportSize(UInt width, UInt height);

		/**
		 * @brief Get camera projection type.
		 * @return Camera projection type.
		*/
		ProjectionType getProjectionType() const { return _projectionType; }

		/**
		 * @brief Set camera projection type.
		 * @param type New camera projection type.
		*/
		void setProjectionType(ProjectionType type) { _projectionType = type; recalculateProjection(); }

		/**
		 * @brief Get orthographic near clip distance.
		 * @return Near clip distance.
		*/
		Float getOrthographicNearClip() const { return _orthoNear; }

		/**
		 * @brief Get orthographic far clip distance.
		 * @return Far clip distance. 
		*/
		Float getOrthographicFarClip() const { return _orthoFar; }

		/**
		 * @brief Get orthographic camera size.
		 * @return Orthographic size.
		*/
		Float getOrthographicSize() const { return _orthoSize; }

		/**
		 * @brief Get perspective near clip distance.
		 * @return Near clip distance.
		*/
		Float getPerspectiveNearClip() const { return _perspectiveNear; }

		/**
		 * @brief Get perspective far clip distance.
		 * @return Far clip distance.
		*/
		Float getPerspectiveFarClip() const { return _perspectiveFar; }

		/**
		 * @brief Get perspective vertical Field of View.
		 * @return Vertical FOV.
		*/
		Float getPerspectiveVerticalFOV() const { return _perspectiveFOV; }

		/**
		 * @brief Set orthographic near clip distance.
		 * @param nearClip New near clip distance.
		*/
		void setOrthographicNearClip(Float nearClip) { _orthoNear = nearClip; recalculateOrthographicProjection(); }

		/**
		 * @brief Set orthographic far clip distance.
		 * @param farClip New far clip distance.
		*/
		void setOrthographicFarClip(Float farClip) { _orthoFar = farClip; recalculateOrthographicProjection(); }

		/**
		 * @brief Set orthographic camera size.
		 * @param size New orthographic size.
		*/
		void setOrthographicSize(Float size) { _orthoSize = size; recalculateOrthographicProjection(); }

		/**
		 * @brief Set perspective near clip distance.
		 * @param nearClip New near clip distance.
		*/
		void setPerspectiveNearClip(Float nearClip) { _perspectiveNear = nearClip; recalculatePerspectiveProjection(); }

		/**
		 * @brief Set perspective far clip distance.
		 * @param farClip New far clip distance.
		*/
		void setPerspectiveFarClip(Float farClip) { _perspectiveFar = farClip; recalculatePerspectiveProjection(); }
		
		/**
		 * @brief Set perspective camera vertical Field of View.
		 * @param fov Field of View.
		*/
		void setPerspectiveVerticalFOV(Float fov) { _perspectiveFOV = fov; recalculatePerspectiveProjection(); }

	private:

		void recalculateProjection();

		void recalculatePerspectiveProjection();
		void recalculateOrthographicProjection();

		Float _orthoSize = 10.0f;
		Float _orthoNear = -1.0f; Float _orthoFar = 1.0f;

		Float _perspectiveFOV = 45.0f * Mathf::degrees2Radians();
		Float _perspectiveNear = 0.001f, _perspectiveFar = 1000.0f;

		Float _aspectRatio = 1.0f;

		ProjectionType _projectionType = ProjectionType::Orthographic;
	};

}
