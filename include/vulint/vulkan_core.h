#ifndef VULKAN_INTRO_VULKANCORE_H
#define VULKAN_INTRO_VULKANCORE_H

#include <Windows.h>

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

private:
	/**
	* Handle to vulkan dll
	*/
	HMODULE vulkan_library_;

	/**
	* Loads function pointers for functions listed in vulkanFunctionList.h
	* Then it declares the functions with their correct names using these pointers
	*/
	void InitFunctions();
};

#endif // !VULKAN_INTRO_VCORE_H
