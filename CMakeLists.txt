cmake_minimum_required(VERSION 2.6)
project(vivoood)

set(SOURCE WebSite.cpp HangmanWidget.cpp ImagesWidget.cpp)

add_executable(vivoood main.cpp ${SOURCE})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    
    COMMAND rm ${CMAKE_BINARY_DIR}/WebStyle.css 
    COMMAND ln -s ${CMAKE_SOURCE_DIR}/WebStyle.css ${CMAKE_BINARY_DIR}
    
    COMMAND rm ${CMAKE_BINARY_DIR}/WebTemplates.xml 
    COMMAND ln -s ${CMAKE_SOURCE_DIR}/WebTemplates.xml ${CMAKE_BINARY_DIR}
    
    COMMAND rm -rf ${CMAKE_BINARY_DIR}/data
    COMMAND cp -rf ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}
)

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(vivoood wt wthttp)
