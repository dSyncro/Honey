#pragma once

#include "ComponentDrawing.h"

#include <ImGui/imgui.h>

namespace Honey {

	REGISTER_COMPONENT_DRAWER(TagComponentDrawer, info)
	{
		std::string& tag = info.entity.getComponent<TagComponent>().tag;
		static char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), tag.c_str());
		if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			tag = std::string(buffer);
	}

}
