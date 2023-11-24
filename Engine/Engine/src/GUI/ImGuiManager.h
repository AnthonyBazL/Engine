#pragma once

#include <map>
#include "ImGuiWindow.h"

#ifndef SCENE_H
#include "../../../Engine/src/Components/Scene.h"
#endif // !SCENE_H

#include "Windows/ObjectPropertiesGUI.h"
#include "Windows/ProfilerGUI.h"
#include "Windows/SceneTransformGUI.h"

namespace Engine
{
	class ImGuiManager
	{
		enum class ImGuiWindowType
		{
			PROFILER = 0,
			SCENE_TRANSFORM = 1,
			OBJECT_PROPERTIES = 2,
			APP_WINDOW = 3
		};

	public:
		ImGuiManager(GLFWwindow* window, Scene* pScene);
		~ImGuiManager();
		void Render();
		// TODO: Idea is to be able from the app using the engine to also add new window specific to the app
		/*_declspec(dllexport) */void PushNewWindow(ImGuiWindow* pNewWindow);

	private:
		std::map<ImGuiWindowType, ImGuiWindow*> _windowsMap;
	};
}