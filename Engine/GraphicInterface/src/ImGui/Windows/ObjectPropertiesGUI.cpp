#include "ObjectPropertiesGUI.h"
#include <GLM/gtc/type_ptr.hpp>

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
			if (ImGui::DragFloat3("##WorldPosition", _worldPosition, 0.1f))
			{
				if (_pMesh != nullptr)
				{
					_pMesh->Translate(glm::make_vec3(_worldPosition));
				}
			}

			ImGui::Text("Rotation: ");
			ImGui::SameLine();
			if (ImGui::DragFloat3("##EulerRotation", _eulerRotation))
			{
				if (_pMesh != nullptr)
				{
					_pMesh->Rotate(glm::make_vec3(_eulerRotation));
				}
			}

			ImGui::Text("Scale: ");
			ImGui::SameLine();
			if (ImGui::DragFloat3("##Scale", _scale, 0.1f))
			{
				if (_pMesh != nullptr)
				{
					_pMesh->Scale(glm::make_vec3(_scale));
				}
			}

			ImGui::End();
		}
	}
	void ObjectPropertiesGUI::SetObject(Mesh* pMesh)
	{
		_pMesh = pMesh;
	}
}
