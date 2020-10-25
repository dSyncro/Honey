#pragma once

#include "ComponentDrawing.h"

#include <Honeycomb/Editor/EditorGUI.h>

namespace Honey {

	REGISTER_COMPONENT_DRAWER(NameComponentDrawer, entity)
	{
		std::string& name = entity.getComponent<NameComponent>().name;
		static char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), name.c_str());
		EditorGUI::textField("Name", name);
	}

}
