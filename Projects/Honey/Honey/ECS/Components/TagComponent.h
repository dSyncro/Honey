#pragma once

#include <string>

namespace Honey {

	/**
	 * @brief Tag Component.
	 * It holds the entity tag.
	*/
	struct TagComponent {

		TagComponent() = default;
		~TagComponent() = default;
		TagComponent(const TagComponent&) = default;

		/**
		 * @brief Construct TagComponent.
		 * @param tag The tag.
		*/
		TagComponent(const std::string& tag) : tag(tag) { }

		/**
		 * @brief Entity tag.
		*/
		std::string tag;
	};

}
