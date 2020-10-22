/**
 * @file NameComponent.h
*/

#pragma once

#include <string>

namespace Honey {

	/**
	 * @brief Name Component.
	 * It holds the entity name.
	*/
	struct NameComponent {

		NameComponent() = default;
		~NameComponent() = default;

		/**
		 * @brief Construct NameComponent.
		 * @param name The name.
		*/
		NameComponent(const std::string& name) : name(name) { }

		NameComponent(const NameComponent&) = default;

		/**
		 * @brief Entity name.
		*/
		std::string name;
	};

}
