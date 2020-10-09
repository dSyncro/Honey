#pragma once

#include "Application.h"
#include "Core/Engine.h"

extern Honey::Application* Honey::createApplication();

int main(int argc, char** argv)
{
	Honey::Engine::init();

	HNY_PROFILE_BEGIN_SESSION("Startup", "HoneyProfile-Startup.json");
	Honey::Application* app = Honey::createApplication();
	HNY_PROFILE_END_SESSION();

	HNY_PROFILE_BEGIN_SESSION("Runtime", "HoneyProfile-Runtime.json");
	app->run();
	HNY_PROFILE_END_SESSION();

	HNY_PROFILE_BEGIN_SESSION("Shutdown", "HoneyProfile-Shutdown.json");
	delete app;
	HNY_PROFILE_END_SESSION();

	Honey::Engine::shutdown();
}
