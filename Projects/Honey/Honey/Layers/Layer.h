#pragma once

#include <string>

#include <Honey/Events/Event.h>

namespace Honey {

	/**
	 * @brief Base class for engine layers.
	*/
	class Layer
	{

	public:

		Layer(const std::string& name = "Layer") : _name(name) {}
		virtual ~Layer() = default;

		/**
		 * @brief Called when Layer gets attached.
		*/
		virtual void onAttach() {}

		/**
		 * @brief Called when Layer gets detached.
		*/
		virtual void onDetach() {}

		/**
		 * @brief Called when Layer gets updated.
		*/
		virtual void onUpdate() {}

		/**
		 * @brief Called when Layer draws ImGui stuff.
		*/
		virtual void onImGuiRender() {}

		/**
		 * @brief Called when Layer receives an event.
		*/
		virtual void onEvent(Event& event) {}

		/**
		 * @brief Get layer name.
		 * @return The layer name.
		*/
		const std::string& getName() const { return _name; }

	protected:

		std::string _name;
	};

}
