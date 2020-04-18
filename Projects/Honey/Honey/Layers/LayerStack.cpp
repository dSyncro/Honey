#include "LayerStack.h"

using namespace Honey;

LayerStack::~LayerStack()
{
	for (Layer* layer : _layers)
	{
		layer->OnDetach();
		delete layer;
	}
}

void LayerStack::PushLayer(Layer* layer)
{
	_layers.emplace(_layers.begin() + _layerInsertIndex, layer);
	_layerInsertIndex++;
}

void LayerStack::PushOverlay(Layer* overlay)
{
	_layers.emplace_back(overlay);
}

void LayerStack::PopLayer(Layer* layer)
{
	std::vector<Layer*>::iterator it = std::find(_layers.begin(), _layers.begin() + _layerInsertIndex, layer);

	if (it == _layers.begin() + _layerInsertIndex) return;
	
	layer->OnDetach();
	_layers.erase(it);
	_layerInsertIndex--;
}

void LayerStack::PopOverlay(Layer* overlay)
{
	std::vector<Layer*>::iterator it = std::find(_layers.begin() + _layerInsertIndex, _layers.end(), overlay);

	if (it == _layers.end()) return;

	overlay->OnDetach();
	_layers.erase(it);
}