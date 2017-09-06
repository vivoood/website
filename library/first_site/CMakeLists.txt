cmake_minimum_required(VERSION 2.6)
project(first_site)

set( external_shared_libs wt wthttp boost_signals )

add_library(first_site SHARED MainWidget.cpp)
target_link_libraries(first_site ${external_shared_libs} primitives)
