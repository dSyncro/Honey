#include "CameraComponentDrawer.h"

using namespace Honey;

COMPONENT_DRAWER_FUNCTION(CameraComponentDrawer, info)
{
	CameraComponent& cameraComponent = info.entity.getComponent<CameraComponent>();
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

	switch (cam.getProjectionType())
	{
		case SceneCamera::ProjectionType::Perspective:
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

			break;
		}

		case SceneCamera::ProjectionType::Orthographic:
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

			break;
		}
	}
}
