#ifndef VULKAN_INTRO_VULKANFUNCS_H
#define VULKAN_INTRO_VULKANFUNCS_H

#include "vulkan/vulkan.h"

/**
* This file declares function pointers for vulkan API
*/

#define VULKAN_EXPORTED_FUNC(func) extern PFN_##func func;
#define VULKAN_GLOBAL_FUNC(func) extern PFN_##func func;
#define VULKAN_INSTANCE_FUNC(func) extern PFN_##func func;
#define VULKAN_DEVICE_FUNC(func) extern PFN_##func func;

#include "vulint/vulkan_func_list.inl"

#endif