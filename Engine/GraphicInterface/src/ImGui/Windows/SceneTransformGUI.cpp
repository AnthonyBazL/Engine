#include "SceneTransformGUI.h"

namespace GUI
{
	SceneTransformGUI::SceneTransformGUI(Scene* pScene) : ImGuiWindow((char*)"Scene Transform")
	{
		_pScene = pScene;
		_pCamera = _pScene->GetCamera();
		float* camPos = (float*)glm::value_ptr(_pCamera->GetWorldPosition());
		_cameraPosition[0] = camPos[0];
		_cameraPosition[1] = camPos[1];
		_cameraPosition[2] = camPos[2];
	}

	SceneTransformGUI::~SceneTransformGUI()
	{
	}

	void SceneTransformGUI::Render()
	{
		ImGui::ShowDemoWindow();

		if (ImGui::Begin(_name))
		{
			ImGui::Text("Camera position:");
			ImGui::SameLine();
			if (ImGui::DragFloat3("##Camera Position", _cameraPosition))
			{
				_pScene->GetCamera()->SetPosition(glm::make_vec3(_cameraPosition));
			}

			ImGui::End();
		}
	}
}
