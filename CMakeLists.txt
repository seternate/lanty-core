# Copyright <2022> <Levin Jeck>

# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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
