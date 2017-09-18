# # Make list for lib_utils shared library
# # folder: root/libs/lib_utils
# cmake_minimum_required(VERSION 3.0.2)
# 
# # Add includes directories
# include(UtilsOthers)
# include(UtilsFiles)
# include_directories(${EGT_ROOTDIR}/libs)
# 
# # Make preliminary checks
# CHECK_COMPILER_VERSION()
# 
# # Add build target
# BUILD_LIBRARY_RECURSIVE(SHARED)
# 
# target_link_libraries("${FOLDER_NAME}" GenericMsg UniStream)
# 
# # Add definitions
# add_definitions(-fPIC)
# 
# # Add dependency to previous target
# CONNECT_TO_PREVIOUS_TARGET(${FOLDER_NAME})
# 
# set(CMAKE_EXE_LINKER_FLAGS "-WL,--unresolved-symbols=report-all")

cmake_minimum_required(VERSION 2.6)
project(UniObject)

set( build_files UniMsg.cpp UniObject.cpp )

include_directories(${CMAKE_SOURCE_DIR}/library/utils/UniStream)
include_directories(${CMAKE_SOURCE_DIR}/library/utils/GenericMsg)

add_library(UniObject SHARED ${build_files})
# target_link_libraries(UniObject ${external_shared_libs})
