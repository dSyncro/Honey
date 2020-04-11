#include "Application.h"

#include <Honey/Logging/Log.h>
#include <Honey/Events/Window/WindowResizeEvent.h>

using namespace Honey;

Application::Application()
{

}

Application::~Application()
{

}

void Application::Run()
{
	WindowResizeEvent e(1280, 720);
	HNY_CORE_TRACE(e);
	while (true);
}