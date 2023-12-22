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
		void CleanUp();
		void InitializeVulkan();
		void CreateVulkanInstance();

		GLFWwindow* _pWnd = nullptr;
		VkInstance _vkInstance;
		const uint32_t WIDTH = 800;
		const uint32_t HEIGHT = 600;
	};
}