#pragma once

#include "ComponentDrawing.h"

#include <ImGui/imgui.h>

namespace Honey {

	REGISTER_COMPONENT_DRAWER(NameComponentDrawer, info)
	{
		std::string& name = info.entity.getComponent<NameComponent>().name;
		static char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), name.c_str());
		if (ImGui::InputText("Name", buffer, sizeof(buffer)))
			name = std::string(buffer);
	}

}
