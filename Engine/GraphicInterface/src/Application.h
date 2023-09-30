#pragma once

#if USE_OPENGL
#include "OpenGLRenderer.h"
#endif

#include "Scene.h"

namespace GraphicInterface
{
	class Application
	{
	public:
		Application();
		~Application();
		void Run();

	private:
		Renderer* _pRenderer;
		Scene* _pScene;
	};
}

