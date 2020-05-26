#include "Sandbox2D.h"

#include <ImGui/imgui.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Sandbox2D::OnAttach()
{
	HNY_PROFILE_FUNCTION();
	_texture = Honey::Texture2D::Create("assets/textures/logo.png");
}

void Sandbox2D::OnDetach()
{
	HNY_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate()
{
	HNY_PROFILE_FUNCTION();

	_cameraController.OnUpdate();
	float deltaTime = Honey::Time::GetDeltaTime();

	HNY_APP_INFO("DeltaTime: {0}", deltaTime);
	HNY_APP_INFO("FPS: {0}", Honey::Time::GetFrameRate());
	HNY_APP_INFO("Frame: {0}", Honey::Time::GetFrameCount());

	_cameraController.OnUpdate();

	Honey::Renderer2D::ResetStatistics();
	Honey::RenderCommand::SetClearColor({ .1f, .1f, .1f, 1 });
	Honey::RenderCommand::Clear();

	Honey::Renderer2D::BeginScene(_cameraController.GetCamera());

	for (int y = 0; y < 3; y++) 
		for (int x = 0; x < 3; x++)
			Honey::Renderer2D::DrawQuad({ x + 5.0f, y + 5.0f }, { 0.9f, 0.9f }, { x / 3.0f, y / 3.0f, 0.8f, 1.0f });

	Honey::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, _squareColor);
	Honey::Renderer2D::DrawQuad({ 0.0f, 5.0f }, { 1.0f, 1.0f }, _texture);

	Honey::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Honey::Event& e)
{
	HNY_PROFILE_FUNCTION();
	_cameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
	HNY_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::Text("Renderer2D Stats");
	const Honey::Renderer2D::Statistics& stats = Honey::Renderer2D::GetStatistics();
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Vertex Count: %d", stats.GetVertexCount());
	ImGui::Text("Index Count: %d", stats.GetIndexCount());
	ImGui::ColorEdit4("Square Color", glm::value_ptr(_squareColor));
	ImGui::End();
}