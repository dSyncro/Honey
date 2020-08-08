#pragma once

#include "Application.h"
#include "Core/Log.h"

extern Honey::Application* Honey::CreateApplication();

#if defined(HNY_PLATFORM_WINDOWS)

#include <Honey/Platform/Windows/Input/WindowsKeyTable.h>

int main(int argc, char** argv)
{
	Honey::Log::Init();
	Honey::WindowsKeyTable::Init();

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

#elif defined(HNY_PLATFORM_GLFW)

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

#else
#	error "Unknown platform!"
#endif
