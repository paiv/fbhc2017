cmake_minimum_required(VERSION 3.2)
project(task2)

add_executable(task2 main.cpp)

set_property(TARGET task2 PROPERTY CXX_STANDARD 11)

set(TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(TESTS_COMMAND "${CMAKE_CURRENT_BINARY_DIR}/task2")
configure_file(tests/runner.py.in tests_runner.py @ONLY)
