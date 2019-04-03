#include "dm.h"

/*
	essa biblioteca foi escrita por Bruno P. Larsen, usando o tutorial
	disponivel em vulkan-tutorial.com/Drawing_a_triangle
*/

//===================================================================
//Auxiliary funtions and structures

//used to debug dynamically drawing vertices
const std::vector<vertex> vertices = {
	{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},
	{{-0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}}
};

const std::vector<uint16_t> indices = {
	0,1,2,2,3,0
};

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

//secao de debug, sera deixada de ora da versao final para aumentar a performance
#ifdef DEBUG
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};
#endif

//check that the swap chain (image buffer holder) is present in the card
struct swapChainSupportDetails{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentMode;
};

queueFamilyIndices findQueueFamilies(VkPhysicalDevice dev, VkSurfaceKHR surface){
	queueFamilyIndices indices;
	VkBool32 presentSupport;
	uint32_t queueFamilyCount = 0;

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
		details.presentMode.resize(presentModeCount);
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
	return ind.isComplete() && checkExtensionSupport(dev, surface) && checkSwapChainSupport(dev, surface);
}

VkSurfaceFormatKHR chooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR> availableFormats){
	//if the surface doesn't have a preferred format, we choose RGBA with SRGB colorspace
	if(availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED){
		return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
	}

	//if it has, we frst check that that format is available
	for(int i=0; i<availableFormats.size(); i++){
		if(availableFormats[i].format == VK_FORMAT_B8G8R8A8_UNORM && availableFormats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormats[i];
		}
	}

	//if not, we'll just take the first available
	return availableFormats[0];
}

VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& cap, uint32_t width, uint32_t height){
	if(cap.currentExtent.width != std::numeric_limits<uint32_t>::max()){
		return cap.currentExtent;
	}else{
		VkExtent2D actualExtent = {width, height};
		if(cap.maxImageExtent.width > actualExtent.width){
			actualExtent.width = (cap.maxImageExtent.width > cap.minImageExtent.width) ? cap.maxImageExtent.width : cap.minImageExtent.width;
		}else{
			actualExtent.width = (cap.maxImageExtent.width > actualExtent.width) ? cap.maxImageExtent.width : actualExtent.width;
		}
		if(cap.maxImageExtent.height > actualExtent.height){
			actualExtent.height = (cap.maxImageExtent.height > cap.minImageExtent.height) ? cap.maxImageExtent.height : cap.minImageExtent.height;
		}else{
			actualExtent.height = (cap.maxImageExtent.height > actualExtent.height) ? cap.maxImageExtent.height : actualExtent.height;
		}
		return actualExtent;
	}
}

static std::vector<char> readFile(const std::string& filename){
	//File starts at the end
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if(!file.is_open()){
		throw std::runtime_error("failed to open shader file");
	}

	//we use the position at the end of the file to determine it's size
	size_t fileSize = (size_t)file.tellg();
	//allocate a buffer with the correct size
	std::vector<char> buffer(fileSize);
	//go back to the beginning and read all the file
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();
	return buffer;
}

VkShaderModule createShaderModule(const std::vector<char>& code, VkDevice device){
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkShaderModule shaderModule;
	if(vkCreateShaderModule(device,&createInfo, nullptr, &shaderModule) != VK_SUCCESS){
		throw std::runtime_error("Failed to create shader module");
	}

	return shaderModule;
}

uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physDevice){
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(physDevice, &memProperties);

	for(uint32_t i=0; i< memProperties.memoryTypeCount; i++){
		if((typeFilter & (1<<i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties){
			return i;
		}
	}

	throw std::runtime_error("failed to find suitable memory type!");
}

std::vector<const char*> getRequiredExtensions(){
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef DEBUG
	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
	return extensions;
}

//===================================================================
//Private setup Methods implementations

void DisplayManager::initWindow(){
	//initiates glfw with correct parameters
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, "projeto 1", nullptr, nullptr);
}

void DisplayManager::initVulkan(){
	createInstance();

	createSurface();

	pickPhysicalDevice();

	createLogicalDevice();

	createSwapChain();

	createImageViews();

	createRenderPass();

	createGraphicsPipeline();

	createFramebuffers();

	createCommandPool();

	createVertexBuffers();

	createIndexBuffer();

	createCommandBuffers();

	createSemaphores();
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
#ifdef DEBUG
		createInfo.ppEnabledLayerNames = validationLayers.data();
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
#endif

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
			this->physDevice = devices[i];
			break;
		}
	}

	if(physDevice == VK_NULL_HANDLE)
		throw std::runtime_error("None of the Available GPUs support the desired operations");
}

