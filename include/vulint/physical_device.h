#ifndef VULKAN_INTRO_PHYSICALDEVICE_H
#define VULKAN_INTRO_PHYSICALDEVICE_H

#include "vulkan/vulkan.h"

class PhysicalDevice
{
public:
	/**
	* Physical Device Constructor
	* @param vk_device vkDevice object to be stored in class
	*/
	PhysicalDevice(const VkPhysicalDevice& vk_device);

	~PhysicalDevice();

	/**
	* Sets the physical device properties struct
	* This is done outside constructor to allow physical devices to e constructed without info through VKEnumeratePhysicalDevices
	* @see device_properties_
	*/
	void SetProperties(const VkPhysicalDeviceProperties& properties);

private:
	VkPhysicalDeviceProperties device_properties_;
	VkPhysicalDevice device_handle_;
};

#endif