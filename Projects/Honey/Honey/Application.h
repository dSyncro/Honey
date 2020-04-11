#pragma once

#include "Core.h"

namespace Honey {

	class HONEY_API Application
	{
	public:

		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();

}