void DisplayManager::createLogicalDevice(){
	float queuePriorities = 1.0f;
	//Informatio to create all necessary queues
	queueFamilyIndices ind = findQueueFamilies(physDevice,surface);
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

	//armazena apenas os indices unicos de filas, caso a fila grafica e de apresentacao sejam a mesma
	std::set<uint32_t> uniqueQueues = {ind.graphicsFamily.value(), ind.presentFamily.value()};

	//for(std::set<uint32_t>::iterator it=uniqueQueues.begin(); it != uniqueQueues.end(); it++){
	for(uint32_t queueFam : uniqueQueues){
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFam;
		queueCreateInfo.queueCount = 1;
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

void DisplayManager::createSwapChain(){
	swapChainSupportDetails details = querySwapChainSupport(physDevice, surface);
	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(details.formats);
	VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
	VkExtent2D extent = chooseSwapExtent(details.capabilities,width,height);

	uint32_t imageCount = details.capabilities.minImageCount + 1;
	if(details.capabilities.maxImageCount > 0){
		imageCount = (imageCount > details.capabilities.maxImageCount) ? imageCount : details.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface;
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	createInfo.preTransform = details.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	queueFamilyIndices ind = findQueueFamilies(physDevice, surface);
	uint32_t indices[] = {ind.graphicsFamily.value(), ind.presentFamily.value()};
	if(indices[0] == indices[1]){
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; 
	}else{
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = indices;
	}

	if(vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapchain) != VK_SUCCESS){
		throw std::runtime_error("unable to create swapchain");
	}

	vkGetSwapchainImagesKHR(device,swapchain, &imageCount, nullptr);
	swapchainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(device,swapchain, &imageCount, swapchainImages.data());
	swapchainImageFormat = surfaceFormat.format;
	swapchainExtent = extent;
}

void DisplayManager::createImageViews(){
	swapchainImageViews.resize(swapchainImages.size());
	for(size_t i=0; i<swapchainImageViews.size(); i++){
		VkImageViewCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = swapchainImages[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = swapchainImageFormat;

		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		if(vkCreateImageView(device, &createInfo, nullptr, &swapchainImageViews[i]) != VK_SUCCESS){
			throw std::runtime_error("Failed to create image view");
		}
	}
}

void DisplayManager::createRenderPass(){
	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = swapchainImageFormat;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	//ignore the stencil buffer
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;

	if(vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS){
		throw std::runtime_error("failed to create render pass");
	}
}

void DisplayManager::createGraphicsPipeline(){
	//first we need to load the shader code (defined in other files) and wrap them around shader modules
	auto vertexShaderCode = readFile("shaders/vert.spv");
	auto fragShaderCode = readFile("shaders/frag.spv");

	VkShaderModule vertShaderModule = createShaderModule(vertexShaderCode, device);
	VkShaderModule fragShaderModule = createShaderModule(fragShaderCode, device);

	//next we need to create shaders, to link them to the GPU
	VkPipelineShaderStageCreateInfo vertexShaderInfo= {};
	vertexShaderInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertexShaderInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertexShaderInfo.module = vertShaderModule;
	vertexShaderInfo.pName = "main"; //name of the entrypoint function of the module

	VkPipelineShaderStageCreateInfo fragShaderInfo= {};
	fragShaderInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderInfo.module = fragShaderModule;
	fragShaderInfo.pName = "main";

	//they are now ready to be linked to the GPU
	VkPipelineShaderStageCreateInfo shaderStages[] = {vertexShaderInfo,fragShaderInfo};

	//information about how vertices will be inputted
	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
	auto bindingDescription = vertex::getBindingDescription();
	auto attributeDescription = vertex::getAttributeDescription();
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescription.size());
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescription.data();

	//Input Assembly is how to assemble the points we give the object. 
	//For example, make a triangle out of every 3 points, or draw them separately.
	//for the class project, we'll be using no connection
	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	//topology used specifically for the tutorial
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
	//actual topology that will be used for the project
//	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	//creates a default viewport
	VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float) swapchainExtent.width;
	viewport.height = (float) swapchainExtent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	//doesn't scissor anything of the viewport out
	VkRect2D scissor = {};
	scissor.offset = {0,0};
	scissor.extent = swapchainExtent;

	VkPipelineViewportStateCreateInfo viewportState = {};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	//sets the rasterization
	VkPipelineRasterizationStateCreateInfo rasterizer = {};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;

	//disable multisampling
	VkPipelineMultisampleStateCreateInfo multisampling = {};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	//disable color blending
	VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;
	VkPipelineColorBlendStateCreateInfo colorBlend = {};
	colorBlend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlend.logicOpEnable = VK_FALSE;
	colorBlend.attachmentCount = 1;
	colorBlend.pAttachments = &colorBlendAttachment;

	//Dynamic state:
	//If we want to be able to change the viewport, line width, blend or other parts of the graphics pipeline, we can set this structure:
	/*
	   VkDynamicState dynamicState[]={
	   		VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_LINE_WIDTH
			//Or other things that we want dinamically changing
	   }
	   VkPipelineDynamicStateCreateInfo dynamicState = {};
	   dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	   dynamicState.dynamicStateCount = 2;//actual count of dynamic states
	   dynamicState.pDynamicStates = &dynamicState;
	*/
	//doing so results in the creation of the pipeline ignoring the information passed when created (for viewport, for example)
	//and instead requesting the info at drawing time
	//if nothing is dynamic, we can set the pointer to null when creating the graphics pipeline

	//pipelineLayout can store information about variables that can be changed, such as transformation matrices or texture samplers
	//even if we dont use any, we still need an empty struct
	VkPipelineLayoutCreateInfo pipelineLayoutCreate = {};
	pipelineLayoutCreate.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutCreate.setLayoutCount = 0;

	if(vkCreatePipelineLayout(device, &pipelineLayoutCreate, nullptr, &pipelineLayout) != VK_SUCCESS){
		throw std::runtime_error("Failed to create the pipeline layout!");
	}

	//at last, we have all we need to create the graphics pipeline
	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pColorBlendState = &colorBlend;
	pipelineInfo.layout = pipelineLayout;
	pipelineInfo.renderPass = renderPass;
	pipelineInfo.subpass = 0;

	if(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS){
		throw std::runtime_error("Failed to create Graphics pipeline");
	}

	//finally we can destroy the shader modules, as they have already been lined to the GPU
	vkDestroyShaderModule(device, vertShaderModule, nullptr);
	vkDestroyShaderModule(device, fragShaderModule, nullptr);
}

void DisplayManager::createFramebuffers(){
	swapchainFrambuffer.resize(swapchainImageViews.size());

	for(int i = 0; i < swapchainImageViews.size(); i++){
		VkImageView attachments[] = {
			swapchainImageViews[i]
		};

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = swapchainExtent.width;
		framebufferInfo.height = swapchainExtent.height;
		framebufferInfo.layers = 1;

		if(vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapchainFrambuffer[i]) != VK_SUCCESS){
			throw std::runtime_error("failed to create framebuffers");
		}
	}
}

