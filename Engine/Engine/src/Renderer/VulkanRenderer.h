#pragma once
#define GLFW_INCLUDE_VULKAN // It will include vulkan.h that embed all Vulkan definitions
#include "Renderer.h"
#include <optional>


namespace Engine
{
	struct QueueFamilyIndices 
	{
		// We use "optional" as 0 can be a graphicFamily index so checking if value is assigned at least once guarantee that an index has been explicitly set
		std::optional<uint32_t> graphicsFamily;

		bool IsComplete() {
			return graphicsFamily.has_value();
		}
	};

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
		void PickPhysicalDevice();
		bool IsDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		void CreateLogicalDevice();

		GLFWwindow* _pWnd = nullptr;
		VkInstance _vkInstance;
		VkDevice _logicalDevice;
		VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
		VkQueue _graphicsQueue;
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