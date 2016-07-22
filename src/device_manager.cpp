#include "vulint/device_manager.h"
#include "vulint/vulkan_funcs.h"
#include <iostream>

DeviceManager::DeviceManager()
	: physical_devices_vector_()
{
}

DeviceManager::~DeviceManager()
{
//TODO: safely destroy logical devices
}

bool DeviceManager::GetPhysicalDevices(const VkInstance& instance, unsigned int max_devices, bool print_info)
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

	std::string device_type_names[] = { "OTHER", "INTEGRATE GPU", "DISCRETE GPU", "VIRTUAL GPU", "CPU" };

	// During loop add the device handle to the physical devices vector
	//	and get the properties to add those as well
	for (auto it = temp_devices_vector_.begin(); it != temp_devices_vector_.end(); ++it)
	{
		//push back handle
		physical_devices_vector_.emplace_back(*it);

		// add properties to the newly added PhysicalDevice
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(*it, &properties);
		physical_devices_vector_.back().SetProperties(properties);

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
	}

	return true;
}

bool DeviceManager::CreateLogicalDevice(const VkInstance& instance)
{
	return true;	
}
