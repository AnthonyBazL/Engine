#include "Application.h"

namespace GraphicInterface
{
	Application::Application()
	{
		_pRenderer = new OpenGLRenderer();
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		_pRenderer->StartRendering();
		while(true)
		{ }
	}
}