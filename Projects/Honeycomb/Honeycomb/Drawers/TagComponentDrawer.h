#pragma once

#include "ComponentDrawing.h"

#include <Honeycomb/Editor/EditorGUI.h>

namespace Honey {

	REGISTER_COMPONENT_DRAWER(TagComponentDrawer, entity)
	{
		std::string& tag = entity.getComponent<TagComponent>().tag;
		static char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), tag.c_str());
		EditorGUI::textField("Tag", tag);
	}

}
