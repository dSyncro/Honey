#include "SceneCamera.h"

using namespace Honey;
using namespace Honey::Math;

void SceneCamera::setOrthographic(Float size, Float nearClip, Float farClip)
{
	_projectionType = ProjectionType::Orthographic;

	_orthoSize = size;
	_orthoNear = nearClip;
	_orthoFar = farClip;

	recalculateProjection();
}

void SceneCamera::setPerspective(Float verticalFOV, Float nearClip, Float farClip)
{
	_projectionType = ProjectionType::Perspective;

	_perspectiveFOV = verticalFOV;
	_perspectiveNear = nearClip;
	_perspectiveFar = farClip;

	recalculateProjection();
}

void SceneCamera::setViewportSize(UInt width, UInt height)
{
	_aspectRatio = static_cast<Float>(width) / static_cast<Float>(height);
	recalculateProjection();
}

void SceneCamera::recalculateProjection()
{
	switch (_projectionType)
	{
		case ProjectionType::Perspective: recalculatePerspectiveProjection(); return;
		case ProjectionType::Orthographic: recalculateOrthographicProjection(); return;
		default: return;
	}
}

void SceneCamera::recalculatePerspectiveProjection()
{
	_projection = Matrix4x4::perspective(_perspectiveFOV, _aspectRatio, _perspectiveNear, _perspectiveFar);
}

void SceneCamera::recalculateOrthographicProjection()
{
	Float orthoLeft = -0.5f * _orthoSize * _aspectRatio;
	Float orthoRight = 0.5f * _orthoSize * _aspectRatio;
	Float orthoBottom = -0.5f * _orthoSize;
	Float orthoTop = 0.5f * _orthoSize;

	_projection = Matrix4x4::orthographic(orthoLeft, orthoRight, orthoBottom, orthoTop, _orthoNear, _orthoFar);
}
