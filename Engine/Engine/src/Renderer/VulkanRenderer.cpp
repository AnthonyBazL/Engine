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
		GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		std::cout << extensionCount << " extensions supported\n";

		glm::mat4 matrix;
		glm::vec4 vec;
		auto test = matrix * vec;

		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}

		glfwDestroyWindow(window);

		glfwTerminate();

		return 0;
	}

	void VulkanRenderer::Render()
	{

	}
}
