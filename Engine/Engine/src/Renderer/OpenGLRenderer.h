#pragma once
#if USE_OPENGL
#include "Renderer.h"
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
		double _mousePosX = 0.0;
		double _mousePosY = 0.0;

		int CreateWindow();
		int Render();
		void CleanUp();
		bool PrepareMeshData(MeshData* pMeshData);
		void DrawMesh(Mesh* pMesh);
		void TestComputeShader();
	};
}
#endif
