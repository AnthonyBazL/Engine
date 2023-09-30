#pragma once

#ifndef IMGUI_EXTERNAL
#include "../External/imgui.h"
#include "../External/imgui_impl_glfw.h"
#include "../External/imgui_impl_opengl3.h"
#endif // !IMGUI_EXTERNAL

namespace GUI
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

