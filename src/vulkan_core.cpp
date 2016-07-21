#include "vulint/vulkan_core.h"
#include "winhelp/ErrorHandling.h"
#include <vulkan/vulkan.h>
#include "vulint/vulkan_funcs.h"
#include <iostream>
#include <Windows.h>

//functions are loaded dynamically
//VK_NO_PROTOTYPES ensures vulkan function declarations are not made in "vulkan.h"
//	this ensures functions not loaded from "vulkan-1.dll" are not declared.
//	If static linking with vulkan every declaration in "vulkan.h" would be defined,
//	but this is not true with dynamic linking

VulkanCore::VulkanCore()
	: device_manager_()
{
	vulkan_library_ = LoadLibrary("vulkan-1.dll");
	InitExportedFunctions();
	InitGlobalFunctions();
}


VulkanCore::~VulkanCore()
{
	if(vulkan_instance_)
	{
		vkDestroyInstance(vulkan_instance_, nullptr);
	}
	if (!FreeLibrary(vulkan_library_))
	{
		//TODO: Possibly display errors using message boxes instead
		std::cerr << WinHelper::GetLastSystemError() << std::endl;
	}
}

void VulkanCore::InitExportedFunctions() const
{
#define VULKAN_EXPORTED_FUNC(func){														\
	func = (PFN_##func)GetProcAddress(vulkan_library_, #func);							\
	if (!func)																			\
		std::cerr << "Unable to load vulkan exported function: " << #func << std::endl;	\
}

#include "vulint/vulkan_func_list.inl"
}

void VulkanCore::InitGlobalFunctions() const
{
#define VULKAN_GLOBAL_FUNC(func){														\
	func = (PFN_##func)vkGetInstanceProcAddr(nullptr, #func);							\
	if(!func)																			\
		std::cerr << "Unable to load vulkan global function: " << #func << std::endl;	\
}

#include "vulint/vulkan_func_list.inl"
}

void VulkanCore::InitInstanceFunctions() const
{
#define VULKAN_INSTANCE_FUNC(func){														\
	func = (PFN_##func)vkGetInstanceProcAddr(VULKAN_INSTANCE_VAR_NAME, #func);			\
	if(!func)																			\
		std::cerr << "Unable to load vulkan instance function: " << #func << std::endl;	\
}

#include "vulint/vulkan_func_list.inl"
}

bool VulkanCore::InitInstance(const std::string& app_name, std::array<int, 3> app_version)
{
	VkApplicationInfo application_info;
	application_info.sType = VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO;
	application_info.pNext = nullptr;
	application_info.pApplicationName = app_name.c_str();
	application_info.applicationVersion = VK_MAKE_VERSION(app_version[0], app_version[1], app_version[2]);
	application_info.pEngineName = "Vulkan Engine";
	application_info.engineVersion = VK_MAKE_VERSION(0, 1, 0);
	application_info.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instance_info;
	instance_info.sType = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_info.pNext = nullptr;
	instance_info.flags = 0;
	instance_info.pApplicationInfo = &application_info;
	instance_info.enabledExtensionCount = 0;
	instance_info.ppEnabledExtensionNames = nullptr;
	instance_info.enabledLayerCount = 0;
	instance_info.ppEnabledLayerNames = nullptr;

	if (vkCreateInstance(&instance_info, nullptr, &vulkan_instance_) != VK_SUCCESS)
	{
		std::cerr << "Error creating a vulkan instance!" << std::endl;
		return false;
	}

	//instance is created so instance functions can be loaded
	InitInstanceFunctions();

	return true;
}

bool VulkanCore::InitDevices(const int max_devices, bool print_device_info, const int max_queues, bool print_queue_properties)
{
	device_manager_.GetPhysicalDevices(vulkan_instance_, max_devices, print_device_info);

	/*for(auto it = physical_devices_vector_.begin(); it != physical_devices_vector_.end(); ++it)
	{
		unsigned int num_queues;
		if (max_queues <= 0)
		{
			vkGetPhysicalDeviceQueueFamilyProperties(*it, &num_queues, nullptr);
			if (num_queues <= 0)
			{
				std::cerr << "Error getting number of queue families for physical device: " <<
					physical_device_properties_vector_.at(it - physical_devices_vector_.begin()).deviceName << std::endl;
			}
		}
		else
			num_queues = max_queues;

		std::vector<VkQueueFamilyProperties> queue_family_properties_vector;
		queue_family_properties_vector.resize(num_queues);
		vkGetPhysicalDeviceQueueFamilyProperties(*it, &num_queues, queue_family_properties_vector.data());
		
		if(print_queue_properties)
		{
			for (auto queue_it = queue_family_properties_vector.begin(); queue_it != queue_family_properties_vector.end(); ++queue_it)
			{
				std::string types = "";
				if (queue_it->queueFlags & VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT)
					types += "Compute, ";
				if (queue_it->queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT)
					types += "Graphics, ";
				if (queue_it->queueFlags & VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT)
					types += "Transfer, ";
				if (queue_it->queueFlags & VkQueueFlagBits::VK_QUEUE_SPARSE_BINDING_BIT)
					types += "Sparse Binding, ";
				if (types != "")
					types.erase(types.length() - 2, std::string::npos);
				std::cout << "QUEUE FAMILY " << physical_device_properties_vector_.at(it - physical_devices_vector_.begin()).deviceName << " {" << std::endl;
				std::cout << "Queue Type: " << types << std::endl;
				std::cout << "Queue Count: " << queue_it->queueCount << std::endl;
				std::cout << "Timestamp Valid Bits: " << queue_it->timestampValidBits << std::endl;
				std::cout << "Minimum Granularity: " << "(w,h,d)   (" << queue_it->minImageTransferGranularity.width << ", "
					<< queue_it->minImageTransferGranularity.height << ", " << queue_it->minImageTransferGranularity.depth << ")"<< std::endl;
				std::cout << "}" << std::endl << std::endl;	
			}
		}
	}*/

	return true;
}


