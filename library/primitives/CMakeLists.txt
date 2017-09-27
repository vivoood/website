cmake_minimum_required(VERSION 2.6)
project(primitives)

set( external_shared_libs wt wthttp boost_signals )

add_library(primitives SHARED CWSignals.cpp CWHeader.cpp CWTabs.cpp CWTableLayout.cpp CWFooter.cpp CWOffer.cpp CWPublicOffers.cpp CWFAQ.cpp CWContacts.cpp Factory.cpp Constants.cpp)
target_link_libraries(primitives ${external_shared_libs})
