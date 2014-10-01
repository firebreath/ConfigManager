
include_directories(
    ${FB_SCRIPTINGCORE_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${FB_CONFIG_DIR})

file (GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    [^.]*.cpp
    [^.]*.h
    )

add_library(fbConfigManager ${SOURCES})

append_firebreath_link_library(${PROJECT_NAME})
append_firebreath_include_dir(${CMAKE_CURRENT_SOURCE_DIR})
