cmake_minimum_required(VERSION 3.30)
project(ansi)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# CMAKE_BINARY_DIR should be build
set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(INSTALL_DIR /usr/local/bin)

# tests options

# Root include directory
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
# Collect all directories (recursively)
file(GLOB_RECURSE HEADER_DIRS LIST_DIRECTORIES true "${INCLUDE_DIR}/*")
# Initialize the include directories list with the root
set(INCLUDE_DIRS ${INCLUDE_DIR})
# Filter directories explicitly
foreach (DIR ${HEADER_DIRS})
    if (IS_DIRECTORY "${DIR}")
        list(APPEND INCLUDE_DIRS "${DIR}")
    endif ()
endforeach ()
# Remove duplicates (just in case)
list(REMOVE_DUPLICATES INCLUDE_DIRS)

# Source files
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.c++)

# Set output directories for executables and libraries
# Define output directories for executables and libraries
# The ${CMAKE_BINARY_DIR} changes dynamically based on the build directory.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Optimization flags
set(OPT_FLAGS "-O3 -march=native -flto")
set(DEBUG_FLAGS "-g -O0 -fno-omit-frame-pointer")
set(RELEASE_FLAGS "${OPT_FLAGS} -DNDEBUG")
set(RELWITHDEBINFO_FLAGS "${OPT_FLAGS} -g -DNDEBUG")
set(EXTRA_FLAGS "-fexperimental-library")

# Combine flags for each build type
set(CMAKE_CXX_FLAGS_DEBUG "${DEBUG_FLAGS} ${EXTRA_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${RELEASE_FLAGS} ${EXTRA_FLAGS}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${RELWITHDEBINFO_FLAGS} ${EXTRA_FLAGS}")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${RELEASE_FLAGS} -Os ${EXTRA_FLAGS}")

# Add the library
add_library(${PROJECT_NAME} ansi.h++ ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

# Optional: Add SO versioning for shared libraries
if (BUILD_SHARED_LIBS)
    set_target_properties(${PROJECT_NAME} PROPERTIES
      VERSION 0.0.1
      SOVERSION 0
    )
endif ()
