#pragma once

#include <string>

namespace Honey {

	struct TagComponent {

		TagComponent() = default;
		~TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag) : Tag(tag) { }

		std::string Tag;
	};

}
