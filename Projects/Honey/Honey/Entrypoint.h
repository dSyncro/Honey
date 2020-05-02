#pragma once

#include "Application.h"
#include "Core/Log.h"

#ifdef HNY_PLATFORM_WINDOWS

extern Honey::Application* Honey::CreateApplication();

int main(int argc, char** argv)
{
	Honey::Log::Init();

	HNY_APP_INFO("App logger attached");
	HNY_CORE_INFO("Core logger attached");

	Honey::Application* app = Honey::CreateApplication();
	app->Run();
	delete app;
}

#endif