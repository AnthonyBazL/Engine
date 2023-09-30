#pragma once

#include <map>
#include "Windows/ImGuiWindow.h"
#include "Windows/ProfilerGUI.h"
#include "Windows/SceneTransformGUI.h"
#include "Windows/ObjectPropertiesGUI.h"

namespace GUI
{
	class ImGuiManager
	{
		enum class ImGuiWindowType
		{
			PROFILER			= 0,
			SCENE_TRANSFORM		= 1,
			OBJECT_PROPERTIES	= 2
		};

	public:
		ImGuiManager(GLFWwindow* window);
		~ImGuiManager();
		void Render();

	private:
		std::map<ImGuiWindowType, ImGuiWindow*> _windowsMap;
	};
}

