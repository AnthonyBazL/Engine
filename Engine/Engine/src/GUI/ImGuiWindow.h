#pragma once

#ifndef IMGUI_EXTERNAL
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#if USE_OPENGL
#include <ImGui/imgui_impl_opengl3.h>
#elif USE_VULKAN
#include <ImGui/imgui_impl_vulkan.h>
#endif
#endif // !IMGUI_EXTERNAL

namespace Engine
{
	class ImGuiWindow
	{
	public:
		ImGuiWindow(char* name) { _name = name; };
		virtual ~ImGuiWindow() {};
		virtual void Render() = 0;

	protected:
		char* _name;
		bool _opened = false;
	};
}

