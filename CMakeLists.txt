#
# Copyright (c) 2023-24 Armin Sobhani
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
cmake_minimum_required(VERSION 3.19...3.26)

## detect if g3p is being bundled, disable unit tests in that case
#
if(NOT DEFINED PROJECT_NAME)
  set(NOT_SUBPROJECT ON)
else()
  set(NOT_SUBPROJECT OFF)
endif()

## Set default build type to Release if none was specified
#
include(cmake/BuildType.cmake)

## life is about choices...
#
option(G3P_ENABLE_TESTS "Enable the unit tests ?" ON)

## finally our project...
#
project(
  g3p
  VERSION 1.2.0
  LANGUAGES CXX
  DESCRIPTION "gnuplot for Modern C++ with support for Jupyter"
)

## prevent in-source builds
#
if (CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  message(FATAL_ERROR "Building in-source is not supported! Create a build dir and remove ${CMAKE_SOURCE_DIR}/CMakeCache.txt")
endif()

## find the thread library
#
find_package(Threads REQUIRED)

## find gnuplot
#
find_package(Gnuplot)
if (NOT GNUPLOT_FOUND)
  message(WARNING "g3p requires gnuplot executable to be in the PATH environment variable")
endif()

## necessary modules
#
include(GNUInstallDirs)
include(FetchContent)

## defining g3p target
#
add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(${PROJECT_NAME} INTERFACE
  Threads::Threads
)
set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${g3p_VERSION}
  SOVERSION ${g3p_VERSION_MAJOR}
)

## specifying the export name for the targets
#
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-targets
)

## installing g3p header files
#
add_subdirectory(include)

## installing g3p export target file
#
install(
  EXPORT ${PROJECT_NAME}-targets
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

## generate the config file that includes the exports
#
include(CMakePackageConfigHelpers)
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

## creating version file
#
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
  VERSION "${g3p_VERSION_MAJOR}.${g3p_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

## installing g3p export config files
#
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

## make export target available from the build tree
#
export(EXPORT ${PROJECT_NAME}-targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-targets.cmake"
  NAMESPACE ${PROJECT_NAME}::
)

## include unit test and artwork only when g3p is not being used as a subproject
#
if (NOT_SUBPROJECT)
  ## add unit tests
  #
  if(${G3P_ENABLE_TESTS})
    enable_testing()
    find_package(
      Catch2 3
      HINTS $ENV{HOME} /usr/local /opt/local /opt
    )
    if(NOT Catch2_FOUND)
        message(STATUS "Fetching Catch2 library...")
        FetchContent_Declare(
          catch2
          GIT_REPOSITORY https://github.com/catchorg/Catch2.git
          GIT_TAG        v3.5.2
        )
        FetchContent_MakeAvailable(Catch2)
        list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    endif()
    include(CTest)
    include(Catch)
    add_subdirectory(test)
  endif()

  ## adding artwork
  #
  add_subdirectory(artwork)
endif(NOT_SUBPROJECT)
