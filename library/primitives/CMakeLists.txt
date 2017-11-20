cmake_minimum_required(VERSION 2.6)
project(primitives)

set( external_shared_libs wt wthttp boost_signals crypto++ )

add_library(primitives SHARED CWHash.cpp CWSignals.cpp CWOwnerData.cpp CWOwnerFreeOffers.cpp CWValidators.cpp CWLeftCol.cpp CWCombo.cpp CWUserLineInput.cpp CWRegisterAccount.cpp CWAfterLogin.cpp CWLogin.cpp CWHeader.cpp CWTabs.cpp CWRadioButtons.cpp CWTableLayout.cpp CWContiCtryForm.cpp CWFooter.cpp CWOffer.cpp CWUser.cpp CWPublicOffers.cpp CWFAQ.cpp CWDreamTeam.cpp CWOwnerSettings.cpp CWOwnerContainer.cpp CWAccount.cpp CWContacts.cpp CWOwnerFreeOffersView.cpp CWQuery.cpp CWOfferBig.cpp CWMyQueries.cpp Factory.cpp Debug.cpp Constants.cpp)
target_link_libraries(primitives ${external_shared_libs})
