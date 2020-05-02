#include "Sandbox2D.h"

#include <ImGui/imgui.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Sandbox2D::OnAttach()
{
	
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
	Honey::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, _squareColor);

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