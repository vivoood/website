cmake_minimum_required(VERSION 2.6)
project(vivoood)

set(SOURCE WebSite.cpp HangmanWidget.cpp ImagesWidget.cpp)

add_executable(vivoood main.cpp ${SOURCE})

target_link_libraries(vivoood wt wthttp)
