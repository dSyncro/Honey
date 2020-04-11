#pragma once

#include "Application.h"
#include "Logging/Log.h"

#ifdef HNY_PLATFORM_WINDOWS

extern Honey::Application* Honey::CreateApplication();

int main(int argc, char** argv)
{
	Honey::Log::Init();

	HNY_APP_INFO("info");
	HNY_CORE_INFO("info");

	Honey::Application* app = Honey::CreateApplication();
	app->Run();
	delete app;
}

#endif