#include "SubTexture.h"

using namespace Honey;
using namespace Honey::Math;

SubTexture2D::SubTexture2D(const Reference<Texture2D>& texture, const Math::Vector2& bottomLeft, const Math::Vector2& topRight)
	: _texture(texture)
{
	_texCoords[0] = Math::Vector2(bottomLeft.X, bottomLeft.Y);
	_texCoords[1] = Math::Vector2(topRight.X, bottomLeft.Y);
	_texCoords[2] = Math::Vector2(topRight.X, topRight.Y);
	_texCoords[3] = Math::Vector2(bottomLeft.X, topRight.Y);
}

Reference<SubTexture2D> SubTexture2D::CreateFromCoordinates(
	const Reference<Texture2D>& texture, 
	const Vector2& coords, 
	const Vector2& cellSize, 
	const Vector2& spriteSize)
{
	Vector2 bottomLeft = Vector2(
		coords.X * cellSize.X / texture->GetWidth(), 
		coords.Y * cellSize.Y / texture->GetHeight()
	);

	Vector2 topRight = Vector2(
		(coords.X + spriteSize.X) * cellSize.X / texture->GetWidth(), 
		(coords.Y + spriteSize.Y) * cellSize.Y / texture->GetHeight()
	);

	return CreateReference<SubTexture2D>(texture, bottomLeft, topRight);
}
