#include "Editor.h"

using namespace Honey;

Entity Editor::_selectedEntity = Entity::null();

void Editor::select(Entity entity)
{
	_selectedEntity = entity;
}

Entity Editor::getSelectedEntity()
{
	return _selectedEntity;
}

template <typename T>
void Editor::deselect()
{
	static_assert("You cannot deselect nothing");
}

template <>
void Editor::deselect<Entity>()
{
	_selectedEntity = Entity::null();
}
