#pragma once

#include "ImGuiWindow.h"

namespace GUI
{
	class SceneTransformGUI : public ImGuiWindow
	{
	public:
		SceneTransformGUI();
		~SceneTransformGUI();
		void Render() override;
	};
}
