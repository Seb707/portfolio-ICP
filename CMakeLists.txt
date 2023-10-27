cmake_minimum_required(VERSION 3.15)
project(GTI320-labo-02)

include(CMakeDependentOption)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include( build-google-test )
include( build-nanogui )

add_subdirectory(labo01)
add_subdirectory(labo02)

if( MSVC )
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT labo02)
endif()