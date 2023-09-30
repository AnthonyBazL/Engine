#pragma once
#include "Renderer.h"
#include "ImGui/ImGuiManager.h"
#include <vector>

using namespace GUI;

namespace GraphicInterface
{
	class OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer(Scene* pScene);
		void StartRendering() override;
		void StopRendering() override;

	private:
		ImGuiManager* _pGUIManager = nullptr;
		GLFWwindow* _pWnd = nullptr;

		int CreateWindow();
		int Render();
		GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
	};
}

