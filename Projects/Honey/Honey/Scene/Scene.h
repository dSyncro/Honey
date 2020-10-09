#pragma once

/*
	This is an absolute mess but it is still in development.
	Revisit this as soon as it get stabler.
*/

#include <entt.hpp>

#include <Honey/Math/Math.h>
#include <Honey/Renderer/Camera/Camera.h>

namespace Honey {

	class Entity;
	struct TransformComponent;
	struct TagComponent;
	struct NameComponent;
	struct CameraComponent;

	struct RenderCameraData {

		Honey::Camera* Camera = nullptr;
		Math::Matrix4x4 Transform = Math::Matrix4x4::identity();

		void Reset() noexcept { Camera = nullptr; Transform = Math::Matrix4x4::identity(); }

		operator bool() const { return Camera; }
	};

	/**
	 * @brief Game world scene.
	*/
	class Scene {

	public:

		Scene() = default;
		~Scene() = default;

		/**
		 * @brief Create entity.
		 * @param name Entity name.
		 * @param tag Entity tag.
		 * @return The entity.
		*/
		Entity createEntity(const std::string& name = "Entity", const std::string& tag = "Untagged");

		/**
		 * @brief Delete entity from scene.
		 * @param entity The entity.
		*/
		void deleteEntity(const Entity& entity);

		/**
		 * @brief Called when scene starts.
		*/
		void onStart();

		/**
		 * @brief Called when scene updates.
		*/
		void onUpdate();

		/**
		 * @brief Called when scene stops.
		*/
		void onStop();

		/**
		 * @brief Called on viewport resize.
		 * @param width New viewport width.
		 * @param height New viewport height.
		*/
		void onViewportResize(UInt width, UInt height);
	private:

		entt::registry _registry;
		RenderCameraData _mainCamera;

		friend class Entity;
		friend class SceneHierarchyFrame;
	};

}
