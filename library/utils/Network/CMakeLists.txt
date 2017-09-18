# Make list for lib_utils shared library
# folder: root/libs/lib_utils
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
# TARGET_LINK_LIBRARIES(${FOLDER_NAME} Platform)
# 
# # Add definitions
# add_definitions(-fPIC)
# 
# # Add dependency to previous target
# CONNECT_TO_PREVIOUS_TARGET(${FOLDER_NAME})
# target_include_directories(${FOLDER_NAME} PUBLIC ${EGT_ROOTDIR}/libs)
# 
# set(CMAKE_EXE_LINKER_FLAGS "-WL,--unresolved-symbols=report-all")

cmake_minimum_required(VERSION 2.6)
project(Network)
set( build_files Network.cpp )
set( build_files_net_base NetworkBase/IConnection.cpp NetworkBase/IConnector.cpp NetworkBase/NetMsg.cpp )
set( build_files_networks Networks/BashClient.cpp Networks/LocalClient.cpp Networks/LocalConnection.cpp Networks/LocalServer.cpp )

include_directories(${CMAKE_SOURCE_DIR}/library/utils/UniStream)
include_directories(${CMAKE_SOURCE_DIR}/library/utils/Platform)

add_library(Network SHARED ${build_files} ${build_files_net_base} ${build_files_networks} )
# target_link_libraries(Network ${external_shared_libs})
