#include "ObjectPropertiesGUI.h"

namespace Engine
{
	ObjectPropertiesGUI::ObjectPropertiesGUI() : ImGuiWindow((char*)"Object Properties")
	{
		
	}

	ObjectPropertiesGUI::~ObjectPropertiesGUI()
	{
	}

	void ObjectPropertiesGUI::Render()
	{
		if (ImGui::Begin(_name, &_opened))
		{
			ImGui::Text("World Position: ");
			ImGui::SameLine();
			if (ImGui::DragFloat3("##WorldPosition", _worldPosition, 0.1f))
			{
				if (_pMesh != nullptr)
				{
					_pMesh->Translate(_worldPosition);
				}
			}

			ImGui::Text("Rotation: ");
			ImGui::SameLine();
			if (ImGui::DragFloat3("##EulerRotation", _eulerRotation))
			{
				if (_pMesh != nullptr)
				{
					_pMesh->Rotate(_eulerRotation);
				}
			}

			ImGui::Text("Scale: ");
			ImGui::SameLine();
			if (ImGui::DragFloat3("##Scale", _scale, 0.1f))
			{
				if (_pMesh != nullptr)
				{
					_pMesh->Scale(_scale);
				}
			}

			ImGui::Text("Shininess: ");
			ImGui::SameLine();
			if (ImGui::DragFloat("##Shininess", &_shininess, 0.1f))
			{
				if (_pMesh != nullptr)
				{
					_pMesh->SetShininess(_shininess);
				}
			}

			ImGui::End();
		}
	}
	void ObjectPropertiesGUI::SetObject(Mesh* pMesh)
	{
		_pMesh = pMesh;
		_shininess = _pMesh->GetShininess();
	}
}
