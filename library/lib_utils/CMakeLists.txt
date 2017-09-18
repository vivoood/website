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

# Add subdirectories
add_subdirectory(ComponentsMgr)
add_subdirectory(GenericMsg)
add_subdirectory(GenericFunctionBinder)
add_subdirectory(UniObject)
add_subdirectory(UniStream)
add_subdirectory(FunctionBinder)
add_subdirectory(Network)
add_subdirectory(Profiler)
add_subdirectory(RemoteStorage)
add_subdirectory(ProfilerMgr)
add_subdirectory(Platform)
add_subdirectory(TaskMgr)


# Make static version of lib_utils
GET_CPP_RECURSIVE_IGNOREPATH(${CMAKE_CURRENT_SOURCE_DIR} "UniStream;UniObject;ComponentsMgr;GenericMsg;GenericFunctionBinder;FunctionBinder;Network;Profiler;RemoteStorage;ProfilerMgr;Platform;TaskMgr" LIB_UTILS_CPPS)
BUILD_LIB(SHARED "${FOLDER_NAME}" "${LIB_UTILS_CPPS}")

# Make static version of lib_utils TO BE REMOVED!!
GET_CPP_RECURSIVE(${CMAKE_CURRENT_SOURCE_DIR} LIB_CPPS)

CHECK_FOR_LIBRARY( "OpenSSL"   "OPENSSL"   "libssl-dev"      )
CHECK_FOR_LIBRARY( "Crypto"    "CRYPTO"    "libcrypto++-dev" )
CHECK_FOR_LIBRARY( "PugiXML"   "PUGIXML"   "libpugixml-dev"  )
CHECK_FOR_LIBRARY( "LibXml2"   "LIBXML2"   "libxml2-dev"  )

target_link_libraries(lib_utils egt_debug utils ${OPENSSL_LIBRARIES} ${PUGIXML_LIBRARY} ${CRYPTO_LIBRARY} ComponentsMgr GenericMsg GenericFunctionBinder UniObject UniStream FunctionBinder Network Profiler RemoteStorage TaskMgr ${LIBXML2_LIBRARIES})

# Add definitions
add_definitions(-fPIC)
include_directories(${LIBXML2_INCLUDE_DIR})

# Add dependency to previous target
CONNECT_TO_PREVIOUS_TARGET(${FOLDER_NAME})

set(CMAKE_EXE_LINKER_FLAGS "-WL,--unresolved-symbols=report-all")
