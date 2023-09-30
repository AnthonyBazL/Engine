#pragma once

#include "ImGuiWindow.h"

namespace GUI
{
	class ProfilerGUI : public ImGuiWindow
	{
	public:
		ProfilerGUI();
		~ProfilerGUI();
		void Render() override;
	};
}
