#include "ImGuiManager.h"

namespace Engine
{
	ImGuiManager::ImGuiManager(GLFWwindow* pWindow, Engine::Scene* pScene)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		ImGui::StyleColorsDark();

#if USE_OPENGL
		ImGui_ImplGlfw_InitForOpenGL(pWindow, true);
		ImGui_ImplOpenGL3_Init("#version 330");
#elif USE_VULKAN
		// ImGui Initialized in VulkanRenderer class directly for now
#endif

		_windowsMap[ImGuiWindowType::PROFILER] = new ProfilerGUI();
		_windowsMap[ImGuiWindowType::SCENE_TRANSFORM] = new SceneTransformGUI(pScene);
		_windowsMap[ImGuiWindowType::OBJECT_PROPERTIES] = new ObjectPropertiesGUI();

		// TODO: to remove, just here for testing
		// Goal is to select object with mouse clicking
		((ObjectPropertiesGUI*)_windowsMap[ImGuiWindowType::OBJECT_PROPERTIES])->SetObject(pScene->GetMeshes()[2]);
	}

	ImGuiManager::~ImGuiManager()
	{
#if USE_OPENGL
		ImGui_ImplOpenGL3_Shutdown();
#elif USE_VULKAN
		ImGui_ImplVulkan_Shutdown();
#endif
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		for (const auto& window : _windowsMap)
		{
			delete window.second;
		}

		_windowsMap.clear();
	}

	void ImGuiManager::PushNewWindow(ImGuiWindow* pNewWindow)
	{
		_windowsMap.insert({ ImGuiWindowType::APP_WINDOW, pNewWindow });
	}

	void ImGuiManager::Render()
	{
#if USE_OPENGL
		ImGui_ImplOpenGL3_NewFrame();
#elif USE_VULKAN
		ImGui_ImplVulkan_NewFrame();
#endif
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (const auto& window : _windowsMap)
		{
			window.second->Render();
		}

		ImGui::Render();
#if USE_OPENGL
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#elif USE_VULKAN
		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), nullptr); // VK command buffer to pass here
#endif
	}
}