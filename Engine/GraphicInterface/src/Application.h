#pragma once

#include "../../Engine/Core.h"



namespace GraphicInterface
{
	class Application
	{
	public:
		Application();
		~Application();
		void Run();

	private:
		Engine::Core* _pEngine;
	};
}

