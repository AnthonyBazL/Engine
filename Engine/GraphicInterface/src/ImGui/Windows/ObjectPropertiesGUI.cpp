#include "ObjectPropertiesGUI.h"

namespace GUI
{
	ObjectPropertiesGUI::ObjectPropertiesGUI() : ImGuiWindow((char*)"Object Properties")
	{

	}

	ObjectPropertiesGUI::~ObjectPropertiesGUI()
	{
	}

	void ObjectPropertiesGUI::Render()
	{
		if (ImGui::Begin(_name))
		{
			ImGui::Text("World Position: ");
			ImGui::SameLine();
			if (ImGui::DragFloat3("##WorldPosition", _worldPosition))
			{
				//_pScene->GetCamera()->SetPosition(glm::make_vec3(_cameraPosition));
			}

			ImGui::Text("Rotation: ");
			ImGui::SameLine();
			if (ImGui::DragFloat3("##EulerRotation", _eulerRotation))
			{
				//_pScene->GetCamera()->SetPosition(glm::make_vec3(_cameraPosition));
			}

			ImGui::Text("Scale: ");
			ImGui::SameLine();
			if (ImGui::DragFloat3("##Scale", _scale))
			{
				//_pScene->GetCamera()->SetPosition(glm::make_vec3(_cameraPosition));
			}

			ImGui::End();
		}
	}
}
