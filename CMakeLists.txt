cmake_minimum_required(VERSION 2.6)
project(vivoood)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )

add_subdirectory(library)

set(SOURCE WebSite.cpp)
set(internal_libs hangman)

include_directories(library)

add_executable(vivoood main.cpp ${SOURCE})
target_link_libraries(vivoood ${internal_libs} )

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    
    COMMAND rm ${CMAKE_BINARY_DIR}/WebStyle.css 
    COMMAND ln -s ${CMAKE_SOURCE_DIR}/data/WebStyle.css ${CMAKE_BINARY_DIR}
    
    COMMAND rm ${CMAKE_BINARY_DIR}/WebTemplates.xml 
    COMMAND ln -s ${CMAKE_SOURCE_DIR}/data/WebTemplates.xml ${CMAKE_BINARY_DIR}
    
    COMMAND rm -rf ${CMAKE_BINARY_DIR}/pics
    COMMAND cp -rf ${CMAKE_SOURCE_DIR}/data/pics ${CMAKE_BINARY_DIR}
)
