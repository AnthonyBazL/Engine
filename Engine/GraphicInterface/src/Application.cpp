#include "Application.h"

namespace GraphicInterface
{
	Application::Application()
	{
		_pScene = new Scene();
		_pRenderer = new OpenGLRenderer(_pScene);
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