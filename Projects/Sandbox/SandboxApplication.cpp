#include <Honey.h>

class Sandbox : public Honey::Application {

public:

	Sandbox()
	{
		PushOverlay(new Honey::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Honey::Application* Honey::CreateApplication()
{
	return new Sandbox();
}