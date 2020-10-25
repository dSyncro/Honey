#pragma once

#include <string>

#include <Honey.h>

#include "EditorStyle.h"

namespace Honey {

	class EditorGUI {

	public:

		// Pure virtual class

		EditorGUI() = delete;
		EditorGUI(const EditorGUI&) = delete;
		EditorGUI(EditorGUI&&) = delete;
		EditorGUI& operator =(const EditorGUI&) = delete;
		EditorGUI& operator =(EditorGUI&&) = delete;

		static void beginWindow(const std::string& name);
		static void endWindow();

		static void drawVector3(const std::string& label, Math::Vector3& values, Float resetValue = 0.0f, Float columnWidth = 100.0f);

		static bool menuItem(const std::string& label);

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
