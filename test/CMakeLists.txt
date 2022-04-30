cmake_minimum_required(VERSION 3.18)

include(GoogleTest)

project(lanty-core-test)

find_package(Qt5
   COMPONENTS
      Test
   REQUIRED)

set(LANTY_CORE_TEST_SOURCES
   source/core/FileExtensionTest.cpp
   source/core/main.cpp
   source/core/JSONLoadableTest.cpp
   source/core/YAMLLoadableTest.cpp
   source/game/GameClientLoaderTest.cpp
   source/game/GameClientTest.cpp
   source/game/GameImageTest.cpp
   source/game/GameLoaderTest.cpp
   source/game/GameServerLoaderTest.cpp
   source/game/GameServerTest.cpp
   source/game/GameTest.cpp
   source/game/GameVersionLoaderTest.cpp
   source/game/GameVersionTest.cpp
   source/game/QGamelistTest.cpp
   source/game/QGameTest.cpp
   source/user/QUserlistTest.cpp
   source/user/QUserTest.cpp
   source/user/UserLoaderTest.cpp
   source/user/UserTest.cpp)

add_executable(lanty-core-test
   ${LANTY_CORE_TEST_SOURCES})

set_target_properties(lanty-core-test
   PROPERTIES
      CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set_target_properties(lanty-core-test
    PROPERTIES
      CXX_STANDARD 17)
endif()

target_include_directories(lanty-core-test
   PRIVATE
      include)

target_link_libraries(lanty-core-test
   PRIVATE
      gtest
      Qt5::Test
      lanty-core-library::lanty-core-library)

gtest_discover_tests(lanty-core-test)

if(LANTY_CORE_LLVM_COVERAGE)
   find_program(LLVM_PROFDATA llvm-profdata REQUIRED)
   add_custom_target(lanty-core-coverage-preprocessing
      COMMAND LLVM_PROFILE_FILE=default.profraw $<TARGET_FILE:lanty-core-test>
      COMMAND "llvm-profdata" "merge" "default.profraw" "-o" "default.profdata"
      DEPENDS lanty-core-test)

   find_program(LLVM_COV llvm-cov REQUIRED)
   add_custom_target(lanty-core-coverage-lcov-exporting
      COMMAND "llvm-cov" "export" "-ignore-filename-regex='(.+\/(moc_|Serializable.hpp|FileExtension.hpp).?)|(.+\/library\/.+)|(.+\/include\/(game|user))'" "-format=lcov" "-instr-profile=default.profdata" "$<TARGET_FILE:lanty-core-test>" ">" "coverage.lcov"
      DEPENDS lanty-core-coverage-preprocessing)

   add_custom_target(lanty-core-coverage-detail
      COMMAND "llvm-cov" "show" "$<TARGET_FILE:lanty-core-test>" "-ignore-filename-regex='(.+\/(moc_|Serializable.hpp|FileExtension.hpp).?)|(.+\/library\/.+)|(.+\/include\/(game|user))'" "-instr-profile=default.profdata"
      DEPENDS lanty-core-coverage-preprocessing)

   add_custom_target(lanty-core-coverage-summary
      ALL
      COMMAND "llvm-cov" "report" "$<TARGET_FILE:lanty-core-test>" "-ignore-filename-regex='(.+\/(moc_|Serializable.hpp|FileExtension.hpp).?)|(.+\/library\/.+)|(.+\/include\/(game|user))'" "-instr-profile=default.profdata"
      DEPENDS lanty-core-coverage-preprocessing)

   find_program(GENHTML genhtml)
   if(GENHTML)
      add_custom_target(lanty-core-coverage-html
         ALL
         COMMAND "genhtml" "coverage.lcov" "--legend" "--output-directory=coverage-html"
         DEPENDS lanty-core-coverage-lcov-exporting)
   else()
      message("Could not find genhtml. Skipping coverage HTML reporting.")
   endif()

   find_program(LCOV_COBERTURA lcov_cobertura)
   if(LCOV_COBERTURA)
      add_custom_target(lanty-core-coverage-cobertura
         ALL
         COMMAND "lcov_cobertura" "coverage.lcov"
         DEPENDS lanty-core-coverage-lcov-exporting)
   else()
      message("Could not find lcov_cobertura. Skipping coverage cobertura reporting.")
   endif()
endif()
