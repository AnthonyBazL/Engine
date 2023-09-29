#pragma once
#include "Renderer.h"

namespace GraphicInterface
{
	class OpenGLRenderer : public Renderer
	{
		void StartRendering() override;
		void StopRendering() override;
	};
}

