cmake_minimum_required(VERSION 2.8)
project(raccoochat)

# settings
set(CMAKE_CXX_FLAGS "-std=c++14 -O3 -Wall -Wextra -Wuninitialized")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
set(CMAKE_FILES_DIRECTORY "build/")

# includes
include_directories(SYSTEM ${PROJECT_SOURCE_DIR})
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/raccoochat/third-party/gtest-1.7.0/fused-src)

# subdirectories
add_subdirectory(${PROJECT_SOURCE_DIR}/raccoochat/third-party/gtest-1.7.0/fused-src/gtest)

# sources
set(SOURCES
    # thrift
    ${PROJECT_SOURCE_DIR}/raccoochat/gen-cpp/RaccooChat.cpp
    ${PROJECT_SOURCE_DIR}/raccoochat/gen-cpp/raccoochat_constants.cpp
    ${PROJECT_SOURCE_DIR}/raccoochat/gen-cpp/raccoochat_types.cpp
    # raccoochat
    ${PROJECT_SOURCE_DIR}/raccoochat/DeserializationUtils.cpp
    ${PROJECT_SOURCE_DIR}/raccoochat/FileDataBase.cpp
    ${PROJECT_SOURCE_DIR}/raccoochat/MessageUtils.cpp
    ${PROJECT_SOURCE_DIR}/raccoochat/RaccooChatServer.cpp
    ${PROJECT_SOURCE_DIR}/raccoochat/SerializationUtils.cpp
    ${PROJECT_SOURCE_DIR}/raccoochat/Tools.cpp
    ${PROJECT_SOURCE_DIR}/raccoochat/UserUtils.cpp
)

add_library(raccoochat STATIC ${SOURCES})
target_link_libraries(raccoochat glog gflags thrift)

# binaries
macro(make_binary binary_source binary_name)
    add_executable(${binary_name} raccoochat/${binary_source})
    target_link_libraries(${binary_name} raccoochat pthread)
    set_target_properties(${binary_name}
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin/")
endmacro(make_binary)

make_binary(server.cpp server)

# unit testing
macro(make_test test_source test_name)
    add_executable(${test_name} raccoochat/test/${test_source})
    target_link_libraries(${test_name} raccoochat gtest gtest_main pthread)
    set_target_properties(${test_name}
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "test/")
    add_test(${test_name} test/${test_name})
endmacro(make_test)

enable_testing()
make_test(SimpleTest.cpp SimpleTest)
