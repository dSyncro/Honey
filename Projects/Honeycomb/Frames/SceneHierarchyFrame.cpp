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

	ImGui::Begin("Properties");

	if (_selected)
	{
		DrawComponents(_selected);
	}

	ImGui::End();
}

void SceneHierarchyFrame::DrawEntityNode(Entity entity)
{
	NameComponent& nc = entity.getComponent<NameComponent>();
	ImGuiTreeNodeFlags flags = (_selected == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
	bool isOpened = ImGui::TreeNodeEx((void*)(entt::entity)entity, flags, nc.name.c_str());

	if (ImGui::IsItemClicked())
		_selected = entity;

	if (isOpened) ImGui::TreePop();
}

void SceneHierarchyFrame::DrawComponents(Entity entity)
{
	if (entity.hasComponent<NameComponent>())
	{
		std::string& name = entity.getComponent<NameComponent>().name;
		static char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), name.c_str());
		if (ImGui::InputText("Name", buffer, sizeof(buffer)))
		{
			name = std::string(buffer);
		}
	}

	if (entity.hasComponent<TagComponent>())
	{
		std::string& tag = entity.getComponent<TagComponent>().tag;
		static char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), tag.c_str());
		if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
		{
			tag = std::string(buffer);
		}
	}

	if (entity.hasComponent<TransformComponent>())
	{
		TransformComponent& transform = entity.getComponent<TransformComponent>();
		Math::Vector3 eulerAngles = transform.rotation.ToEulerAngles();
		ImGui::DragFloat3("Position", &transform.position[0], 0.5f);
		ImGui::DragFloat3("Rotation", &eulerAngles[0], 0.5f);
		ImGui::DragFloat3("Scale", &transform.scale[0], 0.5f);
		transform.rotation = Math::Quaternion::FromEulerAngles(eulerAngles);
	}
}
