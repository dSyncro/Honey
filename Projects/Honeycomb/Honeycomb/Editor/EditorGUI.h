#pragma once

#include <string>

#include <Honey.h>

#include "EditorStyle.h"

namespace Honey {

	class EditorGUI {

	public:

		HNY_PURE_STATIC(EditorGUI);

		static void beginWindow(const std::string& name);
		static void endWindow();

		static void label(const std::string& text);
		static void textField(const std::string& label, std::string& text, UInt bufferSize = 256);
		static void vector2Field(const std::string& label, Math::Vector2& values, Float resetValue = 0.0f, Float columnWidth = 100.0f);
		static void vector3Field(const std::string& label, Math::Vector3& values, Float resetValue = 0.0f, Float columnWidth = 100.0f);
		static void colorEdit(const std::string& label, Color& color);

		static bool menuItem(const std::string& label);
		static bool checkbox(const std::string& label, bool* value);

		static const EditorStyle& getStyle()
		{
			return _style;
		}

		static void setStyle(const EditorStyle& style)
		{
			_style = style;
		}

	private:

		static EditorStyle _style;

	};
}
