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
		vkDestroyInstance(_vkInstance, nullptr);
		glfwDestroyWindow(_pWnd);
		glfwTerminate();
	}

	void VulkanRenderer::InitializeVulkan()
	{
		CreateVulkanInstance();
	}

	void VulkanRenderer::CreateVulkanInstance()
	{
		// Optional datas here but it may provide useful informations to the driver in order to optimize the app
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		// Not optional
		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		if (glfwVulkanSupported() == GLFW_FALSE)
		{
			std::cout << "Vulkan isn't supported" << std::endl;
		}

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;

		if (vkCreateInstance(&createInfo, nullptr, &_vkInstance) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create Vulkan instance!");
		}

		// Display available Vulkan extensions and check if every Vulkan extensions required by GLFW are available
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
		std::cout << "available extensions:\n";

		uint8_t glfwExtensionsSupportedCount = 0;
		for (const auto& extension : extensions) 
		{
			std::cout << '\t' << extension.extensionName << '\n';

			if (glfwExtensionsSupportedCount != glfwExtensionCount)
			{
				for (int i = 0; i < glfwExtensionCount; ++i)
				{
					if (strcmp(extension.extensionName, glfwExtensions[i]) == 0)
					{
						++glfwExtensionsSupportedCount;
					}
				}
			}
		}

		if (glfwExtensionsSupportedCount == glfwExtensionCount)
		{
			std::cout << "Every Vulkan extensions required by GLFW are supported." << std::endl;
		}
	}
}
