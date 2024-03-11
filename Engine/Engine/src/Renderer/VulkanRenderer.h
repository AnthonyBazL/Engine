#pragma once
#if USE_VULKAN
//#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN // It will include vulkan.h that embed all Vulkan definitions
#define GLM_FORCE_RADIANS
// Following define will force GLM to use a version of vec2 and mat4 that has the alignment requirements already specified
// Check this explication about alignment requirement: https://docs.vulkan.org/tutorial/latest/05_Uniform_buffers/01_Descriptor_pool_and_sets.html#_alignment_requirements
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <chrono>
#include "Renderer.h"
//#include "../Loader/TextureLoader.h" 
//#define GLFW_EXPOSE_NATIVE_WIN32
//#include <GLFW/glfw3native.h>
#include <optional>
#include <set>
#include <limits> // Necessary for std::numeric_limits
#include <algorithm> // Necessary for std::clamp

namespace Engine
{
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 color;
		glm::vec2 texCoord;

		static VkVertexInputBindingDescription GetBindingDescription() 
		{
			VkVertexInputBindingDescription bindingDescription{};
			bindingDescription.binding = 0; // The binding parameter specifies the index of the binding in the array of bindings.
			bindingDescription.stride = sizeof(Vertex); // The stride parameter specifies the number of bytes from one entry to the next
			/*
			The inputRate parameter can have one of the following values:
				VK_VERTEX_INPUT_RATE_VERTEX: Move to the next data entry after each vertex
				VK_VERTEX_INPUT_RATE_INSTANCE: Move to the next data entry after each instance
			*/
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 3> GetAttributeDescriptions() 
		{
			std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

			// Position vertex attribute
			attributeDescriptions[0].binding = 0; // The binding parameter tells Vulkan from which binding the per-vertex data comes
			attributeDescriptions[0].location = 0; // The location parameter references the location directive of the input in the vertex shader
			/*
			The input in the vertex shader with location 0 is the position, which has two 32-bit float components
				float: VK_FORMAT_R32_SFLOAT
				vec2: VK_FORMAT_R32G32_SFLOAT
				vec3: VK_FORMAT_R32G32B32_SFLOAT
				vec4: VK_FORMAT_R32G32B32A32_SFLOAT
			*/
			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos); // The offset parameter specifies the number of bytes since the start of the per-vertex data to read from

			// Color vertex attribute
			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);

			attributeDescriptions[2].binding = 0;
			attributeDescriptions[2].location = 2;
			attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

