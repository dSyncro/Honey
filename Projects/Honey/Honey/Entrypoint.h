#pragma once

#include "Application.h"
#include "Core/Log.h"

#ifdef HNY_PLATFORM_WINDOWS

extern Honey::Application* Honey::CreateApplication();

int main(int argc, char** argv)
{
	Honey::Log::Init();

	HNY_PROFILE_BEGIN_SESSION("Startup", "HoneyProfile-Startup.json");
	Honey::Application* app = Honey::CreateApplication();
	HNY_PROFILE_END_SESSION();

	HNY_PROFILE_BEGIN_SESSION("Runtime", "HoneyProfile-Runtime.json");
	app->Run();
	HNY_PROFILE_END_SESSION();

	HNY_PROFILE_BEGIN_SESSION("Shutdown", "HoneyProfile-Shutdown.json");
	delete app;
	HNY_PROFILE_END_SESSION();
}

#endif