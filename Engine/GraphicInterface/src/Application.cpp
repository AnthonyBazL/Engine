#include "Application.h"

namespace GraphicInterface
{
	Application::Application()
	{
		_pEngine->GetInstance().Initialize();
	}

	Application::~Application()
	{
		
	}

	void Application::Run()
	{		
		while(true)
		{ }
	}
}