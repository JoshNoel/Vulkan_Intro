#ifndef VULKAN_INTRO_VULKANCORE_H
#define VULKAN_INTRO_VULKANCORE_H

#include "vulkan/vulkan.h"
#include <Windows.h>
#include <array>
#include <string>
#include <vector>
#include "vulint/device_manager.h"

/**
* Handles dynamic loading of vulkan library and functions
*/
class VulkanCore
{
public:
	/**
	* VulkanCore constructor.
	* Loads the vulkan dll
	*/
	VulkanCore();

	/**
	* VulkanCore desctructor.
	* Frees the vulkan dll handle
	*/
	~VulkanCore();

	VulkanCore(const VulkanCore&) = delete;
	VulkanCore& operator=(const VulkanCore&) = delete;

	/**
	* Initializes instances and devices
	* @param app_name Application name
	* @param app_version holds the application version in format {major, minor, patch}
	*/
	bool InitInstance(const std::string& app_name, const std::array<int, 3> app_version);

	/**
	* Initializes devices
	* @param max_devices maximum number of devices to query. If 0 all available devices will be queried
	* @param max_queues maximum number of queue families to query. If 0 all available devices will be queried
	*/
	bool InitDevices(const int max_devices, bool print_device_properties, const int max_queues, bool print_queue_properties);

	//TODO: Create a function that will create a logical device based off of a set of parameters
	/**
	* Creates a logical device based off of parameters
	*/
	bool createLogicalDevice();

private:
	/**
	* Handle to vulkan dll
	*/
	HMODULE vulkan_library_;

	/**
	* Handles lifetime of all logical devices
	*/
	DeviceManager device_manager_;

	//useful for mainting stability of function loading macro
#define VULKAN_INSTANCE_VAR_NAME vulkan_instance_
	/**
	* Handle to VKInstance
	*/
	VkInstance VULKAN_INSTANCE_VAR_NAME;

	/**
	* Sets exported function pointer variables defined in vulkan_funcs.cpp
	*/
	void InitExportedFunctions() const;

	/**
	* Sets global function pointer variables defined in vulkan_funcs.cpp
	*/
	void InitGlobalFunctions() const;

	/**
	* Sets instance function pointer variables defined in vulkan_funcs.cpp
	*/
	void InitInstanceFunctions() const;
};

#endif // !VULKAN_INTRO_VCORE_H
