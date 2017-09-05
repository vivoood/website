cmake_minimum_required(VERSION 2.6)
project(vivoood)

set(SOURCE WebSite.cpp HangmanWidget.cpp ImagesWidget.cpp)

add_executable(vivoood main.cpp ${SOURCE})

# file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(vivoood wt wthttp)
