#pragma once

#include <Honey/Core.h>

enum KeyMods : uint16_t {
	Shift    = BIT(0),
	Control  = BIT(1),
	Alt      = BIT(2),
	Super    = BIT(3),
	CapsLock = BIT(4),
	NumLock  = BIT(5)
};
