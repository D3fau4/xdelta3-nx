cmake_minimum_required(VERSION 3.24)
project(xdelta3_nx C)

set(CMAKE_C_STANDARD 23)

# We have to add the cmake directory to have access to
# the Switch tools and also find_package for libnx.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# SwitchTools provide various helper functions for building Switch file formats.
include(SwitchTools)

# Find libnx, which is required by our application.
find_package(LIBNX REQUIRED)

target_include_directories(xdelta3_nx PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        )

add_library(xdelta3_nx source/xdelta3.c)