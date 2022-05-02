cmake_minimum_required(VERSION 3.18)

project(lanty-core
    VERSION
        0.1.0
    LANGUAGES
        C
        CXX)

include(CMakeDependentOption)

option(BUILD_SHARED_LIBS "Building shared library." OFF)
option(BUILD_TESTING "Build tests." OFF)
option(LANTY_CORE_BUILD_SHARED_LIBS "Build lanty-core as a shared library" ${BUILD_SHARED_LIBS})
cmake_dependent_option(LANTY_CORE_BUILD_TESTS
  "Enable lanty-core tests." ON
  "BUILD_TESTING;CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR" OFF)
cmake_dependent_option(LANTY_CORE_LLVM_COVERAGE
  "Enable lanty-core coverage reporting." OFF
  "LANTY_CORE_BUILD_TESTS" OFF)
option(LANTY_CORE_BUILD_DOCUMENTATION "Build the doxygen documentation" OFF)

set(lanty-core-type STATIC)
if (LANTY_CORE_BUILD_SHARED_LIBS)
  set(lanty-core-type SHARED)
endif()

set(build-windows-dll $<AND:$<BOOL:${CMAKE_HOST_WIN32}>,$<BOOL:${LANTY_CORE_BUILD_SHARED_LIBS}>>)

add_subdirectory(project)

if(LANTY_CORE_BUILD_TESTS)
    enable_testing()
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(library/googletest)
    add_subdirectory(test)
endif()

if(LANTY_CORE_BUILD_DOCUMENTATION)
  add_subdirectory(documentation)
endif()
