#pragma once

#include <Honey.h>

namespace Honey {

	class EntityDrawer {

	public:

		EntityDrawer(const Entity& entity) : _entity(entity) {}

		template <typename ComponentType, typename DrawerType>
		void drawComponent(const std::string& name, bool isOpenable = true, bool isRemovable = true)
		{
			const ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen | 
				ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Framed | 
				ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

			bool isNodeOpened = false;
			bool shouldComponentBeRemoved = false;

			if (!_entity.hasComponent<ComponentType>()) return;

			Float contentRegionAvail = ImGui::GetContentRegionAvailWidth();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 4.0f, 4.0f });
			ImGui::Separator();
			if (isOpenable)
				isNodeOpened = ImGui::TreeNodeEx((void*)typeid(ComponentType).hash_code(), treeFlags, name.c_str());
			ImGui::PopStyleVar();

			if (isRemovable)
			{
				Float lineHeight = ImGui::GetFrameHeightWithSpacing();
				ImGui::SameLine(contentRegionAvail - lineHeight * 0.5f);
				if (ImGui::Button("+", { lineHeight, lineHeight }))
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
