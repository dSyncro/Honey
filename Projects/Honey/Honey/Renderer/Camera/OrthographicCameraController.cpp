#include "OrthographicCameraController.h"

#include <Honey/Events/EventDispatcher.h>
#include <Honey/Input/Input.h>
#include <Honey/Math/MathFunctions.h>
#include <Honey/Timing/Time.h>

using namespace Honey;

OrthographicCameraController::OrthographicCameraController(float aspectRatio) 
	: _aspectRatio(aspectRatio), 
	_camera(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel) { }

OrthographicCameraController::OrthographicCameraController(float width, float height) : OrthographicCameraController(width / height) {}

void OrthographicCameraController::OnUpdate()
{
	HNY_PROFILE_FUNCTION();

	Timestamp deltaTime = Time::GetDeltaTime();

	if (Input::isKeyPressed(Keycode::A))
	{
		_position.x -= Mathf::Cos(glm::radians(_rotation)) * _moveSpeed * deltaTime;
		_position.y -= Mathf::Sin(glm::radians(_rotation)) * _moveSpeed * deltaTime;
	}
	if (Input::isKeyPressed(Keycode::D))
	{
		_position.x += Mathf::Cos(glm::radians(_rotation)) * _moveSpeed * deltaTime;
		_position.y += Mathf::Sin(glm::radians(_rotation)) * _moveSpeed * deltaTime;
	}
	if (Input::isKeyPressed(Keycode::W))
	{
		_position.x += -Mathf::Sin(glm::radians(_rotation)) * _moveSpeed * deltaTime;
		_position.y +=  Mathf::Cos(glm::radians(_rotation)) * _moveSpeed * deltaTime;
	}
	if (Input::isKeyPressed(Keycode::S))
	{
		_position.x -= -Mathf::Sin(glm::radians(_rotation)) * _moveSpeed * deltaTime;
		_position.y -=  Mathf::Cos(glm::radians(_rotation)) * _moveSpeed * deltaTime;
	}

	_camera.SetPosition(_position);

	if (_doRotate)
	{
		if (Input::isKeyPressed(Keycode::Q))
			_rotation += _rotationSpeed * deltaTime;
		if (Input::isKeyPressed(Keycode::E))
			_rotation -= _rotationSpeed * deltaTime;

		if (_rotation > 180.0f)
			_rotation -= 360.0f;
		else if (_rotation <= -180.0f)
			_rotation += 360.0f;

		_camera.SetRotation(_rotation);
	}

	_moveSpeed = _zoomLevel;
}

void OrthographicCameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(HNY_BIND_EVENT_CALLBACK(OrthographicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(HNY_BIND_EVENT_CALLBACK(OrthographicCameraController::OnWindowResize));
}

void OrthographicCameraController::Resize(uint32_t width, uint32_t height)
{
	_aspectRatio = (float)width / (float)height;
	_camera.SetProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	HNY_PROFILE_FUNCTION();

	_zoomLevel -= e.getYOffset();
	_zoomLevel = Mathf::Max(_zoomLevel, 0.1f);
	_camera.SetProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
	return false;
}

bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
{
	HNY_PROFILE_FUNCTION();

	Resize(e.getSize().Width, e.getSize().Height);
	return false;
}
