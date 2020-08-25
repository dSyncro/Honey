#pragma once

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
		Math::Matrix4x4 Transform = Math::Matrix4x4::Identity;

		void Reset() noexcept { Camera = nullptr; Transform = Math::Matrix4x4::Identity; }

		operator bool() const { return Camera; }
	};

	class Scene {

	public:

		Scene() = default;
		~Scene() = default;

		Entity CreateEntity(const std::string& name = "Entity", const std::string& tag = "Untagged");
		void DeleteEntity(const Entity& entity);

		void OnPlay();
		void OnUpdate();
		void OnStop();
		void OnViewportResize(uint32_t width, uint32_t height);
	private:

		entt::registry _registry;
		RenderCameraData _mainCamera;

		friend class Entity;
	};

}
