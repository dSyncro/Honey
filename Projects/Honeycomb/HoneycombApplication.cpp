#include <Honeycomb/Editor/EditorLayer.h>

#include <Honey/Entrypoint.h>

namespace Honey {

	class Honeycomb : public Application {

	public:

		Honeycomb()
		{
			pushLayer(new EditorLayer());
			setTitle("Honeycomb - Editor");
		}

		~Honeycomb() = default;
	};

	Application* createApplication()
	{
		return new Honeycomb();
	}
}
