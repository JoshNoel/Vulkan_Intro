#ifndef VULKAN_INTRO_VULKANCORE_H
#define VULKAN_INTRO_VULKANCORE_H

#include <Windows.h>

class VulkanCore
{
public:
	VulkanCore();
	~VulkanCore();

private:
	HMODULE vulkan_library_;
};

#endif // !VULKAN_INTRO_VCORE_H
