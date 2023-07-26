cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(boltdb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMKAE_CXX_FLAGS} -Wall")

set(BOLTDB_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

Include(FetchContent)

# Add dependency: Catch2
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

include_directories(${BOLTDB_INSTALL_INCLUDE_DIR})

add_subdirectory(tests)