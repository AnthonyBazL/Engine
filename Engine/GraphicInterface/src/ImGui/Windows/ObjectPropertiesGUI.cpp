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
			ImGui::Text("Hello !");
			ImGui::End();
		}
	}
}
