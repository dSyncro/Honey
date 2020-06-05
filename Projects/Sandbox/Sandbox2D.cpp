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
	Honey::Renderer2D::DrawQuad({ 0.0f, 1.0f }, { 1.0f, 1.0f }, _texture);

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

    static bool isDockspaceEnabled = true;
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &isDockspaceEnabled, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen) ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Docking"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

            if (ImGui::MenuItem("Close")) Honey::Application::Get().Close();
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    {
        HNY_PROFILE_SCOPE("Settings");
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

    ImGui::End();
}