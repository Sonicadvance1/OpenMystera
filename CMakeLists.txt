########################################
# General setup
#
cmake_minimum_required(VERSION 2.6)
project(Test)

# Set up paths
set(bindir	${CMAKE_INSTALL_PREFIX}/bin	CACHE PATH "bindir")

# Set where the binary files will be built. The program will not execute from
# here. You must run "make install" to install these to the proper location
# as defined above.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binaries)


if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE "Release" CACHE STRING
"Build type (Release/Debug/RelWithDebInfo/MinSizeRe)" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
add_definitions(-ggdb)
add_definitions(-D_DEBUG_)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

if(CMAKE_BUILD_TYPE STREQUAL Release)
add_definitions(-fomit-frame-pointer -O2)
endif(CMAKE_BUILD_TYPE STREQUAL Release)

add_definitions(-Wno-unused-result)
add_definitions(-Wall -Wextra -Werror)
# Add our common directory for Common includes
include_directories(Common/Src)


########################################
# Start compiling our code
#

add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)


# packaging information
set(CPACK_PACKAGE_NAME "OpenMystera")
set(CPACK_PACKAGE_VENDOR "OpenMystera Team")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")


# TODO: CPACK_PACKAGE_DESCRIPTION_FILE
# TODO: CPACK_PACKAGE_DESCRIPTION_SUMMARY
# TODO: CPACK_RESOURCE_FILE_README
# TODO: CPACK_RESOURCE_FILE_WELCOME
# TODO: CPACK_PACKAGE_EXECUTABLES
# TODO: CPACK_PACKAGE_ICON
# TODO: CPACK_NSIS_*

set(CPACK_SET_DESTDIR ON)
set(CPACK_SOURCE_GENERATOR "TGZ;TBZ2;ZIP")
set(CPACK_SOURCE_IGNORE_FILES "\\\\.#;/#;.*~;\\\\.swp;/\\\\.svn")
list(APPEND CPACK_SOURCE_IGNORE_FILES "${CMAKE_BINARY_DIR}")

# CPack must be included after the CPACK_* variables are set in order for those
# variables to take effect.
include(CPack)
