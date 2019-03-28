#include "dm.h"

/*
	essa biblioteca foi escrita por Bruno P. Larsen, usando o tutorial
	disponivel em vulkan-tutorial.com/Drawing_a_triangle
*/

//===================================================================
//Auxiliary funtions and structures

//used to test if there are suitable GPUs present
struct queueFamilyIndices{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete(){
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

//used to confirm that GPUs have the desired extensions
const std::vector<const char*> deviceExtensions{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

//check that the swap chain (image buffer holder) is present in the card
struct swapChainSupportDetails{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentMode;
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

bool checkExtensionSupport(VkPhysicalDevice dev, VkSurfaceKHR surface){
	//gets all available extensions
	uint32_t extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(dev, nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(dev, nullptr, &extensionCount, availableExtensions.data());

	//check if the needed extensions are present
	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
	for(int i = 0; i<extensionCount; i++){
		requiredExtensions.erase(availableExtensions[i].extensionName);
	}
	//so tem todas as extensoes se o set estiver vazio
	return requiredExtensions.empty();
}

//checks the details of the available swap chain
swapChainSupportDetails querySwapChainSupport(VkPhysicalDevice dev, VkSurfaceKHR surface){
	swapChainSupportDetails details;

	//first get the details of the surface
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev, surface, &details.capabilities);

	//next, get the available formats
	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surface, &formatCount, nullptr);
	if(formatCount > 0){
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surface, &formatCount, details.formats.data());
	}

	//finally, get the available presentation modes
	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surface, &presentModeCount, nullptr);
	if(presentModeCount > 0){
		vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surface, &presentModeCount, details.presentMode.data());
	}

	return details;
}

bool checkSwapChainSupport(VkPhysicalDevice dev, VkSurfaceKHR surface){
	swapChainSupportDetails details = querySwapChainSupport(dev,surface);
	return !details.formats.empty() && !details.presentMode.empty();
}

bool isPhysicalDeviceSuitable(VkPhysicalDevice dev, VkSurfaceKHR surface){
	queueFamilyIndices ind = findQueueFamilies(dev, surface);
	//better suitability check TBA
	return ind.isComplete() && checkExtensionSupport(dev, surface) && checkSwapChainSupport(dev, surface);
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
	//Informatio to create all necessary queues
	queueFamilyIndices ind = findQueueFamilies(physDevice,surface);
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueues = {ind.graphicsFamily.value(), ind.presentFamily.value()};

	for(std::set<uint32_t>::iterator it=uniqueQueues.begin(); it != uniqueQueues.end(); it++){
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = *it;
		queueCreateInfo.queueCount = 1;
		queuePriorities = 1.0f;
		queueCreateInfo.pQueuePriorities = &queuePriorities;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	//Desired features for the GPU
	VkPhysicalDeviceFeatures devFeat = {};

	//Information that will be used to create the logical device
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	//queue information
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	//feature information
	createInfo.pEnabledFeatures = &devFeat;

	//extension information
	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	//Actual creation of the logical device
	if(vkCreateDevice(physDevice, &createInfo, nullptr, &device) != VK_SUCCESS){
		throw std::runtime_error("failed to create logical device");
	}

	//get the handlers for the graphics and presentations queues
	vkGetDeviceQueue(device,ind.graphicsFamily.value(), 0, &graphicsQueue);
	vkGetDeviceQueue(device,ind.presentFamily.value(), 0, &presentQueue);
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
