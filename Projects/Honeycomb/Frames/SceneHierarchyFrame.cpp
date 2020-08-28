#include "SceneHierarchyFrame.h"

using namespace Honey;

#include <ImGui/imgui.h>

void SceneHierarchyFrame::OnImGuiRender()
{
	ImGui::Begin("Hierarchy");

	_context->_registry.each([&](auto entity) {
			Entity e(entity, _context.get());
			DrawEntityNode(e);
		}
	); 

	ImGui::End();
}

void SceneHierarchyFrame::DrawEntityNode(Entity entity)
{
	NameComponent& nc = entity.GetComponent<NameComponent>();
	ImGuiTreeNodeFlags flags = (_selected == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
	bool isOpened = ImGui::TreeNodeEx((void*)(entt::entity)entity, flags, nc.Name.c_str());

	if (ImGui::IsItemClicked())
		_selected = entity;

	if (isOpened) ImGui::TreePop();
}
