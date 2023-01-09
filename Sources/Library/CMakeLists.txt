add_library(xdelta3_nx source/xdelta3.c source/Helper.cpp)

target_include_directories(xdelta3_nx PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        )

install(TARGETS xdelta3_nx)