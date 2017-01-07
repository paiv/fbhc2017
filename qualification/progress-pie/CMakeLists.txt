cmake_minimum_required(VERSION 3.2)
project(progress_pie)

add_executable(progresspie main.cpp)

set_property(TARGET progresspie PROPERTY CXX_STANDARD 11)

set(TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(TESTS_COMMAND "${CMAKE_CURRENT_BINARY_DIR}/progresspie")
configure_file(tests/runner.py.in tests_runner.py @ONLY)
