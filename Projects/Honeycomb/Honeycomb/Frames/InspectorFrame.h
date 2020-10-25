#pragma once

#include <Honey.h>

namespace Honey {

	class InspectorFrame {

	public:

		void onImGuiRender();

	private:

		void drawComponents(Entity entity);
	};

}
