#include "EditorGUI.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

using namespace Honey;

EditorStyle EditorGUI::_style = EditorStyle();

void EditorGUI::beginWindow(const std::string& name)
{
	ImGui::Begin(name.c_str());
}

void EditorGUI::endWindow()
{
	ImGui::End();
}

void EditorGUI::label(const std::string& text)
{
	ImGui::Text(text.c_str());
}

static void pushStyleColor(ImGuiCol colorType, Color color)
{
	ImGui::PushStyleColor(colorType, ImVec4(color.r, color.g, color.b, color.a));
}

void EditorGUI::vector2Field(const std::string& label, Math::Vector2& values, Float resetValue, Float columnWidth)
{
	ImGuiIO& io = ImGui::GetIO();
	ImFont* boldFont = io.Fonts->Fonts[0];

	const Color activeColorOffset = Color(0.1f, 0.1f, 0.1f, 0.0f);
	const Color hoveredColorOffset = Color(0.5f, 0.5f, 0.5f, 0.0f);

	EditorStyle style = EditorGUI::getStyle();

	ImGui::PushID(label.c_str());

	ImGui::Columns(2);

	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());

	ImGui::NextColumn();

	ImGui::PushItemWidth(ImGui::CalcItemWidth() / 2.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });

	Float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

	pushStyleColor(ImGuiCol_Button, style.xAxisColor);
	pushStyleColor(ImGuiCol_ButtonActive, (style.xAxisColor + activeColorOffset).clampToOne());
	pushStyleColor(ImGuiCol_ButtonHovered, (style.xAxisColor + hoveredColorOffset).clampToOne());
	ImGui::PushFont(boldFont);
	if (ImGui::Button("X", buttonSize))
		values.x = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##X", &values.x, 0.1f);
	ImGui::SameLine();

	pushStyleColor(ImGuiCol_Button, style.yAxisColor);
	pushStyleColor(ImGuiCol_ButtonActive, (style.yAxisColor + activeColorOffset).clampToOne());
	pushStyleColor(ImGuiCol_ButtonHovered, (style.yAxisColor + hoveredColorOffset).clampToOne());
	ImGui::PushFont(boldFont);
	if (ImGui::Button("Y", buttonSize))
		values.y = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Y", &values.y, 0.1f);
	ImGui::SameLine();

	ImGui::PopItemWidth();
	ImGui::PopStyleVar();

	ImGui::Columns(1);

	ImGui::PopID();
}

void EditorGUI::vector3Field(const std::string& label, Math::Vector3& values, Float resetValue, Float columnWidth)
{
	ImGuiIO& io = ImGui::GetIO();
	ImFont* boldFont = io.Fonts->Fonts[0];

	const Color activeColorOffset = Color(0.1f, 0.1f, 0.1f, 0.0f);
	const Color hoveredColorOffset = Color(0.5f, 0.5f, 0.5f, 0.0f);

	EditorStyle style = EditorGUI::getStyle();

	ImGui::PushID(label.c_str());

	ImGui::Columns(2);

	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());

	ImGui::NextColumn();

	ImGui::PushItemWidth(ImGui::CalcItemWidth() / 3.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });

	Float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

	pushStyleColor(ImGuiCol_Button, style.xAxisColor);
	pushStyleColor(ImGuiCol_ButtonActive, (style.xAxisColor + activeColorOffset).clampToOne());
	pushStyleColor(ImGuiCol_ButtonHovered, (style.xAxisColor + hoveredColorOffset).clampToOne());
	ImGui::PushFont(boldFont);
	if (ImGui::Button("X", buttonSize))
		values.x = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##X", &values.x, 0.1f);
	ImGui::SameLine();

	pushStyleColor(ImGuiCol_Button, style.yAxisColor);
	pushStyleColor(ImGuiCol_ButtonActive, (style.yAxisColor + activeColorOffset).clampToOne());
	pushStyleColor(ImGuiCol_ButtonHovered, (style.yAxisColor + hoveredColorOffset).clampToOne());
	ImGui::PushFont(boldFont);
	if (ImGui::Button("Y", buttonSize))
		values.y = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Y", &values.y, 0.1f);
	ImGui::SameLine();

	pushStyleColor(ImGuiCol_Button, style.zAxisColor);
	pushStyleColor(ImGuiCol_ButtonActive, (style.zAxisColor + activeColorOffset).clampToOne());
	pushStyleColor(ImGuiCol_ButtonHovered, (style.zAxisColor + hoveredColorOffset).clampToOne());
	ImGui::PushFont(boldFont);
	if (ImGui::Button("Z", buttonSize))
		values.z = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Z", &values.z, 0.1f);

	ImGui::PopItemWidth();
	ImGui::PopStyleVar();

	ImGui::Columns(1);

	ImGui::PopID();
}

void EditorGUI::colorEdit(const std::string& label, Color& color)
{
	ImGui::ColorEdit4(label.c_str(), &color.r);
}

bool EditorGUI::menuItem(const std::string& label)
{
	return ImGui::MenuItem(label.c_str());
}

bool EditorGUI::checkbox(const std::string& label, bool* value)
{
	return ImGui::Checkbox(label.c_str(), value);
}

void EditorGUI::textField(const std::string& label, std::string& text, UInt bufferSize)
{
	char* buffer = new char[bufferSize];
	memset(buffer, 0, bufferSize);
	strcpy_s(buffer, bufferSize, text.c_str());
	bool changed = ImGui::InputText(label.c_str(), buffer, bufferSize);
	if (changed) text = std::string(buffer);
}
