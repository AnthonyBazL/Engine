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
		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();
		void SetupDebugMessenger();
		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

		GLFWwindow* _pWnd = nullptr;
		VkInstance _vkInstance;
		VkDebugUtilsMessengerEXT _debugMessenger;
		const uint32_t WIDTH = 800;
		const uint32_t HEIGHT = 600;
		const std::vector<const char*> _validationLayers = 
		{
			"VK_LAYER_KHRONOS_validation"
		};

#ifdef USE_VULKAN_VALIDATION_LAYERS
		const bool _enableValidationLayers = true;
#else
		const bool _enableValidationLayers = false;
#endif
	};
}