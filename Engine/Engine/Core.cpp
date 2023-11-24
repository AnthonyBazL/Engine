#include "Core.h"

namespace Engine
{
	Core::Core()
	{
		_pRenderer = new OpenGLRenderer(new Scene());
	}

	Core::~Core()
	{
		delete _pRenderer;
	}

	void Core::Initialize()
	{
		_pRenderer->StartRendering();
	}
}