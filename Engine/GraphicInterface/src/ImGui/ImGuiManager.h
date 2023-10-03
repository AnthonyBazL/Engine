#pragma once

#include <map>
#include "Windows/ImGuiWindow.h"
#include "Windows/ProfilerGUI.h"
#include "Windows/SceneTransformGUI.h"
#include "Windows/ObjectPropertiesGUI.h"

#ifndef SCENE_H
#include "../Scene.h"
#endif // !SCENE_H


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
		ImGuiManager(GLFWwindow* window, Scene* pScene);
		~ImGuiManager();
		void Render();

	private:
		std::map<ImGuiWindowType, ImGuiWindow*> _windowsMap;
	};
}