void DisplayManager::createCommandPool(){
	queueFamilyIndices queueFamilies = findQueueFamilies(physDevice, surface);

	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilies.graphicsFamily.value();

	if(vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS){
		throw std::runtime_error("failed to create command pool");
	}
}

void DisplayManager::createCommandBuffers(){
	commandBuffers.resize(swapchainFrambuffer.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

	if(vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS){
		throw std::runtime_error("failed to allocate command buffers");
	}

	for(size_t i = 0; i < commandBuffers.size(); i++){
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		
		if(vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS){
			throw std::runtime_error("failed to begin recording command buffer");
		}

		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = renderPass;
		renderPassInfo.framebuffer = swapchainFrambuffer[i];
		renderPassInfo.renderArea.offset = {0,0};
		renderPassInfo.renderArea.extent = swapchainExtent;

		VkClearValue clearColor = {0.0f,0.0f,0.0f,1.0f};
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(commandBuffers[i],VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

		VkBuffer vertexBuffers[] = {vertexBuffer};
		VkDeviceSize offsets[] = {0};
		vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);

		vkCmdBindIndexBuffer(commandBuffers[i], indexBuffer, 0, VK_INDEX_TYPE_UINT16);

		vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(indices.size()), 1, 0, 0,0);

		vkCmdEndRenderPass(commandBuffers[i]);

		if(vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS){
			throw std::runtime_error("failed to record command buffer");
		}
	}
}

void DisplayManager::createSemaphores(){
	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	if(	(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS) ||
		(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS)) {
		throw std::runtime_error("failed to create semaphores");
	}
}

