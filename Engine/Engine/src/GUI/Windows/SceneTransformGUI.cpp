#include "SceneTransformGUI.h"

namespace Engine
{
	SceneTransformGUI::SceneTransformGUI(Scene* pScene) : ImGuiWindow((char*)"Scene Transform")
	{
		_pCamera = pScene->GetCamera();
		float* camPos = _pCamera->GetWorldPosition();
		_cameraPosition[0] = camPos[0];
		_cameraPosition[1] = camPos[1];
		_cameraPosition[2] = camPos[2];
		_camFar = _pCamera->GetFar();
		_camNear = _pCamera->GetNear();
		_camFov = _pCamera->GetFov();

		_pLight = pScene->GetLight();
		float* lightPos = _pLight->GetWorldPosition();
		_lightPosition[0] = lightPos[0];
		_lightPosition[1] = lightPos[1];
		_lightPosition[2] = lightPos[2];

		_diffuseLightIntensity = _pLight->GetDiffuseIntensity();
		_ambiantLightIntensity = _pLight->GetAmbiantIntensity();
		_specularLightIntensity = _pLight->GetSpecularIntensity();
	}

	SceneTransformGUI::~SceneTransformGUI()
	{
	}

	void SceneTransformGUI::Render()
	{
		if (ImGui::Begin(_name, &_opened))
		{
			// Camera settings
			if (ImGui::CollapsingHeader("Camera"))
			{
				ImGui::Text("Position:");
				ImGui::SameLine();
				if (ImGui::DragFloat3("##Camera Position", _cameraPosition))
				{
					_pCamera->SetWorldPosition(_cameraPosition);
				}

				ImGui::Text("FOV:");
				ImGui::SameLine();
				if (ImGui::DragFloat("##Camera FOV", &_camFov))
				{
					_pCamera->SetFov(_camFov);
				}

				ImGui::Text("Far:");
				ImGui::SameLine();
				if (ImGui::DragFloat("##Camera Far", &_camFar))
				{
					_pCamera->SetFar(_camFar);
				}

				ImGui::Text("Near:");
				ImGui::SameLine();
				if (ImGui::DragFloat("##Camera Near", &_camNear))
				{
					_pCamera->SetNear(_camNear);
				}

				ImGui::Spacing();
			}

			// Light settings
			if (ImGui::CollapsingHeader("Light"))
			{
				ImGui::Text("Position:");
				ImGui::SameLine();
				if (ImGui::DragFloat3("##Light Position", _lightPosition))
				{
					_pLight->SetWorldPosition(_lightPosition);
				}

				ImGui::Text("Diffuse intensity:");
				ImGui::SameLine();
				if (ImGui::DragFloat("##Diffuse Light Intensity", &_diffuseLightIntensity, 0.01f))
				{
					_pLight->SetDiffuseIntensity(_diffuseLightIntensity);
				}

				ImGui::Text("Ambiant intensity:");
				ImGui::SameLine();
				if (ImGui::DragFloat("##Ambiant Light Intensity", &_ambiantLightIntensity, 0.01f))
				{
					_pLight->SetAmbiantIntensity(_ambiantLightIntensity);
				}

				ImGui::Text("Specular intensity:");
				ImGui::SameLine();
				if (ImGui::DragFloat("##Specular Light Intensity", &_specularLightIntensity, 0.01f))
				{
					_pLight->SetSpecularIntensity(_specularLightIntensity);
				}

				ImGui::Text("Range:");
				ImGui::SameLine();
				if (ImGui::DragFloat("##Light Range", &_lightRange))
				{
					_pLight->SetRange(_lightRange);
				}

				ImGui::Spacing();
			}

			ImGui::End();
		}
	}
}
