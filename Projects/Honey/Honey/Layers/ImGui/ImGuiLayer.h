#pragma once

#include <Honey/Layers/Layer.h>

namespace Honey {

	/**
	 * @brief Layer on which ImGui stuff happens.
	*/
	class ImGuiLayer final : public Layer {

	public:

		ImGuiLayer();
		~ImGuiLayer();

		/**
		 * @brief Called when ImGuiLayer gets attached.
		*/
		virtual void onAttach() override;

		/**
		 * @brief Called when ImGuiLayer gets detached.
		*/
		virtual void onDetach() override;
		// virtual void OnImGuiRender() override;

		/**
		 * @brief Begin context for ImGui rendering.
		*/
		void begin();

		/**
		 * @brief End context for ImGui rendering.
		*/
		void end();
	};

}
