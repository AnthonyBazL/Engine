#pragma once
#if USE_OPENGL
#include "Renderer.h"
#include "../GUI/ImGuiManager.h"
#include <vector>

namespace Engine
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
		double _mousePosX = 0.0;
		double _mousePosY = 0.0;

		int CreateWindow();
		int Render();
		void CleanUp();
		bool PrepareMeshData(MeshData* pMeshData);
		void DrawMesh(Mesh* pMesh);
	};
}
#endif
