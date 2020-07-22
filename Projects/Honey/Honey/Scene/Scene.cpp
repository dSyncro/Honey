#include "Scene.h"

#include <Honey/Components/SpriteRendererComponent.h>
#include <Honey/Components/TransformComponent.h>
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