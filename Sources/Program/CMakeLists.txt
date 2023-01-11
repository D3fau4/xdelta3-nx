# First, we want to add the regular ELF target.
add_executable(xdelta_nx_test source/main.cpp)

# Next, we need to set the required target properties
# so CMake can detect the metadata for the application.
set_target_properties(xdelta_nx_test PROPERTIES
        APP_TITLE "Xdelta test"
        APP_AUTHOR "D3fau4"
        APP_VERSION "0.1.0"
        ROMFS "${CMAKE_CURRENT_LIST_DIR}/romfs"
        )

target_include_directories(xdelta_nx_test PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        )

# Then, we link the required libraries (libnx) against the executable.
target_link_libraries(xdelta_nx_test switch::libnx xdelta3_nx)

# Set these variables if you don't want to use an icon or
# don't want `add_nro_target` to generate a .nacp file.
set(NO_ICON TRUE)
#set(NO_NACP TRUE)

# And finally we can add the actual binary (.nro) target.
add_nro_target(xdelta_nx_test)