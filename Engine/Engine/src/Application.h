#pragma once
namespace Engine
{
	class __declspec(dllexport) Application
	{
	public:
		Application();
		virtual ~Application(); // Virtual because, inherited by the app using this engine

		void Run();
	};
}

