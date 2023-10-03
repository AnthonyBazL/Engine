#pragma once

#include "ImGuiWindow.h"

#ifndef SCENE_H
#include "../../Scene.h"
#endif // !SCENE_H

#include <glm/gtc/type_ptr.hpp>


namespace GUI
{
	class SceneTransformGUI : public ImGuiWindow
	{
	public:
		SceneTransformGUI(Scene* pScene);
		~SceneTransformGUI();
		void Render() override;

	private:
		Scene* _pScene = nullptr;
		float _cameraPosition[3];
		Camera* _pCamera = nullptr;
	};
}
