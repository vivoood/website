# Make list for lib_utils shared library
# folder: root/libs/lib_utils
# cmake_minimum_required(VERSION 3.0.2)
# 
# # Add includes directories
# include(UtilsOthers)
# include(UtilsFiles)
# include_directories(${EGT_ROOTDIR}/libs)
# 
# # Make preliminary checks
# CHECK_COMPILER_VERSION()
# GET_FOLDER_NAME()
# 
# # Add build target
# GET_CPP_RECURSIVE_IGNOREPATH(${CMAKE_CURRENT_SOURCE_DIR} "EmptyFactory" COMP_MGR_CPPS)
# BUILD_LIB(SHARED "${FOLDER_NAME}" "${COMP_MGR_CPPS}")
# 
# # Add dependecies
# CHECK_FOR_LIBRARY( "PugiXML"   "PUGIXML"   "libpugixml-dev"  )
# target_link_libraries(${FOLDER_NAME} UniObject UniStream ${PUGIXML_LIBRARY})
# 
# # Add definitions
# add_definitions(-fPIC)
# 
# # Add dependency to previous target
# CONNECT_TO_PREVIOUS_TARGET(${FOLDER_NAME})
# 
# set(CMAKE_EXE_LINKER_FLAGS "-WL,--unresolved-symbols=report-all")


cmake_minimum_required(VERSION 2.6)
project(ComponentsMgr)
set( build_files ComponentsMgr.cpp ComponentLogger.cpp HashConstructor.cpp IBaseComponent.cpp IBaseComponentBasicReaders.cpp IBaseComponentBasicWriters.cpp IBaseComponentHashes.cpp IBaseComponentTypes.cpp SerializeTools.cpp )

include_directories(${CMAKE_SOURCE_DIR}/library/utils/UniStream)
include_directories(${CMAKE_SOURCE_DIR}/library/utils/UniObject)
include_directories(${CMAKE_SOURCE_DIR}/library/utils/FunctionBinder)
include_directories(${CMAKE_SOURCE_DIR}/library/utils/GenericMsg)
include_directories(${CMAKE_SOURCE_DIR}/library/utils/GenericFunctionBinder)

add_library(ComponentsMgr SHARED ${build_files})
# target_link_libraries(ComponentsMgr ${external_shared_libs})
