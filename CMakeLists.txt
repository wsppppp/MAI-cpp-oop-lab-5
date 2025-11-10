cmake_minimum_required(VERSION 3.16)
project(oop_lab_4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Библиотека фигур (только заголовочные файлы)
add_library(figures INTERFACE)
target_include_directories(figures INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Основное приложение
add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE figures)

# Подключение GoogleTest для тестирования
enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Сборка тестов
add_executable(run_tests tests/test_figures.cpp)
target_link_libraries(run_tests PRIVATE gtest_main figures)
add_test(NAME unit_tests COMMAND run_tests)