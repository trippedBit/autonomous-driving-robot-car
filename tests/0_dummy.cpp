// Dummy file to make CMake happy while no real test files are present.

#include "../build/_deps/catch2-src/src/catch2/catch_test_macros.hpp"

#include "../src/0_dummy.h"

TEST_CASE("Dummy test case", "[dummy]")
{
    REQUIRE(dummy() == 1);
}