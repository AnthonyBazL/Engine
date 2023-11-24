#pragma once

#include "../ImGuiWindow.h"

namespace Engine
{
	class ProfilerGUI : public ImGuiWindow
	{
	public:
		ProfilerGUI();
		~ProfilerGUI();
		void Render() override;
	};
}
