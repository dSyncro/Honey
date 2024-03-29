#pragma once

#include <Honey.h>

using namespace Honey;

class CameraScrollController : public Behaviour {

public:

	Float ZoomSpeed = 5.0f;

	Float Size = 10.0f;

	void onUpdate() override
	{
		Timestamp deltaTime = Time::getDeltaTime();

		SceneCamera& camera = getComponent<CameraComponent>().camera;
		Float scroll = Input::getVMouseScroll();
		Size = camera.getOrthographicSize();
		Size -= scroll * ZoomSpeed;
		Size = Mathf::clamp(Size, 0.1f, Mathf::infinity());
		camera.setOrthographicSize(Size);
	}
};

class CameraWASDController : public Behaviour {

public:

	Float Speed = 1.0f;

	void onUpdate() override
	{
		Timestamp deltaTime = Time::getDeltaTime();

		SceneCamera& camera = getComponent<CameraComponent>().camera;

		TransformComponent& transform = getComponent<TransformComponent>();
		CameraScrollController& other = getComponent<CameraScrollController>();
		Math::Vector3 pos = transform.position;
		if (Input::isKeyPressed(Keycode::A))
			pos.x -= other.Size * Speed * deltaTime;
		if (Input::isKeyPressed(Keycode::D))
			pos.x += other.Size * Speed * deltaTime;
		if (Input::isKeyPressed(Keycode::S))
			pos.y -= other.Size * Speed * deltaTime;
		if (Input::isKeyPressed(Keycode::W))
			pos.y += other.Size * Speed * deltaTime;
		transform.position = pos;
	}
};
