#include "EditorLayer.h"

#include <Honey/Entrypoint.h>

namespace Honey {

	class Honeycomb : public Application {

	public:

		Honeycomb()
		{
			PushLayer(new EditorLayer());
		}

		~Honeycomb() = default;
	};

	Application* CreateApplication()
	{
		return new Honeycomb();
	}
}