#pragma once

#include "ImGuiWindow.h"

namespace GUI
{
	class ObjectPropertiesGUI : public ImGuiWindow
	{
	public:
		ObjectPropertiesGUI();
		~ObjectPropertiesGUI();
		void Render() override;
	};
}
