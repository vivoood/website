cmake_minimum_required(VERSION 2.6)
project(vivoood)

option(gccv "gccv" 0x)

if (${gccv} STREQUAL "0x")
	SET(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

if (${gccv} STREQUAL "11")
	set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
endif()

if (${gccv} STREQUAL "14")
	set (CMAKE_CXX_FLAGS "--std=gnu++14 ${CMAKE_CXX_FLAGS}")
endif()

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )

add_subdirectory(library)

set(SOURCE WebSite.cpp)
set(internal_libs first_site)

include_directories(library)

add_executable(vivoood main.cpp ${SOURCE})
target_link_libraries(vivoood ${internal_libs} dl )

option(enable_rm "enable_rm" OFF)
message(STATUS ">>>>>>>> ENABLE RM IS " ${enable_rm})
if (${enable_rm} STREQUAL "ON")
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND rm ${CMAKE_BINARY_DIR}/WebStyle.css
		COMMAND rm ${CMAKE_BINARY_DIR}/WebTemplates.xml
		COMMAND rm ${CMAKE_BINARY_DIR}/pics
		COMMAND rm ${CMAKE_BINARY_DIR}/users
		COMMAND rm ${CMAKE_BINARY_DIR}/autorun.sh
		COMMAND rm ${CMAKE_BINARY_DIR}/autorun.py
		
        COMMAND ln -s ${CMAKE_SOURCE_DIR}/data/WebStyle.css ${CMAKE_BINARY_DIR}
        COMMAND ln -s ${CMAKE_SOURCE_DIR}/data/WebTemplates.xml ${CMAKE_BINARY_DIR}
        COMMAND ln -s ${CMAKE_SOURCE_DIR}/data/pics ${CMAKE_BINARY_DIR}
        COMMAND ln -s ${CMAKE_SOURCE_DIR}/data/users ${CMAKE_BINARY_DIR}
        COMMAND ln -s ${CMAKE_SOURCE_DIR}/data/autorun.sh ${CMAKE_BINARY_DIR}
        COMMAND ln -s ${CMAKE_SOURCE_DIR}/data/autorun.py ${CMAKE_BINARY_DIR}
	)
endif()

# add_custom_command(
#     TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ln -s ${CMAKE_SOURCE_DIR}/data/WebStyle.css ${CMAKE_BINARY_DIR}
#     COMMAND ln -s ${CMAKE_SOURCE_DIR}/data/WebTemplates.xml ${CMAKE_BINARY_DIR}
#     COMMAND ln -s ${CMAKE_SOURCE_DIR}/data/pics ${CMAKE_BINARY_DIR}
#     COMMAND ln -s ${CMAKE_SOURCE_DIR}/data/users ${CMAKE_BINARY_DIR}
#     COMMAND ln -s ${CMAKE_SOURCE_DIR}/data/autorun.sh ${CMAKE_BINARY_DIR}
#     COMMAND ln -s ${CMAKE_SOURCE_DIR}/data/autorun.py ${CMAKE_BINARY_DIR}
# )
