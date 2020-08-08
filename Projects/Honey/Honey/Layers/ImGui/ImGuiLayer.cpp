#include "ImGuiLayer.h"

#include <Honey/Application.h>

#include <Honey/Events/EventDispatcher.h>

#include <Honey/Events/KeyEvents.h>
#include <Honey/Events/MouseEvents.h>
#include <Honey/Events/WindowEvents.h>



#if defined(HNY_PLATFORM_WINDOWS)
#	include <Honey/Platform/ImGui/ImGuiWin32Implementation.h>
#elif defined(HNY_PLATFORM_GLFW)
#	include <Honey/Platform/ImGui/ImGuiGlfwImplementation.h>
#endif
#include <Honey/Platform/ImGui/ImGuiOpenGLRender.h>

extern "C" {
#include <GLFW/glfw3.h>
}

using namespace Honey;

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

ImGuiLayer::~ImGuiLayer() = default;

void ImGuiLayer::OnAttach()
{
    HNY_PROFILE_FUNCTION();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    Application& app = Application::Get();
    GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

    // Setup Platform/Renderer bindings
#if defined(HNY_PLATFORM_WINDOWS)
	ImGui_ImplWin32_Init(app.GetWindow().GetNativeWindow());
#elif defined(HNY_PLATFORM_GLFW)
	ImGui_ImplGlfw_InitForOpenGL(window, true);
#endif
    ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDetach()
{
    HNY_PROFILE_FUNCTION();

    ImGui_ImplOpenGL3_Shutdown();
#if defined(HNY_PLATFORM_WINDOWS)
	ImGui_ImplWin32_Shutdown();
#elif defined(HNY_PLATFORM_GLFW)
	ImGui_ImplGlfw_Shutdown();
#endif
    ImGui::DestroyContext();
}

void ImGuiLayer::Begin()
{
    HNY_PROFILE_FUNCTION();

    ImGui_ImplOpenGL3_NewFrame();
#if defined(HNY_PLATFORM_WINDOWS)
	ImGui_ImplWin32_NewFrame();
#elif defined(HNY_PLATFORM_GLFW)
	ImGui_ImplGlfw_NewFrame();
#endif
    ImGui::NewFrame();
}

void ImGuiLayer::End()
{
    HNY_PROFILE_FUNCTION();

    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
	#if defined(HNY_PLATFORM_WINDOWS)
		HWND win = (HWND)app.GetWindow().GetNativeWindow();
		HDC hdc = GetDC(win);
		HGLRC backup_current_context = wglGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		wglMakeCurrent(hdc, backup_current_context);
	#elif defined(HNY_PLATFORM_GLFW)
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
	#endif
    }
}
