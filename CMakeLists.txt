cmake_minimum_required (VERSION 2.6)
project (goesdump)
enable_language(CXX)

# C++11 Macro
macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)

use_cxx11()

# Version
set (goesdump_VERSION_MAJOR 0)
set (goesdump_VERSION_MINOR 8)

# Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -pipe -march=native")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2 -pipe -march=native")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(CMAKE_MACOSX_RPATH 1)

# Executable
file(GLOB SOURCES src/*.cpp)
add_executable (${PROJECT_NAME} ${SOURCES})

# Links
target_link_libraries (${PROJECT_NAME} SatHelper)
target_link_libraries (${PROJECT_NAME} sz)
target_link_libraries (${PROJECT_NAME} aec)
target_link_libraries (${PROJECT_NAME} boost_system)
target_link_libraries (${PROJECT_NAME} boost_filesystem)

# Includes
include_directories ("${PROJECT_SOURCE_DIR}/include")
include_directories ("${PROJECT_SOURCE_DIR}/include/Headers")
include_directories ("${PROJECT_SOURCE_DIR}/include/Types")

# Debian Package
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Luigi Freitas")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libaec0")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "GOES Packets Decompressor")
INCLUDE(CPack)

# Make Directories
file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/build/logs")
file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/build/channels")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/lib $<TARGET_FILE_DIR:${PROJECT_NAME}>/lib)
