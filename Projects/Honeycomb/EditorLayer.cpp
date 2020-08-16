#include "EditorLayer.h"

#include <ImGui/imgui.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Honey;

class CameraController : public ScriptableEntity {

public:

	float Speed = 5.0f;
	float ZoomSpeed = 8.0f;

	float Size = 10.0f;

	void OnCreate()
	{

	}

	void OnUpdate()
	{
		float deltaTime = Time::GetDeltaTime();

		SceneCamera& camera = GetComponent<CameraComponent>().Camera;
		if (Input::IsKeyPressed(Keycode::Up))
			Size -= ZoomSpeed * deltaTime;
		if (Input::IsKeyPressed(Keycode::Down))
			Size += ZoomSpeed * deltaTime;
		camera.SetOrthographic(Size, -1.0f, 1.0f);

		Transform& transform = GetComponent<TransformComponent>().Transform;
		Math::Vector3 pos = transform.Position;
		if (Input::IsKeyPressed(Keycode::A))
			pos.X -= Speed * deltaTime; 
		if (Input::IsKeyPressed(Keycode::D))
			pos.X += Speed * deltaTime; 
		if (Input::IsKeyPressed(Keycode::S))
			pos.Y -= Speed * deltaTime;
		if (Input::IsKeyPressed(Keycode::W))
			pos.Y += Speed * deltaTime; 
		transform.Position = pos;
	}

	void OnDestroy()
	{

	}
};

void EditorLayer::OnAttach()
{
	HNY_PROFILE_FUNCTION();

    _activeScene = CreateReference<Scene>();

    _camera = _activeScene->CreateEntity("Main Camera", "Main");
    _camera.AddComponent<CameraComponent>();
	_camera.AddComponent<NativeScriptComponent>().Bind<CameraController>();
	
	_entity = _activeScene->CreateEntity();
    _entity.AddComponent<SpriteRendererComponent>();

	_texture = Texture2D::Create("assets/textures/logo.png");

    FrameBufferSpecification specification = { 1280, 720 };
    _frameBuffer = FrameBuffer::Create(specification);
}

void EditorLayer::OnDetach()
{
	HNY_PROFILE_FUNCTION();
}

void EditorLayer::OnUpdate()
{
	HNY_PROFILE_FUNCTION();

	Timestamp deltaTime = Time::GetDeltaTime();
	HNY_CORE_INFO("Delta Time: {0}", deltaTime);
	
	_cameraController.OnUpdate();

	Renderer2D::ResetStatistics();

    _frameBuffer->Bind();

	RenderCommand::SetClearColor({ .1f, .1f, .1f, 1 });
	RenderCommand::Clear();

    _activeScene->OnUpdate();

    _frameBuffer->Unbind();
}

void EditorLayer::OnEvent(Honey::Event& e)
{
	HNY_PROFILE_FUNCTION();
	_cameraController.OnEvent(e);
}

void EditorLayer::OnImGuiRender()
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

            if (ImGui::MenuItem("Close")) Application::Get().Close();
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    {
        HNY_PROFILE_SCOPE("Settings");
        ImGui::Begin("Settings");
        ImGui::Text("Renderer2D Stats");
        const Renderer2D::Statistics& stats = Renderer2D::GetStatistics();
        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quad Count: %d", stats.QuadCount);
        ImGui::Text("Vertex Count: %d", stats.GetVertexCount());
        ImGui::Text("Index Count: %d", stats.GetIndexCount());
		ImGui::Text("Frame Rate: %f", Time::GetFrameRate());
		ImGui::Text("Frame Count: %d", Time::GetFrameCount());
        ImGui::ColorEdit4("Square Color", (float*)&_entity.GetComponent<SpriteRendererComponent>().Color);
        ImGui::End();
    }

    {
        HNY_PROFILE_SCOPE("Viewport");

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
        ImGui::Begin("Viewport");
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

        if (viewportPanelSize.x != _viewportSize.X || viewportPanelSize.y != _viewportSize.Y)
        {
            _frameBuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
            _viewportSize = { viewportPanelSize.x, viewportPanelSize.y };
            _cameraController.Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			_activeScene->OnViewportResize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
        }

        ImGui::Image((void*)_frameBuffer->GetColorAttachmentRendererID(), ImVec2{ _viewportSize.X, _viewportSize.Y }, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
        ImGui::PopStyleVar();
    }

    ImGui::End();
}