			return attributeDescriptions;
		}
	};

	struct QueueFamilyIndices 
	{
		// We use "optional" as 0 can be a graphicFamily index so checking if value is assigned at least once guarantee that an index has been explicitly set
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool IsComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails 
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	struct UniformBufferObject 
	{
		// alignas are important in order to always respect alignment requirement by Vulkan
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};

	class VulkanRenderer : public Renderer
	{
	public:
		VulkanRenderer(Scene* pScene);
		~VulkanRenderer();
		void StartRendering();
		void StopRendering();

	private:
		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);
		static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);
		int CreateWindow();
		void Render();		
		void CleanUp();
		void InitializeVulkan();
		void CreateVulkanInstance();
		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();
		void SetupDebugMessenger();
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void PickPhysicalDevice();
		bool IsDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		void CreateLogicalDevice();
		void CreateSurface();
		bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		void CreateSwapChain();
		void CreateImageViews();
		void CreateGraphicsPipeline();
		// TODO: Change or remove use of this function as specific to shader loading and there is a ShaderLoader class for this
		static std::vector<char> ReadFile(const std::string& filename) {
			std::ifstream file(filename, std::ios::ate | std::ios::binary);

			if (!file.is_open()) {
				throw std::runtime_error("failed to open file!");
			}
			size_t fileSize = (size_t)file.tellg();
			std::vector<char> buffer(fileSize);
			file.seekg(0);
			file.read(buffer.data(), fileSize);
			file.close();

			return buffer;
		}
		VkShaderModule CreateShaderModule(const std::vector<char>& code);
		void CreateRenderPass();
		void CreateFramebuffers();
		void CreateCommandPool();
		void CreateCommandBuffers();
		void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
		void CreateSyncObjects();
		void RecreateSwapChain();
		void CleanupSwapChain();
		void CreateVertexBuffer();
		uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		void CreateIndexBuffer();
		void CreateUniformBuffers();
		void CreateDescriptorSetLayout();
		void UpdateUniformBuffer(uint32_t currentImage);
		void CreateDescriptorPool();
		void CreateDescriptorSets();
		void CreateTextureImage();
		void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		VkCommandBuffer BeginSingleTimeCommands();
		void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
		void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
		void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
		void CreateTextureImageView();
		VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
		void CreateTextureSampler();
		void CreateDepthResources();
		VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		VkFormat FindDepthFormat();
		bool HasStencilComponent(VkFormat format);

		GLFWwindow* _pWnd = nullptr;
		VkInstance _vkInstance;
		VkDevice _logicalDevice;
		VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
		VkDebugUtilsMessengerEXT _debugMessenger;
		VkSurfaceKHR _surface;
		VkSwapchainKHR _swapChain;
		VkBuffer _vertexBuffer;
		VkDeviceMemory _vertexBufferMemory;
		VkBuffer _indexBuffer;
		VkDeviceMemory _indexBufferMemory;
		std::vector<VkBuffer> _uniformBuffers;
		std::vector<VkDeviceMemory> _uniformBuffersMemory;
		std::vector<void*> _uniformBuffersMapped;
		std::vector<VkImage> _swapChainImages;
		std::vector<VkImageView> _swapChainImageViews;
		std::vector<VkFramebuffer> _swapChainFramebuffers;
		VkFormat _swapChainImageFormat; // Frame format choosen (SRGB8, YUV, etc)
		VkExtent2D _swapChainExtent; // Frame resolution choosen (for example 1280x720)
		VkQueue _graphicsQueue; // Correspond to frames we'll be drawing on
		VkQueue _presentQueue; // Correspond to frames displayed on screen
		VkRenderPass _renderPass;
		VkDescriptorSetLayout _descriptorSetLayout;
		VkPipelineLayout _pipelineLayout;
		VkPipeline _graphicsPipeline;
		VkCommandPool _commandPool;
		VkDescriptorPool _descriptorPool;
		std::vector<VkDescriptorSet> _descriptorSets;
		std::vector<VkCommandBuffer> _commandBuffers;
		std::vector<VkSemaphore> _imageAvailableSemaphores; // This semaphore is here to check that a new image has been acquired from the swapchain on GPU side
		std::vector<VkSemaphore> _renderFinishedSemaphores; // This semaphore is here to check that render has finished for current frame on GPU side
		std::vector<VkFence> _inFlightFences; // This fence is here to check that we wait for latest frame to be finished/rendered before rendering another one on CPU side
		uint32_t _currentFrame = 0;
		const uint32_t WIDTH = 800;
		const uint32_t HEIGHT = 600;
		const int MAX_FRAMES_IN_FLIGHT = 2; // Correspond to number of frames that can be processed concurently, avoid to wait for current framer to be rendered before processing the next one
		bool _framebufferResized = false;
		VkImage _textureImage;
		VkDeviceMemory _textureImageMemory;
		VkImageView _textureImageView;
		VkSampler _textureSampler;
		VkImage _depthImage;
		VkDeviceMemory _depthImageMemory;
		VkImageView _depthImageView;

		const std::vector<Vertex> _vertices = {
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
			{{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

			{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
			{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
		};

		const std::vector<uint32_t> _indices = { // Can be uint16_t here but I plan to load heavy models with high number of vertices for testing
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};
		const std::vector<const char*> _validationLayers = 
		{
			"VK_LAYER_KHRONOS_validation"
		};
		const std::vector<const char*> _deviceExtensions = 
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

#ifdef USE_VULKAN_VALIDATION_LAYERS
		const bool _enableValidationLayers = true;
#else
		const bool _enableValidationLayers = false;
#endif
	};
}
#endif