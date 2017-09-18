cmake_minimum_required(VERSION 2.6)
project(utils)

add_subdirectory(ComponentsMgr)
add_subdirectory(UniStream)
add_subdirectory(UniObject)
add_subdirectory(XmlParsers)
add_subdirectory(GenericMsg)
add_subdirectory(GenericFunctionBinder)
add_subdirectory(FunctionBinder)
add_subdirectory(Network)
add_subdirectory(TaskMgr)
add_subdirectory(Platform)

set(LIBXML2_INCLUDE_DIR "/usr/include/libxml2/" ) 
include_directories(${LIBXML2_INCLUDE_DIR})

set( build_files OnExit.cpp MGValidate.cpp Crc.cpp )
set( other_libs ComponentsMgr UniStream UniObject XmlParsers GenericMsg GenericFunctionBinder FunctionBinder Network TaskMgr Platform )

add_library(utils SHARED ${build_files})
target_link_libraries(utils ${other_libs})
