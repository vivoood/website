# # Make list for lib_utils shared library
# # folder: root/libs/lib_utils/Platform
# cmake_minimum_required(VERSION 3.0.2)
# 
# # Add includes directories
# include(UtilsOthers)
# include(UtilsFiles)
# 
# # Make preliminary checks
# CHECK_COMPILER_VERSION()
# 
# # Add build target
# BUILD_LIBRARY_RECURSIVE(SHARED)
# 
# include_directories(${EGT_ROOTDIR}/libs/)
# 
# # Add definitions
# add_definitions(-fPIC)
# 
# # Add dependency to previous target
# CONNECT_TO_PREVIOUS_TARGET(${FOLDER_NAME})
# 
# set(CMAKE_EXE_LINKER_FLAGS "-WL,--unresolved-symbols=report-all")

cmake_minimum_required(VERSION 2.6)
project(Platform)
set( build_files PlatformProcesses.cpp PlatformSockets.cpp PlatformThreads.cpp )

add_library(Platform SHARED ${build_files} )
# target_link_libraries(Platform ${external_shared_libs})
