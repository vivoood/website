cmake_minimum_required(VERSION 2.6)
project(extender)

set( external_shared_libs wt wthttp boost_signals crypto++ )

add_library(extender SHARED CWHash.cpp CWUser.cpp Factory.cpp Debug.cpp EntryOne.cpp CWTable.cpp CWCenterColumn.cpp )
target_link_libraries(extender ${external_shared_libs})
