#ifndef VULKAN_EXPORTED_FUNC
#define VULKAN_EXPORTED_FUNC(func)
#endif

VULKAN_EXPORTED_FUNC(vkGetInstanceProcAddr)

#undef VULKAN_EXPORTED_FUNC

#ifndef VULKAN_GLOBAL_FUNC
#define VULKAN_GLOBAL_FUNC(func)
#endif

VULKAN_GLOBAL_FUNC(vkEnumerateInstanceExtensionProperties)
VULKAN_GLOBAL_FUNC(vkEnumerateInstanceLayerProperties)
VULKAN_GLOBAL_FUNC(vkCreateInstance)

#undef VULKAN_GLOBAL_FUNC

#ifndef VULKAN_INSTANCE_FUNC
#define VULKAN_INSTANCE_FUNC(func)
#endif

VULKAN_INSTANCE_FUNC(vkDestroyInstance)
VULKAN_INSTANCE_FUNC(vkEnumeratePhysicalDevices)
VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceProperties)
VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceQueueFamilyProperties)
VULKAN_INSTANCE_FUNC(vkCreateDevice)
VULKAN_INSTANCE_FUNC(vkDestroyDevice)


#undef VULKAN_INSTANCE_FUNC

#ifndef VULKAN_DEVICE_FUNC
#define VULKAN_DEVICE_FUNC(func)
#endif


#undef VULKAN_DEVICE_FUNC