#pragma once
#include "src/Renderer/OpenGLRenderer.h"
#include "src/Renderer/VulkanRenderer.h"

namespace Engine
{
	class Core
	{
	public:
		_declspec(dllexport) Core();
		_declspec(dllexport) ~Core();

		_declspec(dllexport) static Core& GetInstance()
		{
			static Core instance;
			return instance;
		}

		_declspec(dllexport) void Initialize();

	private:
		Core(Core const&);
		void operator=(Core const&);

		Renderer* _pRenderer;
		Scene* _pScene;
	};
}

