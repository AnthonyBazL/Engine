#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GLEW/GL/glew.h>

namespace GraphicInterface
{
	class Renderer
	{
		enum RenderState
		{
			UNINITIALIZED = 0,
			STARTED = 1,
			STOPPED = 2
		};

	public:
		virtual void StartRendering() = 0;
		virtual void StopRendering() = 0;

	protected:
		RenderState _renderState;
		void* _pRenderFunc;
	};
}