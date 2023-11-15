#include "ProfilerGUI.h"

namespace GUI
{
	ProfilerGUI::ProfilerGUI() : ImGuiWindow((char*)"Profiler")
	{

	}

	ProfilerGUI::~ProfilerGUI()
	{

	}

	void ProfilerGUI::Render()
	{
		ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);
		if (ImGui::Begin(_name, &_opened))
		{
			ImGui::Text("Hello !");
			ImGui::End();
		}
	}
}
