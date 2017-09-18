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
# target_link_libraries(${FOLDER_NAME} UniStream)
# 
# # Add definitions
# add_definitions(-fPIC)
# 
# # Add dependency to previous target
# CONNECT_TO_PREVIOUS_TARGET(${FOLDER_NAME})
# 
# set(CMAKE_EXE_LINKER_FLAGS "-WL,--unresolved-symbols=report-all")

cmake_minimum_required(VERSION 2.6)
project(FunctionBinder)
set( build_files BindableObject.cpp BinderLogger.cpp FunctionCallErrors.cpp )
set( build_files_binder FunctionBinder/FunctionBinder.cpp )
set( build_files_caller FunctionCaller/FunctionCaller.cpp )
set( build_files_connec FunctionConnector/BlockingFunctionConnector.cpp FunctionConnector/RemoteFunctionConnector.cpp FunctionConnector/SimpleFunctionConnector.cpp )

include_directories(${CMAKE_SOURCE_DIR}/library/utils/Network)

add_library(FunctionBinder SHARED ${build_files} ${build_files_binder} ${build_files_caller} ${build_files_connec} )
# target_link_libraries(FunctionBinder ${external_shared_libs})
