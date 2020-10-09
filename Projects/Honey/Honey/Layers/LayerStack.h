#pragma once

#include "Layer.h"

#include <vector>

namespace Honey {

	/**
	 * @brief Layer Stack.
	 * Hold layers and keep them in a tidy order.
	*/
	class LayerStack
	{

	public:

		LayerStack() = default;
		~LayerStack();

		/**
		 * @brief Push layer to stack (on top of last layer).
		 * @param layer The layer
		*/
		void pushLayer(Layer* layer);

		/**
		 * @brief Push overlay to stack (on top of everything).
		 * @param overlay The overlay.
		*/
		void pushOverlay(Layer* overlay);

		/**
		 * @brief Pop layer from stack.
		 * @param layer The layer.
		*/
		void popLayer(Layer* layer);

		/**
		 * @brief Pop overlay from stack.
		 * @param overlay The overlay.
		*/
		void popOverlay(Layer* overlay);

		using iterator = std::vector<Layer*>::iterator;
		using reverse_iterator = std::vector<Layer*>::reverse_iterator;
		using const_iterator = std::vector<Layer*>::const_iterator;
		using const_reverse_iterator = std::vector<Layer*>::const_reverse_iterator;

		iterator begin() { return _layers.begin(); }
		iterator end() { return _layers.end(); }
		reverse_iterator rbegin() { return _layers.rbegin(); }
		reverse_iterator rend() { return _layers.rend(); }

		const_iterator begin() const { return _layers.begin(); }
		const_iterator end() const { return _layers.end(); }
		const_reverse_iterator rbegin() const { return _layers.rbegin(); }
		const_reverse_iterator rend() const { return _layers.rend(); }

	private:

		std::vector<Layer*> _layers;
		UInt _layerInsertIndex = 0;
	};

}
