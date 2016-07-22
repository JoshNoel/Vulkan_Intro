::Personal generate script for vulkan intro
::Generates and builds dependencies for 64 bit Windows
::@ECHO OFF
setlocal

set base_dir=%CD%
set cmake_dir=C:\Program Files\CMake\bin\cmake.exe
set msbuild_dir=C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe

set windows_helper_dir=%CD%\lib\WindowsHelper
set cmake_generator="Visual Studio 14 2015 Win64"
set build_dir_name=build64

::Generate WindowsHelper Library and build
cd %windows_helper_dir%
mkdir %build_dir_name%
cd %build_dir_name%
start /WAIT "Cmake Generating WindowsHelper" "%cmake_dir%" -G %cmake_generator% ..
start /WAIT "Debug Build" "%msbuild_dir%" /p:configuration=debug "WindowsHelper.sln"
start /WAIT "Release Build" "%msbuild_dir%" /p:configuration=release "WindowsHelper.sln"
cd %base_dir%

::Make Debug and release directories, if Vulkan_Intro has not been built yet to create them
mkdir "%base_dir%\%build_dir_name%\bin\Debug"
mkdir "%base_dir%\%build_dir_name%\bin\Release"


::Copy WindowsHelper lib files
xcopy "%windows_helper_dir%\%build_dir_name%\bin\Debug\WindowsHelper.dll" "%base_dir%\%build_dir_name%\bin\Debug"
xcopy "%windows_helper_dir%\%build_dir_name%\bin\Debug\WindowsHelper.lib" "%base_dir%\%build_dir_name%\bin\Debug"
xcopy "%windows_helper_dir%\%build_dir_name%\bin\Debug\WindowsHelper.pdb" "%base_dir%\%build_dir_name%\bin\Debug"

xcopy "%windows_helper_dir%\%build_dir_name%\bin\Release\WindowsHelper.dll" "%base_dir%\%build_dir_name%\bin\Release"
xcopy "%windows_helper_dir%\%build_dir_name%\bin\Release\WindowsHelper.lib" "%base_dir%\%build_dir_name%\bin\Release"

::Generate Vulkan_Intro Project
cd %build_dir_name%%
start /WAIT "CMake Generating Vulkan_Intro" "%cmake_dir%" -G %cmake_generator% ..

endlocal
pause