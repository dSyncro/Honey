#pragma once

#include <Honey.h>

namespace Honey {

	class Editor {

	public:

		// Pure virtual class
		HNY_PURE_STATIC(Editor);

		static void select(Entity entity);
		static Entity getSelectedEntity();
		template <typename T = Entity>
		static void deselect();

	private:

		static Entity _selectedEntity;
	};

}
