# Make list for lib_utils shared library
# folder: root/libs/lib_utils
cmake_minimum_required(VERSION 3.0.2)

# Add includes directories
include(UtilsOthers)
include(UtilsFiles)
include_directories(${EGT_ROOTDIR}/libs)

# Make preliminary checks
CHECK_COMPILER_VERSION()
GET_FOLDER_NAME()

# Add build target
GET_CPP_RECURSIVE_IGNOREPATH(${CMAKE_CURRENT_SOURCE_DIR} "EmptyFactory" COMP_MGR_CPPS)
BUILD_LIB(SHARED "${FOLDER_NAME}" "${COMP_MGR_CPPS}")

# Add dependecies
CHECK_FOR_LIBRARY( "PugiXML"   "PUGIXML"   "libpugixml-dev"  )
target_link_libraries(${FOLDER_NAME} UniObject UniStream ${PUGIXML_LIBRARY})

# Add definitions
add_definitions(-fPIC)

# Add dependency to previous target
CONNECT_TO_PREVIOUS_TARGET(${FOLDER_NAME})

set(CMAKE_EXE_LINKER_FLAGS "-WL,--unresolved-symbols=report-all")
