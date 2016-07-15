#include "vulint/vulkan_core.h"
#include <iostream>

VulkanCore::VulkanCore()
{
	vulkan_library_ = LoadLibrary("vulkan-1.dll");
}

VulkanCore::~VulkanCore()
{
	if (!FreeLibrary(vulkan_library_))
	{
		//TODO: Handle Error
	}
}