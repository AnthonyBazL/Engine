#pragma once
#include "Renderer.h"
#include "ImGuiManager.h"

namespace GraphicInterface
{
	class OpenGLRenderer : public Renderer
	{
	public:
		void StartRendering() override;
		void StopRendering() override;

	private:
		ImGuiManager* _pGUIManager;
	};
}

