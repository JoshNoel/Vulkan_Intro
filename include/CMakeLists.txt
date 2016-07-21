cmake_minimum_required(VERSION 3.6)

set(inc_dir vulint)
set(HEADER_FILE_LIST	vulkan_core.h
						vulkan_funcs.h
						logical_device.h
						physical_device.h
						vulkan_func_list.inl
						device_manager.h)

prepend(HEADER_FILE_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${inc_dir})
set(HEADER_FILE_LIST ${HEADER_FILE_LIST} PARENT_SCOPE)

set(additional_include_dirs "${additional_include_dirs} ${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)
