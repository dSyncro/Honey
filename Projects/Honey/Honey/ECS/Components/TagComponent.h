#pragma once

#include <glm/glm.hpp>

namespace Honey {

	struct TagComponent {

		TagComponent() = default;
		~TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) { }

		std::string Tag;
	};

}