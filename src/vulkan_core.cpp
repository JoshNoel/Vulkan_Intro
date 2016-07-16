#include "vulint/vulkan_core.h"
#include "winhelp/ErrorHandling.h"
#include <iostream>
#include <vulkan/vulkan.h>

//functions are loaded dynamically
//VK_NO_PROTOTYPES ensures vulkan function declarations are not made in "vulkan.h"
//	this ensures functions not loaded from "vulkan-1.dll" are not declared.
//	If static linking with vulkan every declaration in "vulkan.h" would be defined,
//	but this is not true with dynamic linking

VulkanCore::VulkanCore()
{
	vulkan_library_ = LoadLibrary("vulkan-1.dll");
	InitFunctions();
}

void VulkanCore::InitFunctions()
{
	
}


VulkanCore::~VulkanCore()
{
	if (!FreeLibrary(vulkan_library_))
	{	
		//TODO: Possibly display errors using message boxes instead
		std::cerr << WinHelper::GetLastSystemError() << std::endl;
	}
}