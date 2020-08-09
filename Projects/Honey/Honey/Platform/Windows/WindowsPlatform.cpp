#include <Honey/Core/Log.h>
#include <Honey/Core/Platform.h>
#include <Honey/Platform/Windows/Input/WindowsKeyTable.h>

using namespace Honey;

bool Platform::Init()
{
	WindowsKeyTable::Init();
	return true;
}

void Platform::Shutdown()
{
	// TODO: Perform cleanup
}

Platform::API Platform::GetAPI() { return API::Windows; }
