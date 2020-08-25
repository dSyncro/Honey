#pragma once

#include <Honey.h>

using namespace Honey;

class CameraController : public Behaviour {

public:

	float Speed = 1.0f;
	float ZoomSpeed = 5.0f;

	float Size = 10.0f;

	void OnUpdate()
	{
		float deltaTime = Time::GetDeltaTime();

		SceneCamera& camera = GetComponent<CameraComponent>().Camera;
		float scroll = Input::GetMouseScroll();
		Size -= scroll * ZoomSpeed;
		Size = Mathf::Clamp(Size, 0.1f, Mathf::Infinity);
		camera.SetOrthographic(Size, -1.0f, 1.0f);

		TransformComponent& transform = GetComponent<TransformComponent>();
		Math::Vector3 pos = transform.Position;
		if (Input::IsKeyPressed(Keycode::A))
			pos.X -= Size * Speed * deltaTime;
		if (Input::IsKeyPressed(Keycode::D))
			pos.X += Size * Speed * deltaTime;
		if (Input::IsKeyPressed(Keycode::S))
			pos.Y -= Size * Speed * deltaTime;
		if (Input::IsKeyPressed(Keycode::W))
			pos.Y += Size * Speed * deltaTime;
		transform.Position = pos;
	}
};

class CameraScrollController : public Behaviour {

public:

	float ZoomSpeed = 5.0f;

	float Size = 10.0f;

	void OnUpdate()
	{
		float deltaTime = Time::GetDeltaTime();

		SceneCamera& camera = GetComponent<CameraComponent>().Camera;
		float scroll = Input::GetMouseScroll();
		Size -= scroll * ZoomSpeed;
		Size = Mathf::Clamp(Size, 0.1f, Mathf::Infinity);
		camera.SetOrthographic(Size, -1.0f, 1.0f);
	}
};

class CameraWASDController : public Behaviour {

public:

	float Speed = 1.0f;

	void OnUpdate()
	{
		float deltaTime = Time::GetDeltaTime();

		SceneCamera& camera = GetComponent<CameraComponent>().Camera;

		TransformComponent& transform = GetComponent<TransformComponent>();
		CameraScrollController& other = GetComponent<CameraScrollController>();
		Math::Vector3 pos = transform.Position;
		if (Input::IsKeyPressed(Keycode::A))
			pos.X -= other.Size * Speed * deltaTime;
		if (Input::IsKeyPressed(Keycode::D))
			pos.X += other.Size * Speed * deltaTime;
		if (Input::IsKeyPressed(Keycode::S))
			pos.Y -= other.Size * Speed * deltaTime;
		if (Input::IsKeyPressed(Keycode::W))
			pos.Y += other.Size * Speed * deltaTime;
		transform.Position = pos;
	}
};
