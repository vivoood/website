# # Make list for lib_utils shared library
# # folder: root/libs/lib_utils/Profiler
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
# # Add definitions
# add_definitions(-fPIC)
# 
# # Add dependency to previous target
# CONNECT_TO_PREVIOUS_TARGET(${FOLDER_NAME})
# 
# set(CMAKE_EXE_LINKER_FLAGS "-WL,--unresolved-symbols=report-all")

cmake_minimum_required(VERSION 2.6)
project(TaskMgr)
set( build_files TaskMgr.cpp )

add_library(TaskMgr SHARED ${build_files} ${build_files_net_base} ${build_files_networks} )
# target_link_libraries(TaskMgr ${external_shared_libs})
