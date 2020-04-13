#pragma once

#include <Honey/Events/KeyEvents.h>
#include <Honey/Events/MouseEvents.h>
#include <Honey/Events/WindowEvents.h>

#include <Honey/Layers/Layer.h>

namespace Honey {

	class ImGuiLayer : public Layer {

	public:

		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:

		float _time = .0f;
	};

}