#include "Scene.h"

#include <Honey/ECS/Entity.h>
#include <Honey/ECS/Components.h>
#include <Honey/Renderer/2D/Renderer2D.h>
#include <Honey/Math/Matrix/Matrix4x4.h>

using namespace Honey;
using namespace Honey::Math;

void Scene::OnPlay()
{
	_registry.view<NativeScriptComponent>().each([=](entt::entity entity, NativeScriptComponent& nsc)
		{
			for (Behaviour* behaviour : nsc.behaviours)
			{
				behaviour->_entity = &nsc.entity;
			}
			nsc.onCreate();
		}
	);
}

void Scene::OnUpdate()
{
	_registry.view<NativeScriptComponent>().each([=](entt::entity entity, NativeScriptComponent& nsc) 
		{
			nsc.onUpdate();
		}
	);

	_mainCamera.Reset();

	auto rendererView = _registry.view<TransformComponent, TagComponent, CameraComponent>();
	for (entt::entity entity : rendererView)
	{
		auto [transform, tag, camera] = rendererView.get<TransformComponent, TagComponent, CameraComponent>(entity);
		if (tag.tag == "Main")
		{
			_mainCamera.Camera = &camera.camera;
			_mainCamera.Transform = transform.GetTRSMatrix();
		}
	}

	if (_mainCamera)
	{
		auto renderableView = _registry.view<TransformComponent, SpriteRendererComponent>();
		//auto textEntityView = _registry.view<TransformComponent, TextComponent>();

		Renderer2D::BeginScene(*_mainCamera.Camera, _mainCamera.Transform);

		for (entt::entity entity : renderableView)
		{
			auto [transform, spriteRenderer] = renderableView.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawSprite(transform.position, (Vector2)transform.scale, spriteRenderer.sprite, spriteRenderer.tint);
		}

		/*Renderer2D::BeginScreenSpace();
		for (entt::entity entity : textEntityView)
		{
			auto [transform, textComponent] = textEntityView.get<TransformComponent, TextComponent>(entity);
			Renderer2D::DrawText(transform.position, textComponent.text, textComponent.atlas);
		}
		Renderer2D::EndScreenSpace();*/

		Renderer2D::EndScene();
	}
}

void Scene::OnStop()
{

}

Entity Scene::CreateEntity(const std::string& name, const std::string& tag)
{
	Entity entity = Entity(_registry.create(), this);
	entity.addComponent<TransformComponent>();
	entity.addComponent<NameComponent>().name = name;
	entity.addComponent<TagComponent>().tag = tag;
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
		CameraComponent& camComponent = _registry.get<CameraComponent>(entity);
		if (camComponent.hasFixedAspectRatio) continue;
		camComponent.camera.SetViewportSize(width, height);
	}
}
