#include "OrthographicCamera.h"

#include <Honey/Core/Profiling.h>

#include <glm/gtc/matrix_transform.hpp>

using namespace Honey;

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	: _projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), _viewMatrix(1.0f)
{
	HNY_PROFILE_FUNCTION();

	_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
	HNY_PROFILE_FUNCTION();

	_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
}

void OrthographicCamera::SetPosition(const glm::vec3& position)
{ 
	_position = position; 
	RecalculateViewMatrix(); 
}

void OrthographicCamera::SetRotation(float rotation) 
{ 
	_rotation = rotation; 
	RecalculateViewMatrix(); 
}

void OrthographicCamera::RecalculateViewMatrix()
{
	HNY_PROFILE_FUNCTION();

	glm::mat4 transform = 
		glm::translate(glm::mat4(1.0f), _position) 
		* glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0.0f, 0.0f, 1.0f));

	_viewMatrix = glm::inverse(transform);
	_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
}