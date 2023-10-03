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

	private:
		float _eulerRotation[3] = { 0.0f, 0.0f, 0.0f };
		float _worldPosition[3] = { 0.0f, 0.0f, 0.0f };
		float _scale[3] = { 1.0f , 1.0f, 1.0f };
	};
}
