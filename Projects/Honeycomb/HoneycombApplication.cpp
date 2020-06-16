#include "EditorLayer.h"

#include <Honey/Entrypoint.h>

namespace Honey {

	class Honeycomb : public Application {

	public:

		Honeycomb()
		{
			PushLayer(new EditorLayer());
			SetTitle("Honeycomb - Editor");
		}

		~Honeycomb() = default;
	};

	Application* CreateApplication()
	{
		return new Honeycomb();
	}
}