#include "Quad.h"

#include <Honey/Core/Assertion.h>

using namespace Honey;
using namespace Honey::Math;

void Quad::Vertex::Set(const Vector3& position, const Color& color, const Vector2& texCoord, Int textureIndex, const Vector2& tiling)
{
	this->position = position;
	this->color = color;
	this->texCoord = texCoord;
	this->textureIndex = textureIndex;
	this->tiling = tiling;
}

Quad::Quad(const Vertex& first, const Vertex& second, const Vertex& third, const Vertex& forth)
{
	Vertices[0] = first;
	Vertices[1] = second;
	Vertices[2] = third;
	Vertices[3] = forth;
}

Quad::Vertex& Quad::operator [](Int index)
{
	HNY_CORE_ASSERT(index < 4, "Index out of bonds!");
	return Vertices[index];
}

const Quad::Vertex& Quad::operator [](Int index) const
{
	HNY_CORE_ASSERT(index < 4, "Index out of bonds!");
	return Vertices[index];
}
