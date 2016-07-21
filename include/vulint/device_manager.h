#ifndef VULKAN_INTRO_DEVICEMANAGER_H
#define VULKAN_INTRO_DEVICEMANAGER_H

#include "vulint/physical_device.h"
#include <vector>

class DeviceManager
{
public:
	//TODO: Add support for transfer and sparse binding
	enum class LOGICAL_DEVICE_TYPES
	{ GRAPHICS, COMPUTE	};
	/**
	* Device Manager constructor
	*/
	DeviceManager();

	/**
	* DeviceManager destructor
	* Handles destroying logical devices safely
	*/
	~DeviceManager();

	DeviceManager(const DeviceManager&) = delete;
	DeviceManager& operator=(const DeviceManager&) = delete;

	/**
	* Gathers physical devices using VkEnumeratePhysicalDevices
	* Stores the information in a PhysicalDevice in physical_devices_vector_
	* @param instance vulkan instance in order to call instance functions
	* @param max_devices sets the maximum number of physical devices to look for
	* @param print_info if true, the device info for each found physical device will be printed to cout
	* Returns whether the query is succesful, errors printed to cerr
	*/
	bool GetPhysicalDevices(const VkInstance& instance, unsigned int max_devices, bool print_info);

	/**
	* Attempts to create a vulkan logical device with the given parameters
	* Returns true if a logical device can be created with the parameters
	*/
	bool CreateLogicalDevice(const VkInstance& instance);

private:
	/**
	* Holds physical devices found through GetPhysicalDevices
	*/
	std::vector<PhysicalDevice> physical_devices_vector_;
};
#endif
