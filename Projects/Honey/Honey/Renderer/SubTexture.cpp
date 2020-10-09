#include "SubTexture.h"

using namespace Honey;
using namespace Honey::Math;

SubTexture2D::SubTexture2D(const Reference<Texture2D>& texture, const Math::Vector2& bottomLeft, const Math::Vector2& topRight)
	: _texture(texture)
{
	// Just assign texture coords.
	_texCoords[0] = Math::Vector2(bottomLeft.x, bottomLeft.y);
	_texCoords[1] = Math::Vector2(topRight.x, bottomLeft.y);
	_texCoords[2] = Math::Vector2(topRight.x, topRight.y);
	_texCoords[3] = Math::Vector2(bottomLeft.x, topRight.y);
}

Reference<SubTexture2D> SubTexture2D::createFromCoordinates(
	const Reference<Texture2D>& texture, 
	const Vector2& coords, 
	const Vector2& cellSize, 
	const Vector2& spriteSize)
{
	// Compute bounds

	Vector2 bottomLeft = Vector2(
		coords.x * cellSize.x / texture->getWidth(), 
		coords.y * cellSize.y / texture->getHeight()
	);

	Vector2 topRight = Vector2(
		(coords.x + spriteSize.x) * cellSize.x / texture->getWidth(), 
		(coords.y + spriteSize.y) * cellSize.y / texture->getHeight()
	);

	// Construct subtexture
	return CreateReference<SubTexture2D>(texture, bottomLeft, topRight);
}
