#include "SceneCamera.h"

using namespace Honey;
using namespace Honey::Math;

void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
{
	_orthoSize = size;
	_orthoNear = nearClip;
	_orthoFar = farClip;

	RecalculateProjection();
}

void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
{
	_aspectRatio = (float)width / (float)height;
	RecalculateProjection();
}

void SceneCamera::RecalculateProjection()
{
	float orthoLeft = -0.5f * _orthoSize * _aspectRatio;
	float orthoRight = 0.5f * _orthoSize * _aspectRatio;
	float orthoBottom = -0.5f * _orthoSize; 
	float orthoTop = 0.5f * _orthoSize;

	_projection = Matrix4x4::Orthographic(orthoLeft, orthoRight, orthoBottom, orthoTop, _orthoNear, _orthoFar);
}
