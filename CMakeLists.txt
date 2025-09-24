CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(tests)

# catch2 v3.x
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests
  # first source files to test
  src/chassis_motor.cpp
  src/motor_control.cpp
  src/ota.cpp
  src/self_check.cpp
  src/wifi_wrapper.cpp

  # now the test files
  tests/chassis_motor.cpp
  tests/motor_control.cpp
  tests/self_check.cpp
)

# Coverage flags
set(COVERAGE_FLAGS -fprofile-arcs -ftest-coverage -O0 -g)
target_compile_options(tests PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain gcov)
target_compile_definitions(tests PRIVATE UNIT_TESTING)

# Optional: Coverage target
add_custom_target(coverage
  COMMAND ${CMAKE_MAKE_PROGRAM} tests
  COMMAND ./tests
  COMMAND gcov -c
    ./CMakeFiles/tests.dir/src/chassis_motor.cpp.obj
    ./CMakeFiles/tests.dir/src/motor_control.cpp.obj
    ./CMakeFiles/tests.dir/src/self_check.cpp.obj
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running tests and generating coverage report"
)
