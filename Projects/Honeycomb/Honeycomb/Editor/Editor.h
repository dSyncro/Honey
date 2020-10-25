#pragma once

#include <Honey.h>

namespace Honey {

	class Editor {

	public:

		// Pure virtual class

		Editor() = delete;
		Editor(const Editor&) = delete;
		Editor(Editor&&) = delete;
		Editor& operator =(const Editor&) = delete;
		Editor& operator =(Editor&&) = delete;

		static void select(Entity entity);
		static Entity getSelectedEntity();
		template <typename T = Entity>
		static void deselect();

	private:

		static Entity _selectedEntity;
	};

}
