#include "SceneCamera.h"

using namespace Honey;
using namespace Honey::Math;

void SceneCamera::setOrthographic(Float size, Float nearClip, Float farClip)
{
	_orthoSize = size;
	_orthoNear = nearClip;
	_orthoFar = farClip;

	recalculateProjection();
}

void SceneCamera::setViewportSize(UInt width, UInt height)
{
	_aspectRatio = static_cast<Float>(width) / static_cast<Float>(height);
	recalculateProjection();
}

void SceneCamera::recalculateProjection()
{
	Float orthoLeft = -0.5f * _orthoSize * _aspectRatio;
	Float orthoRight = 0.5f * _orthoSize * _aspectRatio;
	Float orthoBottom = -0.5f * _orthoSize; 
	Float orthoTop = 0.5f * _orthoSize;

	_projection = Matrix4x4::orthographic(orthoLeft, orthoRight, orthoBottom, orthoTop, _orthoNear, _orthoFar);
}
