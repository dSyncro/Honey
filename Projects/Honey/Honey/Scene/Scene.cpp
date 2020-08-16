#include "Scene.h"

#include <Honey/ECS/Entity.h>
#include <Honey/ECS/Components.h>
#include <Honey/Renderer/2D/Renderer2D.h>
#include <Honey/Math/Matrix/Matrix4x4.h>

using namespace Honey;

void Scene::OnUpdate()
{
	_registry.view<NativeScriptComponent>().each([=](entt::entity entity, NativeScriptComponent& nsc) 
		{
			if (!nsc.Instance)
			{
				nsc.InstantiateFunction();
				nsc.Instance->_entity = Entity(entity, this);
				nsc.OnCreateFunction(nsc.Instance);
			}

			nsc.OnUpdateFunction(nsc.Instance);
		}
	);

	_mainCamera.Reset();

	auto rendererGroup = _registry.view<TransformComponent, TagComponent, CameraComponent>();
	for (entt::entity entity : rendererGroup)
	{
		auto& [transform, tag, camera] = rendererGroup.get<TransformComponent, TagComponent, CameraComponent>(entity);
		if (tag.Tag == "Main")
		{
			_mainCamera.Camera = &camera.Camera;
			_mainCamera.Transform = &transform.Transform.GetMatrix();
		}
	}

	if (_mainCamera)
	{
		auto renderableGroup = _registry.view<TransformComponent, SpriteRendererComponent>();
		Renderer2D::BeginScene(*_mainCamera.Camera, *_mainCamera.Transform);
		for (entt::entity entity : renderableGroup)
		{
			auto& [transform, sprite] = renderableGroup.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(transform.Transform.Position, (Math::Vector2)transform.Transform.Scale, sprite.Color);
		}
		Renderer2D::EndScene();
	}
}

Entity Scene::CreateEntity(const std::string& name, const std::string& tag)
{
	Entity entity = Entity(_registry.create(), this);
	entity.AddComponent<TransformComponent>();
	entity.AddComponent<NameComponent>().Name = name;
	entity.AddComponent<TagComponent>().Tag = tag;
	return entity;
}

void Scene::DeleteEntity(const Entity& entity)
{
	_registry.destroy(entity);
}

void Scene::OnViewportResize(uint32_t width, uint32_t height)
{
	auto camerasView = _registry.view<CameraComponent>();
	for (entt::entity entity : camerasView)
	{
		auto& camComponent = _registry.get<CameraComponent>(entity);
		if (camComponent.HasFixedAspectRatio) continue;
		camComponent.Camera.SetViewportSize(width, height);
	}
}
