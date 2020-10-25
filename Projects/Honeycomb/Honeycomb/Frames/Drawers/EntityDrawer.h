#pragma once

#include "ComponentDrawers.h"

namespace Honey {

	class EntityDrawer {

	public:

		EntityDrawer(const Entity& entity) : _entity(entity) {}

		template <typename ComponentType, typename DrawerType>
		void drawComponent(const std::string& name, bool isOpenable = true, bool isRemovable = true)
		{
			if (!_entity.hasComponent<ComponentType>()) return;

			ComponentInfo info;
			info.entity = _entity;

			if (isOpenable)
				info.isNodeOpened = ImGui::TreeNodeEx((void*)typeid(ComponentType).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, name.c_str());

			if (isRemovable)
			{
				ImGui::SameLine();
				if (ImGui::Button("+"))
					ImGui::OpenPopup("ComponentCommands");

				if (ImGui::BeginPopup("ComponentCommands"))
				{
					if (ImGui::MenuItem("Remove component"))
						info.shouldComponentBeRemoved = true;

					ImGui::EndPopup();
				}
			}

			if (info.isNodeOpened)
			{
				DrawerType::draw(info);
				ImGui::TreePop();
			}
			else if (!isOpenable) DrawerType::draw(info);

			if (info.shouldComponentBeRemoved)
				info.entity.removeComponent<ComponentType>();
		}

	private:

		Entity _entity;
	};

}
