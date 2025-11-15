cmake_minimum_required(VERSION 3.16)
project(oop_lab_5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Основная цель: main.cpp
add_executable(app src/main.cpp)

# Подключаем директорию include (для MemoryResource, DynamicArray, MyStruct)
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Подключение GoogleTest для тестирования
enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Сборка тестов
add_executable(run_tests tests/test_lab.cpp)
target_include_directories(run_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(run_tests PRIVATE gtest_main)

add_test(NAME unit_tests COMMAND run_tests)