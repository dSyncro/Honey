#pragma once

#include <Honey.h>

#define REGISTER_COMPONENT_DRAWER(drawer, entity) \
	class drawer {                              \
	public:	                                    \
		HNY_PURE_STATIC(drawer);                \
		static void draw(Entity);       \
	};                                          \
	void drawer::draw(Entity entity)

#define COMPONENT_DRAWER_CLASS(drawer)    \
	class drawer {                        \
	public:	                              \
		HNY_PURE_STATIC(drawer);          \
		static void draw(Entity); \
	};

#define COMPONENT_DRAWER_FUNCTION(drawer, entity) void drawer::draw(Entity entity)
