#include "vulint/device_manager.h"
#include "vulint/vulkan_funcs.h"
#include <iostream>
#include "vulkan/vulkan.h"

DeviceManager::DeviceManager()
	: physical_devices_map_()
{
}

DeviceManager::~DeviceManager()
{
//TODO: safely destroy logical devices
}

bool DeviceManager::UpdatePhysicalDevices(const VkInstance& instance, unsigned int max_devices, bool print_info, unsigned int max_queues, bool print_queue_properties)
{
	//get number of physical vulkan-enabled devices if 
	unsigned int num_devices;
	if (vkEnumeratePhysicalDevices(instance, &num_devices, nullptr) != VK_SUCCESS)
	{
		std::cerr << "Error getting number of physical devices" << std::endl;
		return false;
	}
	if (num_devices <= 0)
	{
		std::cerr << "No physical devices found!" << std::endl;
		return false;
	}

	if(num_devices > max_devices && max_devices > 0)
		num_devices = max_devices;

	//to hold the physical device handles
	std::vector<VkPhysicalDevice> temp_devices_vector_;
	temp_devices_vector_.resize(num_devices);
	if (vkEnumeratePhysicalDevices(instance, &num_devices, temp_devices_vector_.data()) != VK_SUCCESS)
	{
		std::cerr << "Error enumerating physical devices" << std::endl;
		return false;
	}

	std::string device_type_names[] = { "OTHER", "INTEGRATED GPU", "DISCRETE GPU", "VIRTUAL GPU", "CPU" };

	// During loop add the device handle to the physical devices vector
	//	and get the properties to add those as well
	for (auto it = temp_devices_vector_.begin(); it != temp_devices_vector_.end(); ++it)
	{
		// add properties to the PhysicalDevice object
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(*it, &properties);
		PhysicalDevice physical_device(*it);
		physical_device.SetProperties(properties);

		//add physical device handle to map
		physical_devices_map_.emplace(physical_device, std::vector<VkQueueFamilyProperties>());

		std::cout << VK_API_VERSION_1_0;
		if (print_info)
		{
			std::cout << "DEVICE: " << properties.deviceName << " {" << std::endl;
			std::cout << "Device ID: " << properties.deviceID << std::endl;
			std::cout << "Device Type: " << device_type_names[properties.deviceType].c_str() << std::endl;
			std::cout << "Encoded Device API Version: " << properties.apiVersion << std::endl;
			std::cout << "Current API Version: " << VK_API_VERSION_1_0 << std::endl;
			std::cout << "Vendor ID: " << properties.vendorID << std::endl;
			std::cout << "Driver Version: " << properties.driverVersion << std::endl;
			std::cout << "}" << std::endl << std::endl;
		}

		unsigned int num_queues;
		if (max_queues <= 0)
		{
			vkGetPhysicalDeviceQueueFamilyProperties(*it, &num_queues, nullptr);
			if (num_queues <= 0)
			{
				std::cerr << "Error getting number of queue families for physical device: " <<
					physical_device.device_properties().deviceName << std::endl;
			}
		}
		else
			num_queues = max_queues;

		std::vector<VkQueueFamilyProperties> queue_family_properties_vector;
		queue_family_properties_vector.resize(num_queues);
		vkGetPhysicalDeviceQueueFamilyProperties(*it, &num_queues, queue_family_properties_vector.data());

		if (print_queue_properties)
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
					<< queue_it->minImageTransferGranularity.height << ", " << queue_it->minImageTransferGranularity.depth << ")" << std::endl;
				std::cout << "}" << std::endl << std::endl;
			}
		}
	}

	return true;
}

bool DeviceManager::GetPhysicalDevices(VkQueueFlags required_flags)
{
	for(auto it = physical_devices_map_.begin(); it != physical_devices_map_.end(); ++it)
	{
		
	}
}


bool DeviceManager::CreateLogicalDevice(const VkInstance& instance)
{
	return true;	
}
