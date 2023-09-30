#include "ImGuiManager.h"

namespace GraphicInterface
{
	ImGuiManager::ImGuiManager(GLFWwindow* window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); 
		(void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	ImGuiManager::~ImGuiManager()
	{
	}
}