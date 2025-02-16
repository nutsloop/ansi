cmake_minimum_required(VERSION 3.30)
project(ansi)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# tests options

# Root include directory
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Source files
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.c++)

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
add_library(${PROJECT_NAME} include/ansi.h++ ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
