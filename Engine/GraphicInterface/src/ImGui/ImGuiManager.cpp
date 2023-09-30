#include "ImGuiManager.h"

namespace GUI
{
	ImGuiManager::ImGuiManager(GLFWwindow* pWindow)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); 
		(void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(pWindow, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		_windowsMap[ImGuiWindowType::PROFILER] = new ProfilerGUI();
		_windowsMap[ImGuiWindowType::SCENE_TRANSFORM] = new SceneTransformGUI();
		_windowsMap[ImGuiWindowType::OBJECT_PROPERTIES] = new ObjectPropertiesGUI();
	}

	ImGuiManager::~ImGuiManager()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		for (const auto& e : _windowsMap)
		{
			delete e.second;
		}

		_windowsMap.clear();
	}

	void ImGuiManager::Render()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (const auto& e : _windowsMap)
		{
			e.second->Render();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}