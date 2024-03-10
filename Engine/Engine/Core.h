#pragma once

#if USE_OPENGL
#include "src/Renderer/OpenGLRenderer.h"
#elif USE_VULKAN
#include "src/Renderer/VulkanRenderer.h"
#else
#include "src/Renderer/OpenGLRenderer.h"
#endif

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
		void* _pRenderer = nullptr;
		Core(Core const&);
		void operator=(Core const&);
	};
}

