#include "OrthographicCameraController.h"

#include <Honey/Timing/Time.h>
#include <Honey/Input/Input.h>
#include <Honey/Events/EventDispatcher.h>

using namespace Honey;

OrthographicCameraController::OrthographicCameraController(float aspectRatio) 
	: _aspectRatio(aspectRatio), 
	_camera(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel)
{

}

OrthographicCameraController::OrthographicCameraController(float width, float height) : OrthographicCameraController(width / height) {}

void OrthographicCameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(HNY_BIND_EVENT_CALLBACK(OrthographicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(HNY_BIND_EVENT_CALLBACK(OrthographicCameraController::OnWindowResize));
}

void OrthographicCameraController::OnUpdate()
{
	HNY_PROFILE_FUNCTION();

	Timestamp deltaTime = Time::GetDeltaTime();

	if (Input::IsKeyPressed(Keycode::A))
		_position.x -= _moveSpeed * deltaTime;
	if (Input::IsKeyPressed(Keycode::D))
		_position.x += _moveSpeed * deltaTime;
	if (Input::IsKeyPressed(Keycode::S))
		_position.y -= _moveSpeed * deltaTime;
	if (Input::IsKeyPressed(Keycode::W))
		_position.y += _moveSpeed * deltaTime;

	if (Input::IsKeyPressed(Keycode::Q))
		_rotation -= _rotationSpeed * deltaTime;
	if (Input::IsKeyPressed(Keycode::E))
		_rotation += _rotationSpeed * deltaTime;

	_camera.SetPosition(_position);
	_camera.SetRotation(_rotation);
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	HNY_PROFILE_FUNCTION();

	_zoomLevel -= e.GetYOffset();
	_zoomLevel = std::fmax(_zoomLevel, 0.1f);
	_camera.SetProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
	return false;
}

bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
{
	HNY_PROFILE_FUNCTION();

	_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
	_camera.SetProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
	return false;
}