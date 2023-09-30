#pragma once
#include <stdio.h>
#include <stdlib.h>

#ifndef GL_H
#define GLFW_INCLUDE_NONE
#include <GLEW/GL/glew.h>
#include <GLFW/glfw3.h>
#endif // !GL_H


#include "Scene.h"

namespace GraphicInterface
{
	class Renderer
	{
		enum class RenderState
		{
			UNINITIALIZED = 0,
			STARTED = 1,
			STOPPED = 2
		};

	public:
		Renderer(Scene* pScene) { _pScene = pScene; };
		virtual void StartRendering() = 0;
		virtual void StopRendering() = 0;

	protected:
		Scene* _pScene;
		RenderState _renderState = RenderState::UNINITIALIZED; // TODO: To manage
		void* _pRenderFunc = nullptr; // TODO: Manage rendering asynchronously in a seperate thread
	};
}