#pragma once

#include "Honey/Core.h"
#include "Layer.h"

#include <vector>

namespace Honey {

	class LayerStack
	{

	public:

		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		inline std::vector<Layer*>::iterator begin() { return _layers.begin(); }
		inline std::vector<Layer*>::iterator end() { return _layers.end(); }
		inline std::vector<Layer*>::reverse_iterator rbegin() { return _layers.rbegin(); }
		inline std::vector<Layer*>::reverse_iterator rend() { return _layers.rend(); }

		inline std::vector<Layer*>::const_iterator begin() const { return _layers.begin(); }
		inline std::vector<Layer*>::const_iterator end() const { return _layers.end(); }
		inline std::vector<Layer*>::const_reverse_iterator rbegin() const { return _layers.rbegin(); }
		inline std::vector<Layer*>::const_reverse_iterator rend() const { return _layers.rend(); }

	private:

		std::vector<Layer*> _layers;
		unsigned int _layerInsertIndex = 0;
	};

}