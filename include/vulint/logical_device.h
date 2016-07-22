#ifndef VULKAN_INTRO_LOGICALDEVICE_H
#define VULKAN_INTRO_LOGICALDEVICE_H

#include "vulkan/vulkan.h"

class LogicalDevice
{
public:
	LogicalDevice(){}
	~LogicalDevice(){}

	LogicalDevice(const LogicalDevice&) = delete;
	LogicalDevice& operator=(const LogicalDevice&) = delete;

private:

	VkDevice logical_device_handle_;
};

#endif