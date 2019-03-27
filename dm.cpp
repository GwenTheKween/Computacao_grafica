#include "dm.h"

//===================================================================
//Auxiliary funtions and structures

struct queueFamilyIndices{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete(){
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

queueFamilyIndices findQueueFamilies(VkPhysicalDevice dev, VkSurfaceKHR surface){
	queueFamilyIndices indices;
	VkBool32 presentSupport;
	uint32_t queueFamilyCount=0;

	vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, queueFamilies.data());

	for(int i=0; i<queueFamilyCount; i++){
		if(	queueFamilies[i].queueCount > 0 && 
			(queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)){
				indices.graphicsFamily = i;
		}

		presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(dev, i, surface, &presentSupport);
		if(queueFamilies[i].queueCount > 0 && presentSupport){
			indices.presentFamily = i;
		}
	}

	return indices;
}

bool isPhysicalDeviceSuitable(VkPhysicalDevice dev, VkSurfaceKHR surface){
	queueFamilyIndices ind = findQueueFamilies(dev, surface);
	//better suitability check TBA
	return ind.isComplete();
}

//===================================================================
//Private Methods implementations

void DisplayManager::initWindow(){
	//initiates glfw with correct parameters
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, "projeto 1", nullptr, nullptr);
}

void DisplayManager::initVulkan(){
	createInstance();

	//debug layers, TBA

	createSurface();

	pickPhysicalDevice();

//	createLogicalDevice();
}

void DisplayManager::createInstance(){
	//information required to start Vulkan instance
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "projeto 1";
	appInfo.applicationVersion = VK_MAKE_VERSION(0,1,0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
	appInfo.apiVersion = VK_API_VERSION_1_0;


	//struct that will carry the info
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	//extension setup
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;
	createInfo.enabledLayerCount = 0;

	if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		throw std::runtime_error("Failed to create Vulkan Instance");
}

void DisplayManager::createSurface(){
	if(glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
		throw std::runtime_error("failed to create GLFW surface");
}

void DisplayManager::pickPhysicalDevice(){
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if(deviceCount == 0){
		throw std::runtime_error("No GPUs with Vulkan access available, Have you installed Vulkan's Firmware?");
	}

	//gets a list of GPUs available, and chooses the best suited
	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	for(int i=0; i<deviceCount; i++){
		if(isPhysicalDeviceSuitable(devices[i],surface)){
			physDevice = devices[i];
			break;
		}
	}

	if(physDevice == VK_NULL_HANDLE)
		throw std::runtime_error("None of the Available GPUs support the desired operations");
}

void DisplayManager::createLogicalDevice(){
	float queuePriorities;
	//Queue creation information
	queueFamilyIndices ind = findQueueFamilies(physDevice,surface);
	VkDeviceQueueCreateInfo queueCreateInfo= {};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = ind.graphicsFamily.value();
	queueCreateInfo.queueCount = 1;
	queuePriorities = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriorities;

	//Desired features for the GPU
	VkPhysicalDeviceFeatures devFeat = {};

	//Information that will be used to create the logical device
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &devFeat;

	//Actual creation of the logical device
	if(vkCreateDevice(physDevice, &createInfo, nullptr, &device) != VK_SUCCESS){
		throw std::runtime_error("failed to create logical device");
	}
}


//===================================================================
//Public Methods implementations

DisplayManager::DisplayManager(int wid, int hei):
	width(wid),
	height(hei),
	device(VK_NULL_HANDLE)
	{

	initWindow();
	initVulkan();

	}

DisplayManager::~DisplayManager(){
	vkDestroyDevice(device, nullptr);
	vkDestroySurfaceKHR(instance, surface, nullptr);
	vkDestroyInstance(instance, nullptr);

	glfwDestroyWindow(window);
	glfwTerminate();
}
