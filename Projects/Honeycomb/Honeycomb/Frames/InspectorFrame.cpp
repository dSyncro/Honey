#include "InspectorFrame.h"

#include <Honeycomb/Editor/Editor.h>
#include <Honeycomb/Editor/EditorGUI.h>
#include <Honeycomb/Frames/Drawers/EntityDrawer.h>

#include <ImGui/imgui.h>

using namespace Honey;

template <typename T>
void addComponentToComponentsList(const std::string& name)
{
	if (!Editor::getSelectedEntity().hasComponent<T>())
	{
		if (EditorGUI::menuItem(name))
		{
			Editor::getSelectedEntity().addComponent<T>();
			ImGui::CloseCurrentPopup();
		}
	}
}

template <typename T>
void addComponentToComponentsList()
{
	const char* name = typeid(T).name();
	addComponentToComponentsList<T>(name);
}

void InspectorFrame::onImGuiRender()
{
	EditorGUI::beginWindow("Properties");

	Entity selectedEntity = Editor::getSelectedEntity();
	if (selectedEntity != Entity::null())
	{
		drawComponents(selectedEntity);

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{

			addComponentToComponentsList<CameraComponent>("Camera");
			addComponentToComponentsList<SpriteRendererComponent>("Sprite Renderer");

			ImGui::EndPopup();
		}

	}

	EditorGUI::endWindow();
}

void InspectorFrame::drawComponents(Entity entity)
{
	EntityDrawer drawer(entity);
	drawer.drawComponent<NameComponent, NameComponentDrawer>("Name", false, false);
	drawer.drawComponent<TagComponent, TagComponentDrawer>("Tag", false, false);
	drawer.drawComponent<TransformComponent, TransformComponentDrawer>("Transform", true, false);
	drawer.drawComponent<CameraComponent, CameraComponentDrawer>("Camera", true, true);
	drawer.drawComponent<SpriteRendererComponent, SpriteRendererComponentDrawer>("Sprite Renderer", true, true);
}
