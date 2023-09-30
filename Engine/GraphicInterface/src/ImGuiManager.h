#pragma once

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

namespace GraphicInterface
{
	class ImGuiManager
	{
	public:
		ImGuiManager(GLFWwindow* window);
		~ImGuiManager();
	};
}

