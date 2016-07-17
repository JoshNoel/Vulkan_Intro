#include "vulkan/vulkan.h"

/**
* This file defines function pointers for vulkan API
*/
#define VULKAN_EXPORTED_FUNC(func) PFN_##func func;
#define VULKAN_GLOBAL_FUNC(func) PFN_##func func;
#define VULKAN_INSTANCE_FUNC(func) PFN_##func func;
#define VULKAN_DEVICE_FUNC(func) PFN_##func func;


#include "vulint/vulkan_func_list.inl"
