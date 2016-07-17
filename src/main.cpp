#include "vulint/vulkan_core.h"
#include <iostream>
#include <exception>

int main()
{
		VulkanCore vulkan_core;
		if (!vulkan_core.InitInstance("Vulkan Intro App", std::array<int, 3>{{1, 0, 0}}))
			return -1;
		if (!vulkan_core.InitDevices(0, true, 0, true))
			return -1;

		std::cout << "Program exited correctly!!" << std::endl << "Press any key to continue..." << std::endl;

		std::getchar();
	return 0;
}