cmake_minimum_required(VERSION 3.6)

set(SRC_FILE_LIST main.cpp
				  vulkan_core.cpp
				  vulkan_funcs.cpp)
				  
prepend(SRC_FILE_LIST ${CMAKE_CURRENT_SOURCE_DIR})

set(SRC_FILE_LIST ${SRC_FILE_LIST} PARENT_SCOPE)
#remember to update list of source files
