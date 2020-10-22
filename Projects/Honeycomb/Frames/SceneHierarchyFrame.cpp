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
		if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
		{
			TransformComponent& transform = entity.getComponent<TransformComponent>();

			ImGui::DragFloat3("Position", &transform.position[0], 0.5f);

			Math::Vector3 degrees = transform.rotation * Mathf::radians2Degrees();
			if (ImGui::DragFloat3("Rotation", &degrees[0], 0.5f))
				transform.rotation = degrees * Mathf::degrees2Radians();

			ImGui::DragFloat3("Scale", &transform.scale[0], 0.5f);

			ImGui::TreePop();
		}
	}

	if (entity.hasComponent<CameraComponent>())
	{
		if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
		{
			CameraComponent& cameraComponent = entity.getComponent<CameraComponent>();
			SceneCamera& cam = cameraComponent.camera;

			const char* projectionTypes[2] = { "Perspective", "Orthographic" };
			const char* currentProjectionType = projectionTypes[static_cast<UInt>(cam.getProjectionType())];
			if (ImGui::BeginCombo("Projection", currentProjectionType))
			{
				for (UInt i = 0; i < 2; i++)
				{
					bool isSelected = currentProjectionType == projectionTypes[i];
					if (ImGui::Selectable(projectionTypes[i], isSelected))
					{
						currentProjectionType = projectionTypes[i];
						cam.setProjectionType(static_cast<SceneCamera::ProjectionType>(i));
					}

					if (isSelected) ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			if (cam.getProjectionType() == SceneCamera::ProjectionType::Perspective)
			{
				Float fov = cam.getPerspectiveVerticalFOV();
				if (ImGui::DragFloat("Vertical FOV", &fov))
					cam.setPerspectiveVerticalFOV(fov);

				Float nearClip = cam.getPerspectiveNearClip();
				if (ImGui::DragFloat("Near Clip", &nearClip))
					cam.setPerspectiveNearClip(nearClip);

				Float farClip = cam.getPerspectiveFarClip();
				if (ImGui::DragFloat("Far Clip", &farClip))
					cam.setPerspectiveFarClip(farClip);
			}

			if (cam.getProjectionType() == SceneCamera::ProjectionType::Orthographic)
			{
				Float size = cam.getOrthographicSize();
				if (ImGui::DragFloat("Size", &size))
					cam.setOrthographicSize(size);

				Float nearClip = cam.getOrthographicNearClip();
				if (ImGui::DragFloat("Near Clip", &nearClip))
					cam.setOrthographicNearClip(nearClip);

				Float farClip = cam.getOrthographicFarClip();
				if (ImGui::DragFloat("Far Clip", &farClip))
					cam.setOrthographicFarClip(farClip);

				ImGui::Checkbox("Fixed Aspect Ratio", &cameraComponent.hasFixedAspectRatio);
			}

			ImGui::TreePop();
		}
	}
}
