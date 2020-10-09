#include "OrthographicCamera.h"

#include <Honey/Core/Profiling.h>

using namespace Honey;
using namespace Honey::Math;

OrthographicCamera::OrthographicCamera(Float left, Float right, Float bottom, Float top)
	: _projectionMatrix(Matrix4x4::orthographic(left, right, bottom, top, -1.0f, 1.0f)), _viewMatrix(1.0f)
{
	HNY_PROFILE_FUNCTION();

	_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
}

void OrthographicCamera::setProjection(Float left, Float right, Float bottom, Float top)
{
	HNY_PROFILE_FUNCTION();

	_projectionMatrix = Matrix4x4::orthographic(left, right, bottom, top, -1.0f, 1.0f);
	_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
}

void OrthographicCamera::setPosition(const Math::Vector3& position)
{ 
	_position = position; 
	recalculateViewMatrix(); 
}

void OrthographicCamera::setRotation(Float rotation)
{ 
	_rotation = rotation; 
	recalculateViewMatrix(); 
}

void OrthographicCamera::recalculateViewMatrix()
{
	HNY_PROFILE_FUNCTION();

	Matrix4x4 transform = 
		Matrix4x4::translate(_position) 
		* Matrix4x4::rotate(_rotation, Math::Vector3(0.0f, 0.0f, 1.0f));

	_viewMatrix = transform.inverse();
	_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
}
