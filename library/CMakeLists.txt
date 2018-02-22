cmake_minimum_required(VERSION 2.6)
project(extender)

set( external_shared_libs wt wthttp boost_signals crypto++ )

add_library(extender SHARED CWUser.cpp Factory.cpp Debug.cpp EntryOne.cpp CWTable.cpp CWCenterColumn.cpp CWLoginCell.cpp CWLineEditField.cpp CWSignals.cpp CWIntroPage.cpp CWSignIn.cpp CWOwnerPage.cpp CWOffersInserter.cpp CWOffersView.cpp CWPublicOffersView.cpp )
target_link_libraries(extender ${external_shared_libs})
