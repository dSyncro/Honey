#pragma once

#include <Honey.h>

namespace Honey {

	class SceneHierarchyFrame {

	public:

		SceneHierarchyFrame(const Reference<Scene>& context = nullptr) { setContext(_context); }

		void setContext(const Reference<Scene>& context) { _context = context; }

		void onImGuiRender();

	private:

		void drawEntityNode(Entity entity);

		Reference<Scene> _context;

	};

}
