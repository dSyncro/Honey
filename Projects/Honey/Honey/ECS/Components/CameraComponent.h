/**
 * @file CameraComponent.h
*/

#pragma once

#include <Honey/Scene/SceneCamera.h>

namespace Honey {

	/**
	 * @brief Camera Component.
	 * It wraps information used for rendering and is
	 * responsible for projection matrix.
	*/
	struct CameraComponent {

		CameraComponent() = default;
		~CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;

		/**
		 * @brief Underlying camera.
		*/
		SceneCamera camera;

		/**
		 * @brief Camera has a fixed aspect ratio.
		 * It means that its aspect ratio will not be
		 * recalculated dynamically when viewport resize occurs.
		*/
		bool hasFixedAspectRatio = false;
	};

}
