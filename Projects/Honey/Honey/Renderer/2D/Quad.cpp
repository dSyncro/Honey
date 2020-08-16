#include "Quad.h"

#include <Honey/Core/Assertion.h>

using namespace Honey;
using namespace Honey::Math;

void Quad::Vertex::Set(const Vector3& position, const Vector4& color, const Vector2& texCoord, float textureIndex, float tilingFactor)
{
	Position = position;
	Color = color;
	TexCoord = texCoord;
	TextureIndex = textureIndex;
	TilingFactor = tilingFactor;
}

Quad::Quad(const Vertex& first, const Vertex& second, const Vertex& third, const Vertex& forth)
{
	Vertices[0] = first;
	Vertices[1] = second;
	Vertices[2] = third;
	Vertices[3] = forth;
}

Quad::Vertex& Quad::operator [](int index)
{
	HNY_CORE_ASSERT(index < 4, "Index out of bonds!");
	return Vertices[index];
}

const Quad::Vertex& Quad::operator [](int index) const
{
	HNY_CORE_ASSERT(index < 4, "Index out of bonds!");
	return Vertices[index];
}
