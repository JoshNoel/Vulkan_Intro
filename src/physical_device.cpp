#include "vulint/physical_device.h"
#include "vulint/vulkan_funcs.h"
#include <utility>

PhysicalDevice::PhysicalDevice(const VkPhysicalDevice& vk_device)
{
	device_handle_ = vk_device;
}

PhysicalDevice::~PhysicalDevice() 
{ }

void PhysicalDevice::SetProperties(const VkPhysicalDeviceProperties& properties)
{
	device_properties_ = properties;
}
