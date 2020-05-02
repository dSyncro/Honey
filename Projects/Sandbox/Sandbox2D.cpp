#include "Sandbox2D.h"

#include <ImGui/imgui.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Sandbox2D::OnAttach()
{
	_texture = Honey::Texture2D::Create("assets/textures/checkerboard.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate()
{
	_cameraController.OnUpdate();
	float deltaTime = Honey::Time::GetDeltaTime();

	HNY_APP_INFO("DeltaTime: {0}", deltaTime);
	HNY_APP_INFO("FPS: {0}", Honey::Time::GetFrameRate());
	HNY_APP_INFO("Frame: {0}", Honey::Time::GetFrameCount());

	_cameraController.OnUpdate();

	Honey::RenderCommand::SetClearColor({ .1f, .1f, .1f, 1 });
	Honey::RenderCommand::Clear();

	Honey::Renderer2D::BeginScene(_cameraController.GetCamera());

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			Honey::Renderer2D::DrawQuad({ x, y }, { 0.9f, 0.9f }, { x / 10.0f, y / 10.0f, 0.8f, 1.0f });
		}
	}

	Honey::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, _squareColor);
	Honey::Renderer2D::DrawQuad({ 0.0f, 1.0f }, { 1.0f, 1.0f }, _texture);

	Honey::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Honey::Event& e)
{
	_cameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(_squareColor));
	ImGui::End();
}