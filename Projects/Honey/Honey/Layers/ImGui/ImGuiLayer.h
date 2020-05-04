#pragma once

#include <Honey/Layers/Layer.h>

namespace Honey {

	class ImGuiLayer final : public Layer {

	public:

		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		// virtual void OnImGuiRender() override;

		void Begin();
		void End();
	};

}