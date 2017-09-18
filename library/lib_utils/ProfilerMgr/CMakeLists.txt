# Make list for lib_utils shared library
# folder: root/libs/lib_utils/ProfilerMgr
cmake_minimum_required(VERSION 3.0.2)

# Add includes directories
include(UtilsOthers)
include(UtilsFiles)
include_directories(${EGT_ROOTDIR}/libs)

# Make preliminary checks
CHECK_COMPILER_VERSION()
GET_FOLDER_NAME()

# Add build target
BUILD_LIBRARY_RECURSIVE(SHARED)

# Add dependecies
target_link_libraries(${FOLDER_NAME} Profiler Network)

# Add definitions
add_definitions(-fPIC)

# Add dependency to previous target
CONNECT_TO_PREVIOUS_TARGET(${FOLDER_NAME})

set(CMAKE_EXE_LINKER_FLAGS "-WL,--unresolved-symbols=report-all")
