#pragma once

#include <Honeycomb/Editor/EditorGUI.h>

#include "ComponentDrawing.h"

namespace Honey {

	REGISTER_COMPONENT_DRAWER(TransformComponentDrawer, info)
	{
		TransformComponent& transform = info.entity.getComponent<TransformComponent>();

		EditorGUI::drawVector3("Position", transform.position);

		Math::Vector3 degrees = transform.rotation * Mathf::radians2Degrees();
		EditorGUI::drawVector3("Rotation", degrees);
		transform.rotation = degrees * Mathf::degrees2Radians();

		EditorGUI::drawVector3("Scale", transform.scale);
	}

}
