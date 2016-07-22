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

set(TARGET_NAME Vulkan_Intro)
project(${TARGET_NAME})
#DEVELOPMENT ENV VARIABLES
#WindowsHelper Library
find_path(windows_helper_include_dir NAMES winhelp/WindowsHelper.h PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib/WindowsHelper/include)
find_library(windows_helper_library_debug WindowsHelper PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib/WindowsHelper/build64/bin/Debug)
find_library(windows_helper_library_release WindowsHelper PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib/WindowsHelper/build64/bin/Release)


#add include directories to variable in subdirectories, add to master after
set(additional_include_dirs "")
add_subdirectory(include)
add_subdirectory(src)
include_directories(${additional_include_dirs} ${windows_helper_include_dir})

add_executable(${TARGET_NAME} ${SRC_FILE_LIST} ${HEADER_FILE_LIST})
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
target_link_libraries(${TARGET_NAME} debug ${windows_helper_library_debug})
target_link_libraries(${TARGET_NAME} optimized ${windows_helper_library_release})
add_definitions(-DVK_NO_PROTOTYPES)