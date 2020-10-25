#pragma once

#include <Honey.h>

namespace Honey {

	class EntityDrawer {

	public:

		EntityDrawer(const Entity& entity) : _entity(entity) {}

		template <typename ComponentType, typename DrawerType>
		void drawComponent(const std::string& name, bool isOpenable = true, bool isRemovable = true)
		{
			bool isNodeOpened = false;
			bool shouldComponentBeRemoved = false;

			if (!_entity.hasComponent<ComponentType>()) return;

			if (isOpenable)
				isNodeOpened = ImGui::TreeNodeEx((void*)typeid(ComponentType).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, name.c_str());

			if (isRemovable)
			{
				ImGui::SameLine();
				if (ImGui::Button("+"))
					ImGui::OpenPopup("ComponentCommands");

				if (ImGui::BeginPopup("ComponentCommands"))
				{
					if (ImGui::MenuItem("Remove component"))
						shouldComponentBeRemoved = true;

					ImGui::EndPopup();
				}
			}

			if (isNodeOpened)
			{
				DrawerType::draw(_entity);
				ImGui::TreePop();
			}
			else if (!isOpenable) DrawerType::draw(_entity);

			if (shouldComponentBeRemoved)
				_entity.removeComponent<ComponentType>();
		}

	private:

		Entity _entity;
	};

}
