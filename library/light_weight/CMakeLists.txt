cmake_minimum_required(VERSION 2.6)
project(light_weight)

set( external_shared_libs wt wthttp boost_signals )

add_library(light_weight SHARED MainWidget.cpp)
target_link_libraries(light_weight ${external_shared_libs} primitives)
