#pragma once

#include <string>

#include <Honey/Events/Event.h>

namespace Honey {

	class Layer
	{

	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return _name; }

	protected:

		std::string _name;
	};

}
