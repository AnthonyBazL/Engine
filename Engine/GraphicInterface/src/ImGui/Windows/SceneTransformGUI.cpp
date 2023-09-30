#include "SceneTransformGUI.h"

namespace GUI
{
	SceneTransformGUI::SceneTransformGUI() : ImGuiWindow((char*)"Scene Transform")
	{
	}

	SceneTransformGUI::~SceneTransformGUI()
	{
	}

	void SceneTransformGUI::Render()
	{
		if (ImGui::Begin(_name))
		{
			ImGui::Text("Hello !");
			ImGui::End();
		}
	}
}
