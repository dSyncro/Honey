#pragma once

#include <Honey.h>

using namespace Honey;

class CameraScrollController : public Behaviour {

public:

	float ZoomSpeed = 5.0f;

	float Size = 10.0f;

	void onUpdate() override
	{
		float deltaTime = Time::GetDeltaTime();

		SceneCamera& camera = getComponent<CameraComponent>().camera;
		float scroll = Input::getVMouseScroll();
		Size -= scroll * ZoomSpeed;
		Size = Mathf::Clamp(Size, 0.1f, Mathf::infinity());
		camera.SetOrthographic(Size, -1.0f, 1.0f);
	}
};

class CameraWASDController : public Behaviour {

public:

	float Speed = 1.0f;

	void onUpdate() override
	{
		float deltaTime = Time::GetDeltaTime();

		SceneCamera& camera = getComponent<CameraComponent>().camera;

		TransformComponent& transform = getComponent<TransformComponent>();
		CameraScrollController& other = getComponent<CameraScrollController>();
		Math::Vector3 pos = transform.position;
		if (Input::isKeyPressed(Keycode::A))
			pos.X -= other.Size * Speed * deltaTime;
		if (Input::isKeyPressed(Keycode::D))
			pos.X += other.Size * Speed * deltaTime;
		if (Input::isKeyPressed(Keycode::S))
			pos.Y -= other.Size * Speed * deltaTime;
		if (Input::isKeyPressed(Keycode::W))
			pos.Y += other.Size * Speed * deltaTime;
		transform.position = pos;
	}
};
