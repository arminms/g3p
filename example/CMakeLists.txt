cmake_minimum_required(VERSION 3.14...3.26)

project(g3p-example CXX)

include(FetchContent)
find_package(
  g3p CONFIG
  HINTS $ENV{HOME} $ENV{HOME}/.local /usr/local /usr
)
if(NOT g3p_DIR)
    message(STATUS "Fetching g3p library...")
    include(FetchContent)
    FetchContent_Declare(
      g3p
      GIT_REPOSITORY https://github.com/arminms/g3p.git
      GIT_TAG main
    )
    FetchContent_MakeAvailable(g3p)
endif()

add_executable(bessel bessel.cpp)
target_link_libraries(bessel PRIVATE g3p::g3p)
