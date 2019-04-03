#ifndef DISPLAY_MANAGER
#define DISPLAY_MANAGER

//#define DEBUG
#define MAX_VERTICES 4

//standard libraries
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <optional>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <cstring>

#include "vertex.h"

class DisplayManager{
private:
	//members used for GLFW library
	GLFWwindow* window;

	//members used for Vulkan library
	VkInstance instance;
	VkSurfaceKHR surface;
	VkPhysicalDevice physDevice;
	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkSwapchainKHR swapchain;
	std::vector<VkImage> swapchainImages;
	std::vector<VkImageView> swapchainImageViews;
	VkFormat swapchainImageFormat;
	VkExtent2D swapchainExtent;
	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	std::vector<VkFramebuffer> swapchainFrambuffer;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	//General Purpose Members
	uint32_t width, height;

	//private setup methods
	void initWindow();
	void initVulkan();
	void createInstance();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createGraphicsPipeline();
	void createFramebuffers();
	void createCommandPool();
	void createVertexBuffers();
	void createIndexBuffer();
	void createCommandBuffers();
	void createSemaphores();
	void createBuffer(VkDeviceSize, VkBufferUsageFlags, VkMemoryPropertyFlags, VkBuffer&, VkDeviceMemory&);

	//private drawing methods
	void drawFrame();
	void copyBuffer(VkBuffer, VkBuffer, VkDeviceSize);

public:
	DisplayManager();
	~DisplayManager();

	void init(int = 800, int = 600);
	void run();

	void fillVertexBuffer(std::vector<vertex>);
};

#endif
