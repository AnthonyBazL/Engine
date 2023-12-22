#include "VulkanRenderer.h"

namespace Engine
{
	VulkanRenderer::VulkanRenderer(Scene* pScene) : Renderer(pScene)
	{
	}

	VulkanRenderer::~VulkanRenderer()
	{
	}

	void VulkanRenderer::StartRendering()
	{		
		int windowCreated = CreateWindow();
		if (windowCreated != -1) Render();
	}

	void VulkanRenderer::StopRendering()
	{

	}

	int VulkanRenderer::CreateWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		_pWnd = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan window", nullptr, nullptr);
		InitializeVulkan();
		glm::mat4 matrix;
		glm::vec4 vec;
		auto test = matrix * vec;

		while (!glfwWindowShouldClose(_pWnd)) {
			glfwPollEvents();
		}

		CleanUp();

		return 0;
	}

	void VulkanRenderer::Render()
	{

	}
	
	void VulkanRenderer::CleanUp()
	{
		if (_enableValidationLayers) {
			DestroyDebugUtilsMessengerEXT(_vkInstance, _debugMessenger, nullptr);
		}

		vkDestroyInstance(_vkInstance, nullptr);
		glfwDestroyWindow(_pWnd);
		glfwTerminate();
	}

	void VulkanRenderer::InitializeVulkan()
	{
		CreateVulkanInstance();
		SetupDebugMessenger();
	}

	void VulkanRenderer::CreateVulkanInstance()
	{
		// Check Vulkan support
		if (glfwVulkanSupported() == GLFW_FALSE)
		{
			std::cout << "Vulkan isn't supported" << std::endl;
		}

		// Check if validation layers are available if we enable them
		if (_enableValidationLayers && !CheckValidationLayerSupport()) 
		{
			throw std::runtime_error("Validation layers requested, but not available!");
		}

		// Optional datas here but it may provide useful informations to the driver in order to optimize the app
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		// Not optional as it will gather informations like layers and extensions to use for a specific VK instance
		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		std::vector<const char*> requiredExtensions = GetRequiredExtensions();
		uint32_t requireExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
		createInfo.enabledExtensionCount = requireExtensionCount;
		createInfo.ppEnabledExtensionNames = requiredExtensions.data();

		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		if (_enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(_validationLayers.size());
			createInfo.ppEnabledLayerNames = _validationLayers.data();

			PopulateDebugMessengerCreateInfo(debugCreateInfo);
			createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
		}
		else
		{
			createInfo.enabledLayerCount = 0;
			createInfo.pNext = nullptr;
		}

		if (vkCreateInstance(&createInfo, nullptr, &_vkInstance) != VK_SUCCESS) 
		{
			throw std::runtime_error("Failed to create Vulkan instance!");
		}

		// Display available Vulkan extensions and check if every Vulkan extensions required by GLFW are available
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
		std::cout << "Available extensions:\n";

		uint8_t requiredExtensionsSupportedCount = 0;
		for (const auto& extension : extensions) 
		{
			std::cout << '\t' << extension.extensionName << '\n';

			if (requiredExtensionsSupportedCount != requireExtensionCount)
			{
				for (int i = 0; i < requireExtensionCount; ++i)
				{
					if (strcmp(extension.extensionName, requiredExtensions[i]) == 0)
					{
						++requiredExtensionsSupportedCount;
					}
				}
			}
		}

		if (requiredExtensionsSupportedCount == requireExtensionCount)
		{
			std::cout << "Every Vulkan extensions required by GLFW are supported." << std::endl;
		}
	}

	bool VulkanRenderer::CheckValidationLayerSupport() 
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : _validationLayers) 
		{
			bool layerFound = false;

			for (const VkLayerProperties& layerProperties : availableLayers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0) 
				{
					layerFound = true;
					break;
				}
			}

			if (!layerFound) {
				return false;
			}
		}

		return true;
	}

	std::vector<const char*> VulkanRenderer::GetRequiredExtensions() 
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (_enableValidationLayers) 
		{
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}

	void VulkanRenderer::SetupDebugMessenger() 
	{
		if (!_enableValidationLayers) return;

		// Setup debug messenger
		VkDebugUtilsMessengerCreateInfoEXT createInfo{};
		PopulateDebugMessengerCreateInfo(createInfo);

		if (CreateDebugUtilsMessengerEXT(_vkInstance, &createInfo, nullptr, &_debugMessenger) != VK_SUCCESS) 
		{
			throw std::runtime_error("Failed to set up Vulkan debug messenger!");
		}
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanRenderer::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) 
	{
		// TODO: Manage more informations here and display messages differently according their severity
		std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
	}

	VkResult VulkanRenderer::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
		const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) 
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr) 
		{
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}
		else 
		{
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void VulkanRenderer::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) 
	{
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, debugMessenger, pAllocator);
		}
	}

	void VulkanRenderer::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) 
	{
		createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		// Here are all message severity for which the specified callback will be triggered
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		// Here are all message types for which the specified callback will be triggered
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = DebugCallback;
	}
}
