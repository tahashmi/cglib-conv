# Minimum cmake version
cmake_minimum_required (VERSION 3.0.0)

# Name of project and that it is C++ only.
project (core CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# ----------------------------------------------------------------------------
# Dependencies
# ----------------------------------------------------------------------------

set(GLIB_INCLUDE_DIRS "/usr/include/glib-2.0") 
set(GLIBC_INCLUDE_DIRS "/usr/lib/x86_64-linux-gnu/glib-2.0/include")
# ----------------------------------------------------------------------------
# Build Setup
# ----------------------------------------------------------------------------

# Add include directories.
include_directories (
${GLIB_INCLUDE_DIRS}
${GLIBC_INCLUDE_DIRS})


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_library(LIB_ARROW arrow)
find_library(LIB_ARROW_CGLIB arrow-glib)
find_library(LIB_ARROW_GLIB glib-2.0) 
find_library(LIB_ARROW_GObject gobject-2.0)
find_library(LIB_ARROW_GGIOObject gio-2.0)

############################################################
# Create a library
############################################################

#Generate the shared library from the library sources
add_library(core SHARED
    core.cpp
)

target_include_directories(core
    PUBLIC 
        ${PROJECT_SOURCE_DIR}
)

## Add executable and link against SeqAn dependencies.
#add_executable (core core.cpp)

target_link_libraries (core ${LIB_ARROW} 
${LIB_ARROW_CGLIB} 
${LIB_ARROW_GLIB} 
${LIB_ARROW_GObject} 
${LIB_ARROW_GGIOObject}
)


# Library
# Note: may not work on windows
install (TARGETS core
    LIBRARY DESTINATION lib)

# Header files
install(DIRECTORY ${PROJECT_SOURCE_DIR}/ 
    DESTINATION include)

message("Lib arrow in: ${LIB_ARROW}")
