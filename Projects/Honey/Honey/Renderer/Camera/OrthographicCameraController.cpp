#include "OrthographicCameraController.h"

#include <Honey/Events/EventDispatcher.h>
#include <Honey/Input/Input.h>
#include <Honey/Math/MathFunctions.h>
#include <Honey/Timing/Time.h>

using namespace Honey;

OrthographicCameraController::OrthographicCameraController(Float aspectRatio) 
	: _aspectRatio(aspectRatio), 
	_camera(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel) { }

OrthographicCameraController::OrthographicCameraController(Float width, Float height) : OrthographicCameraController(width / height) {}

void OrthographicCameraController::onUpdate()
{
	HNY_PROFILE_FUNCTION();

	Timestamp deltaTime = Time::getDeltaTime();

	// Do calculations to limit diagonal speed.
	if (Input::isKeyPressed(Keycode::A))
	{
		_position.x -= Mathf::cos(_rotation) * _moveSpeed * deltaTime;
		_position.y -= Mathf::sin(_rotation) * _moveSpeed * deltaTime;
	}
	if (Input::isKeyPressed(Keycode::D))
	{
		_position.x += Mathf::cos(_rotation) * _moveSpeed * deltaTime;
		_position.y += Mathf::sin(_rotation) * _moveSpeed * deltaTime;
	}
	if (Input::isKeyPressed(Keycode::W))
	{
		_position.x += -Mathf::sin(_rotation) * _moveSpeed * deltaTime;
		_position.y +=  Mathf::cos(_rotation) * _moveSpeed * deltaTime;
	}
	if (Input::isKeyPressed(Keycode::S))
	{
		_position.x -= -Mathf::sin(_rotation) * _moveSpeed * deltaTime;
		_position.y -=  Mathf::cos(_rotation) * _moveSpeed * deltaTime;
	}

	_camera.setPosition(_position);

	// Rotation is temporaly disabled
#if 0
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

		_camera.setRotation(_rotation);
	}
#endif

	_moveSpeed = _zoomLevel;
}

void OrthographicCameraController::onEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(HNY_BIND_EVENT_CALLBACK(OrthographicCameraController::onMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(HNY_BIND_EVENT_CALLBACK(OrthographicCameraController::onWindowResize));
}

void OrthographicCameraController::resize(UInt width, UInt height)
{
	_aspectRatio = static_cast<Float>(width) / static_cast<Float>(height);
	_camera.setProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
}

bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e)
{
	HNY_PROFILE_FUNCTION();

	_zoomLevel -= e.getYOffset();
	_zoomLevel = Mathf::max(_zoomLevel, 0.1f);
	_camera.setProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
	return false;
}

bool OrthographicCameraController::onWindowResize(WindowResizeEvent& e)
{
	HNY_PROFILE_FUNCTION();

	resize(e.getSize().width, e.getSize().height);
	return false;
}
