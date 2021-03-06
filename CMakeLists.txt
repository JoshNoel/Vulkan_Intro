cmake_minimum_required(VERSION 3.6)

function(prepend strings prefix)
	#${strings} = list name
	#${${strings}} = list dereferenced
	set(swap_tmp "")
	foreach(str ${${strings}})
		set(swap_tmp ${swap_tmp} ${prefix}/${str})
	endforeach(str)
	
	set(${strings} ${swap_tmp})
	set(${strings} ${swap_tmp} PARENT_SCOPE)
endfunction(prepend)

#DEVELOPMENT ENV VARIABLES
#WindowsHelper Library
find_path(windows_helper_include_dir winhelp/WindowsHelper.h)
message(STATUS "Windows Helper include dir: " ${windows_helper_include_dir})

set(TARGET_NAME Vulkan_Intro)
project(${TARGET_NAME})

#add include directories to variable in subdirectories, add to master after
set(additional_include_dirs "")
add_subdirectory(include)
add_subdirectory(src)
include_directories(${additional_include_dirs} ${windows_helper_include_dir})

add_executable(${TARGET_NAME} ${SRC_FILE_LIST} ${HEADER_FILE_LIST})
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
