#pragma once

#include "ComponentDrawing.h"

#include <ImGui/imgui.h>

namespace Honey {

	REGISTER_COMPONENT_DRAWER(SpriteRendererComponentDrawer, info)
	{
		SpriteRendererComponent& renderer = info.entity.getComponent<SpriteRendererComponent>();
		Math::Vector4 color = renderer.tint.toRGBA();
		if (ImGui::ColorEdit4("Tint", &color[0]))
			renderer.tint = color;
	}

}
