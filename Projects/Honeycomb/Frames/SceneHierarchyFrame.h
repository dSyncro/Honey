#pragma once

#include <Honey.h>

namespace Honey {

	class SceneHierarchyFrame {

	public:

		SceneHierarchyFrame(const Reference<Scene>& context = nullptr) { SetContext(_context); }

		void SetContext(const Reference<Scene>& context) { _context = context; }

		void OnImGuiRender();

	private:

		void DrawEntityNode(Entity entity);

		Reference<Scene> _context;
		Entity _selected;

	};

}