void DisplayManager::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory){
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if(vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS){
		throw std::runtime_error("failed to create buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties, physDevice);

	if(vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS){
		throw std::runtime_error("failed to allocate buffer memory!");
	}

	vkBindBufferMemory(device, buffer,bufferMemory,0);
}


//===================================================================
//Private Drawing methods

void DisplayManager::drawFrame(){

	//the first step in drawing an image is acquiring it from the swapchain
	uint32_t imageIndex;
	vkAcquireNextImageKHR(
			device, //qual dispositivo logico esta sendo usado para renderizar a imagem
			swapchain, //Qual swapchain contem a imagem desejada
			std::numeric_limits<uint32_t>::max(), //tempo, em segundos, ate timeout
			imageAvailableSemaphore, //semaforo usado para sincronizar o programa
			VK_NULL_HANDLE, //cerca usada para sincronizar
			&imageIndex //onde sera retornada a imagem
		);

	//preparacao para sumbeter comandos
	VkSubmitInfo submitInfo = {};
	VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
	VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT};

	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	//aqui eh indicado em qual imagem estamos trabalhando, ja que o cada commandBuffer eh unico para uma imagem
	submitInfo.pCommandBuffers = &commandBuffers[imageIndex];
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	//Processo de submeter o comando para o buffer, trabalhando na imagem adquirida
	if(vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS){
		throw std::runtime_error("unable to submit command");
	}

	//A ultima parte eh resubmeter a imagem para a swapchain
	VkPresentInfoKHR presentInfo = {};
	VkSwapchainKHR swapchains[] = {swapchain};

	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapchains;
	presentInfo.pImageIndices = &imageIndex;

	//submissao do pedido para apresentar a nova imagem
	vkQueuePresentKHR(presentQueue, &presentInfo);
	//espera terminar de renderizar o frame
	vkQueueWaitIdle(presentQueue);
}

void DisplayManager::createVertexBuffers(){

	VkDeviceSize bufferSize = sizeof(vertices[0])*vertices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, vertices.data(), (size_t) bufferSize);
	vkUnmapMemory(device, stagingBufferMemory);

	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

	copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

	vkDestroyBuffer(device, stagingBuffer, nullptr);
	vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void DisplayManager::createIndexBuffer(){
	VkDeviceSize bufferSize = sizeof(indices[0])*indices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, indices.data(), (size_t) bufferSize);
	vkUnmapMemory(device, stagingBufferMemory);

	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

	copyBuffer(stagingBuffer, indexBuffer, bufferSize);

	vkDestroyBuffer(device, stagingBuffer, nullptr);
	vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void DisplayManager::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size){
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = commandPool;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	VkBufferCopy copyRegion = {};
	copyRegion.size = size;

	vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(graphicsQueue);

	vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}

//===================================================================
//Public Methods implementations

DisplayManager::DisplayManager():
	physDevice(VK_NULL_HANDLE)
	{}

DisplayManager::~DisplayManager(){
	vkDestroyBuffer(device, indexBuffer, nullptr);
	vkFreeMemory(device, indexBufferMemory, nullptr);

	vkDestroyBuffer(device, vertexBuffer, nullptr);
	vkFreeMemory(device, vertexBufferMemory, nullptr);

	vkDestroySemaphore(device, imageAvailableSemaphore, nullptr);
	vkDestroySemaphore(device, renderFinishedSemaphore, nullptr);
	vkDestroyCommandPool(device, commandPool, nullptr);
	for(size_t i = 0; i< swapchainFrambuffer.size(); i++){
		vkDestroyFramebuffer(device, swapchainFrambuffer[i], nullptr);
	}
	vkDestroyPipeline(device, graphicsPipeline, nullptr);
	vkDestroyPipelineLayout(device,pipelineLayout,nullptr);
	vkDestroyRenderPass(device,renderPass,nullptr);
	for(size_t i = 0; i<swapchainImageViews.size(); i++){
		vkDestroyImageView(device,swapchainImageViews[i], nullptr);
	}
	vkDestroySwapchainKHR(device,swapchain, nullptr);
	vkDestroyDevice(device, nullptr);
	vkDestroySurfaceKHR(instance, surface, nullptr);
	vkDestroyInstance(instance, nullptr);

	glfwDestroyWindow(window);
	glfwTerminate();
}

void DisplayManager::init(int wid,int hei){
	width = wid;
	height = hei;
	initWindow();
	initVulkan();
}

void DisplayManager::run(){
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		drawFrame();
	}

	//espera ate todas as operacoes assincronas terminarem
	vkDeviceWaitIdle(device);
}

void DisplayManager::fillVertexBuffer(std::vector<vertex> vertices){
	/*
	if(vertices.size() <= 4){
		void* data;
		vkMapMemory(device, vertexBufferMemory, 0, bufferInfo.size, 0, &data);
		memcpy(data, vertices.data(), (size_t) bufferInfo.size);
		vkUnmapMemory(device, vertexBufferMemory);
	}else{
		throw std::runtime_error("Too many vertices at once");
	}
	*/
}
