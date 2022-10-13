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

project(lanty-core-library)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5
   COMPONENTS
      Core
      Gui
      Network
   REQUIRED)

find_package(yaml-cpp 0.6.3 REQUIRED)

find_package(nlohmann_json 3.9.1 REQUIRED)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/core/version.hpp.in include/core/version.hpp @ONLY)

set(LANTY_CORE_LIBRARY_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/source/core/FileExtension.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/game/Game.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/game/GameClient.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/game/GameClientLoader.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/game/GameImage.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/game/GameLoader.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/game/GameServer.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/game/GameServerLoader.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/game/GameVersion.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/game/GameVersionLoader.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/game/QGame.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/game/QGamelist.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/game/QGamelistFactory.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/game/QGamelistLoader.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/network/Connection.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/network/NetworkHelper.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/network/exploration/HostExplorer.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/network/exploration/HostExposer.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/network/message/AddressMessage.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/network/message/GameDownloadRequest.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/network/message/GamelistMessage.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/network/message/Message.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/network/message/MessageLoader.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/network/message/MessageType.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/network/message/UserMessage.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/user/QUser.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/user/QUserlist.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/user/User.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/source/user/UserLoader.cpp)

set(LANTY_CORE_LIBRARY_HEADERS
   ${CMAKE_CURRENT_SOURCE_DIR}/include/core/FileExtension.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/core/ltycore_global.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/core/JSONLoadable.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/core/JSONSerializable.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/core/YAMLLoadable.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/core/YAMLSerializable.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/game/Game.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/game/GameClient.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/game/GameClientLoader.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/game/GameImage.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/game/GameLoader.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/game/GameServer.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/game/GameServerLoader.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/game/GameVersion.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/game/GameVersionLoader.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/game/QGame.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/game/QGamelist.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/game/QGamelistFactory.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/game/QGamelistLoader.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/network/Connection.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/network/NetworkHelper.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/network/exploration/HostExploration.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/network/exploration/HostExplorer.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/network/exploration/HostExposer.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/network/message/AddressMessage.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/network/message/GameDownloadRequest.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/network/message/GamelistMessage.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/network/message/Message.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/network/message/MessageLoader.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/network/message/MessageType.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/network/message/UserMessage.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/user/QUser.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/user/QUserlist.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/user/User.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/user/UserLoader.hpp)

set(LANTY_CORE_LIBRARY_RCC
   ${CMAKE_CURRENT_SOURCE_DIR}/../resource/core.qrc
   ${CMAKE_CURRENT_SOURCE_DIR}/../resource/style.qrc)

add_library(lanty-core-library ${lanty-core-type}
   ${LANTY_CORE_LIBRARY_SOURCES}
   ${LANTY_CORE_LIBRARY_HEADERS}
   ${LANTY_CORE_LIBRARY_RCC})

add_library(lanty-core-library::lanty-core-library
   ALIAS
      lanty-core-library)

set_target_properties(lanty-core-library
   PROPERTIES
      CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set_target_properties(lanty-core-library
    PROPERTIES
      CXX_STANDARD 17)
endif()

target_include_directories(lanty-core-library
   PUBLIC
      include
   PRIVATE
      ${CMAKE_CURRENT_BINARY_DIR}/include)

target_link_libraries(lanty-core-library
   PUBLIC
      Qt5::Core
      Qt5::Gui
      Qt5::Network
      nlohmann_json::nlohmann_json
      yaml-cpp)

target_compile_options(lanty-core-library
   PRIVATE
      -Werror
      -Wall
      #-Wextra
      #-Wshadow
      #-Weffc++
      #-Wno-long-long
      #-pedantic
      #-pedantic-errors
      )

target_compile_definitions(lanty-core-library
      PRIVATE
         $<${build-windows-dll}:LANTY_CORE_DLL>)

set_target_properties(lanty-core-library
   PROPERTIES
      VERSION "${CMAKE_PROJECT_VERSION}"
      SOVERSION "${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}"
      DEBUG_POSTFIX d)

if(LANTY_CORE_LLVM_COVERAGE)
   target_compile_options(lanty-core-library
      PRIVATE
         -fprofile-instr-generate
         -fcoverage-mapping)

   target_link_options(lanty-core-library
      PUBLIC
         -fprofile-instr-generate)
endif()
