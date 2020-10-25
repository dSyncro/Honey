#pragma once

#include "ComponentDrawing.h"

#include <Honeycomb/Editor/EditorGUI.h>

namespace Honey {

	REGISTER_COMPONENT_DRAWER(SpriteRendererComponentDrawer, entity)
	{
		SpriteRendererComponent& renderer = entity.getComponent<SpriteRendererComponent>();
		EditorGUI::colorEdit("Tint", renderer.tint);
	}

}
