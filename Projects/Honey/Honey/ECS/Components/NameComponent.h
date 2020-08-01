#pragma once

#include <string>

namespace Honey {

	struct NameComponent {

		NameComponent() = default;
		~NameComponent() = default;
		NameComponent(const NameComponent&) = default;
		NameComponent(const std::string& name) : Name(name) { }

		std::string Name;
	};

}
