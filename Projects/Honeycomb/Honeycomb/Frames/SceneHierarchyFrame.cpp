#include "SceneHierarchyFrame.h"

#include <Honeycomb/Editor/Editor.h>
#include <Honeycomb/Editor/EditorGUI.h>

#include <ImGui/imgui.h>

using namespace Honey;

void SceneHierarchyFrame::onImGuiRender()
{
	EditorGUI::beginWindow("Hierarchy");

	_context->_registry.each([&](entt::entity entity) {
			Entity e(entity, _context.get());
			drawEntityNode(e);
		}
	);

	if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		Editor::select(Entity::null());

	if (ImGui::BeginPopupContextWindow(0, 1, false))
	{
		if (EditorGUI::menuItem("Create new empty entity"))
			_context->createEntity("Empty entity");

		ImGui::EndPopup();
	}

	EditorGUI::endWindow();
}

void SceneHierarchyFrame::drawEntityNode(Entity entity)
{
	NameComponent& nc = entity.getComponent<NameComponent>();
	Entity selectedEntity = Editor::getSelectedEntity();
	ImGuiTreeNodeFlags flags = (selectedEntity == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

	bool isOpened = ImGui::TreeNodeEx((void*)(entt::entity)entity, flags, nc.name.c_str());

	if (ImGui::IsItemClicked())
		selectedEntity = entity;

	bool shouldDeleteEntity = false;
	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::MenuItem("Delete Entity")) 
			shouldDeleteEntity = true;

		ImGui::EndPopup();
	}

	if (isOpened) ImGui::TreePop();

	if (shouldDeleteEntity) 
	{ 
		if (selectedEntity == entity)
			selectedEntity = Entity::null();
		_context->deleteEntity(entity);
	}

	Editor::select(selectedEntity);
}
