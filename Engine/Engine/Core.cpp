#include "Core.h"

namespace Engine
{
	Core::Core()
	{
#if USE_OPENGL
		_pRenderer = new OpenGLRenderer(new Scene());
#elif USE_VULKAN
		_pRenderer = new VulkanRenderer(new Scene());
#else
		std::cout << "Engine only support OpenGL and Vulkan for now, please define USE_OPENGL or USE_VULKAN as preprocessor argument." << std::endl;
#endif
	}

	Core::~Core()
	{
		if(_pRenderer)
			delete _pRenderer;
	}

	void Core::Initialize()
	{
		if(_pRenderer)
			_pRenderer->StartRendering();
	}
}