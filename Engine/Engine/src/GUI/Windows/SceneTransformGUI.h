#pragma once

#include "../ImGuiWindow.h"

#ifndef SCENE_H
#include "../../../../Engine/src/Components/Scene.h"
#endif // !SCENE_H

#ifndef CAMERA_H
#include "../../../../Engine/src/Components/Camera.h"
#endif

#ifndef LIGHT_H
#include "../../../../Engine/src/Components/Light.h"
#endif


namespace Engine
{
	class SceneTransformGUI : public ImGuiWindow
	{
	public:
		SceneTransformGUI(Scene* pScene);
		~SceneTransformGUI();
		void Render() override;

	private:
		Camera* _pCamera = nullptr;
		Light* _pLight = nullptr;
		float _cameraPosition[3];
		float _lightPosition[3];
		float _diffuseLightIntensity = 1.0f;
		float _ambiantLightIntensity = 1.0f;
		float _specularLightIntensity = 1.0f;
		float _lightRange = 10.0f;
		float _camFov = 45.0f;
		float _camNear = 0.0f;
		float _camFar = 100.0f;
	};
}
