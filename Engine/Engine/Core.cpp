#include "Core.h"

namespace Engine
{
	Core::Core()
	{
#if USE_OPENGL
		_pRenderer = new OpenGLRenderer(new Scene());
#else
		std::cout << "Engine only support OpenGL for now, please define USE_OPENGL as preprocessor argument." << std::endl;
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