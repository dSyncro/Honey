#include "EditorLayer.h"

#include <ImGui/imgui.h>

#include "Scripts.h"

using namespace Honey;

void EditorLayer::onAttach()
{
	HNY_PROFILE_FUNCTION();

	_activeScene = CreateReference<Scene>();

	_camera = _activeScene->createEntity("Main Camera", "Main");
	_camera.addComponent<CameraComponent>();

	NativeScriptComponent& scriptComponent = NativeScriptComponent::attach(_camera);
	scriptComponent.addBehaviour<CameraScrollController>();
	scriptComponent.addBehaviour<CameraWASDController>();

	_entity = _activeScene->createEntity();
	_entity.addComponent<SpriteRendererComponent>();

	_texture = Texture2D::create("assets/textures/logo.png");

	Reference<SubTexture2D> a = SubTexture2D::createFromCoordinates(_texture, { 0, 0 }, { 1024, 1024 });
	Reference<SubTexture2D> b = SubTexture2D::createFromCoordinates(_texture, { 1, 1 }, { 1024, 1024 });
	_spriteA = _activeScene->createEntity("Sprite A");
	_spriteB = _activeScene->createEntity("Sprite B");
	_spriteA.getComponent<TransformComponent>().position = Math::Vector3(1.0f, 1.0f, 0.0f);
	_spriteB.getComponent<TransformComponent>().position = Math::Vector3(2.0f, 2.0f, 0.0f);
	Reference<Sprite> spriteA = Sprite::create(a);
	Reference<Sprite> spriteB = Sprite::create(b);
	_spriteA.addComponent<SpriteRendererComponent>(spriteA);
	_spriteB.addComponent<SpriteRendererComponent>(spriteB);

    FrameBufferSpecification specification = { 1280, 720 };
    _frameBuffer = FrameBuffer::create(specification);

	_font = Font::createFromFile("assets/fonts/Lato-Regular.ttf");
	_atlas = FontAtlas::create(_font, 32);
	Reference<Sprite> fontAtlas = Sprite::create(_atlas->_texture);
	Entity fae = _activeScene->createEntity("FontAtlas");
	fae.getComponent<TransformComponent>().position = Math::Vector3(3.0f, 3.0f, 0.0f);
	fae.getComponent<TransformComponent>().scale = Math::Vector3(5.0f, 5.0f, 5.0f);
	fae.addComponent<SpriteRendererComponent>(fontAtlas);

	Entity text = _activeScene->createEntity("Text");
	text.addComponent<TextComponent>();
	text.getComponent<TextComponent>().text = "This is a Text!";
	text.getComponent<TextComponent>().atlas = _atlas;

	_activeScene->onStart();
	_hierarchy.SetContext(_activeScene);
}

void EditorLayer::onDetach()
{
	HNY_PROFILE_FUNCTION();
}

void EditorLayer::onUpdate()
{
	HNY_PROFILE_FUNCTION();

	Timestamp deltaTime = Time::getDeltaTime();
	HNY_CORE_INFO("Delta Time: {0}", (float)deltaTime);
	
	_cameraController.onUpdate();

	Renderer2D::resetStatistics();

    _frameBuffer->bind();

	RenderCommand::setClearColor({ .1f, .1f, .1f, 1 });
	RenderCommand::clear();

    _activeScene->onUpdate();

    _frameBuffer->unbind();
}

void EditorLayer::onEvent(Honey::Event& e)
{
	HNY_PROFILE_FUNCTION();
	_cameraController.onEvent(e);
}

void EditorLayer::onImGuiRender()
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

            if (ImGui::MenuItem("Close")) Application::get().close();
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    {
        HNY_PROFILE_SCOPE("Settings");
        ImGui::Begin("Settings");
        ImGui::Text("Renderer2D Stats");
        const Renderer2D::Statistics& stats = Renderer2D::getStatistics();
        ImGui::Text("Draw Calls: %d", stats.drawCalls);
        ImGui::Text("Quad Count: %d", stats.quadCount);
        ImGui::Text("Vertex Count: %d", stats.getVertexCount());
        ImGui::Text("Index Count: %d", stats.getIndexCount());
		ImGui::Text("Frame Rate: %f", (float)Time::getFrameRate());
		ImGui::Text("Frame Count: %d", Time::getFrameCount());
        ImGui::ColorEdit4("Square Color", (float*)&_entity.getComponent<SpriteRendererComponent>().tint);
        ImGui::End();
    }

    {
        HNY_PROFILE_SCOPE("Viewport");

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
        ImGui::Begin("Viewport");
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

        if (viewportPanelSize.x != _viewportSize.x || viewportPanelSize.y != _viewportSize.y)
        {
            _frameBuffer->resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
            _viewportSize = { viewportPanelSize.x, viewportPanelSize.y };
            _cameraController.resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			_activeScene->onViewportResize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
        }

        ImGui::Image((void*)(uintptr_t)_frameBuffer->getColorAttachmentRendererID(), ImVec2{ _viewportSize.x, _viewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
        ImGui::PopStyleVar();
    }

    ImGui::End();

	_hierarchy.OnImGuiRender();
}
