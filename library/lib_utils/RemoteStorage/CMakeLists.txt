# Make list for lib_utils shared library
# folder: root/libs/lib_utils
cmake_minimum_required(VERSION 3.0.2)

# Add includes directories
include(UtilsOthers)
include(UtilsFiles)

# Make preliminary checks
CHECK_COMPILER_VERSION()

# Add build target
BUILD_LIBRARY_RECURSIVE(SHARED)

TARGET_LINK_LIBRARIES(${FOLDER_NAME} Platform)

include_directories(${EGT_ROOTDIR}/libs/)
include_directories(${EGT_ROOTDIR}/libs/lib_utils/)
#include_directories(${EGT_ROOTDIR}/common/)

# Add definitions
add_definitions(-fPIC)

# Add dependency to previous target
CONNECT_TO_PREVIOUS_TARGET(${FOLDER_NAME})

set(CMAKE_EXE_LINKER_FLAGS "-WL,--unresolved-symbols=report-all")
