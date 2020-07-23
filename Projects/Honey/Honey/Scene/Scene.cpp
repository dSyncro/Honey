#include "Scene.h"

#include <Honey/ECS/Entity.h>
#include <Honey/ECS/Components.h>
#include <Honey/Renderer/2D/Renderer2D.h>

using namespace Honey;

void Scene::OnUpdate()
{
	auto renderableGroup = _registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
	for (entt::entity entity : renderableGroup)
	{
		auto& [transform, sprite] = renderableGroup.get<TransformComponent, SpriteRendererComponent>(entity);
		Renderer2D::DrawQuad(transform, sprite.Color);
	}
}

Entity Scene::CreateEntity(const std::string& tag)
{
	Entity entity = Entity(_registry.create(), this);
	entity.AddComponent<TransformComponent>();
	TagComponent& tagComponent = entity.AddComponent<TagComponent>();
	tagComponent.Tag = tag.empty() ? "Entity" : tag;
	return entity;
}

void Scene::DeleteEntity(const Entity& entity)
{
	_registry.destroy(entity);
}