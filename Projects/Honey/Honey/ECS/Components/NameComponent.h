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
		NameComponent(const NameComponent&) = default;
		NameComponent(const std::string& name) : name(name) { }

		/**
		 * @brief Entity name.
		*/
		std::string name;
	};

}
