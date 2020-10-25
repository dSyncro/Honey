#pragma once

#include <Honey.h>

namespace Honey {

	struct ComponentInfo {

		Entity entity = Entity::null();
		bool isNodeOpened = false;
		bool shouldComponentBeRemoved = false;

	};

}

#define REGISTER_COMPONENT_DRAWER(drawer, info) \
	class drawer {                              \
	public:	                                    \
		HNY_PURE_STATIC(drawer);                \
		static void draw(ComponentInfo&);       \
	};                                          \
	void drawer::draw(ComponentInfo& info)

#define COMPONENT_DRAWER_CLASS(drawer)    \
	class drawer {                        \
	public:	                              \
		HNY_PURE_STATIC(drawer);          \
		static void draw(ComponentInfo&); \
	};

#define COMPONENT_DRAWER_FUNCTION(drawer, info) void drawer::draw(ComponentInfo& info)
