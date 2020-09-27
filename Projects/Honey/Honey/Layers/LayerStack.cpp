#include "LayerStack.h"

using namespace Honey;

/**
 * Layer stack is composed by two kind of layers:
 * - Layers
 * - Overlays
 * 
 * The layer stack is intended to be structured following this rule:
 * - Layers are found firsts
 * - The later a layer got pushed, the higher its index will be
 * - Overlays are found seconds
 * - The later an overlay got pushed, the higher its index will be
 * - Layers are found in range [0; insert index)
 * - Overlays are found in range [insert index, number of elements)
*/

LayerStack::~LayerStack()
{
	// Destroy all layers
	for (Layer* layer : _layers)
	{
		layer->onDetach(); // But before detach them
		delete layer;
	}
}

void LayerStack::pushLayer(Layer* layer)
{
	// Push layer on top of the last pushed one.
	_layers.emplace(_layers.begin() + _layerInsertIndex, layer);
	_layerInsertIndex++;
}

void LayerStack::pushOverlay(Layer* overlay)
{
	// Push overlay on top of everything
	_layers.emplace_back(overlay);
}

void LayerStack::popLayer(Layer* layer)
{
	// Find layer
	std::vector<Layer*>::iterator it = std::find(_layers.begin(), _layers.begin() + _layerInsertIndex, layer);

	// If not found just return
	if (it == _layers.begin() + _layerInsertIndex) return;
	
	layer->onDetach(); // Detach layer
	_layers.erase(it); // Remove it from stack
	_layerInsertIndex--; // Now we have room one index before
}

void LayerStack::popOverlay(Layer* overlay)
{
	// Find overlay
	std::vector<Layer*>::iterator it = std::find(_layers.begin() + _layerInsertIndex, _layers.end(), overlay);

	// If not found just return
	if (it == _layers.end()) return;

	overlay->onDetach(); // Detach overlay
	_layers.erase(it); // Remove it from stack
}
