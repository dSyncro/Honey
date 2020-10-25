#pragma once

#include "ComponentDrawing.h"

#include <Honeycomb/Editor/EditorGUI.h>

namespace Honey {

	REGISTER_COMPONENT_DRAWER(TransformComponentDrawer, entity)
	{
		TransformComponent& transform = entity.getComponent<TransformComponent>();

		EditorGUI::vector3Field("Position", transform.position);

		Math::Vector3 degrees = transform.rotation * Mathf::radians2Degrees();
		EditorGUI::vector3Field("Rotation", degrees);
		transform.rotation = degrees * Mathf::degrees2Radians();

		EditorGUI::vector3Field("Scale", transform.scale);
	}

}
