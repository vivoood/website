cmake_minimum_required(VERSION 2.6)
project(light_weight)

set( external_shared_libs wt wthttp boost_signals crypto++ )
set( sourcefiles FreeOffers.cpp CWTableLayout.cpp Factory.cpp Debug.cpp CWOffer.cpp CWOwnerData.cpp CWHash.cpp )

add_library(light_weight SHARED MainWidget.cpp ${sourcefiles})
target_link_libraries(light_weight ${external_shared_libs})
