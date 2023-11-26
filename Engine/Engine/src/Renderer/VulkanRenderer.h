#pragma once
#define GLFW_INCLUDE_VULKAN // It will include vulkan.h that embed all Vulkan definitions
#include "Renderer.h"

namespace Engine
{
	class VulkanRenderer : public Renderer
	{
	public:
		VulkanRenderer(Scene* pScene);
		~VulkanRenderer();
		void StartRendering();
		void StopRendering();

	private:
		int CreateWindow();
		void Render();
	};
}