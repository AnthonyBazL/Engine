#include "Application.h"

namespace GraphicInterface
{
	Application::Application()
	{
		_pRenderer = new OpenGLRenderer();
	}

	Application::~Application()
	{
		delete _pRenderer;
	}

	void Application::Run()
	{
		_pRenderer->StartRendering();
		while(true)
		{ }
	}
}