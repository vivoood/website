cmake_minimum_required(VERSION 2.6)
project(XmlParsers)

set( build_files XmlGameFile.cpp XmlMultigameFile.cpp XmlReadFile.cpp XmlTools.cpp )

add_library(XmlParsers SHARED ${build_files})
target_link_libraries(XmlParsers pugixml)
