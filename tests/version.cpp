#include "../build/_deps/catch2-src/src/catch2/catch_test_macros.hpp"

#include "../src/VERSION.h"
#include "../src/mocks.h"

#include <sstream>

TEST_CASE("TEST_0011 - version information exists and format is correct", "[version]")
{
    // Step 2
    static_assert(std::is_same<decltype(VERSION), const char *>::value, "VERSION is not of type const char *");

    // Step 3
    std::string version = VERSION;
    char delimiter = '.';
    std::vector<std::string> elements;
    std::string element;

    std::stringstream stream(version);
    while (std::getline(stream, element, delimiter))
    {
        elements.push_back(element);
    }
    REQUIRE(elements.size() == 3);

    // Steps 5 and 6
    std::cout << "Elements: " << std::endl;
    int result;
    for (std::string &element : elements)
    {
        std::cout << element << std::endl;
        REQUIRE_NOTHROW(result = std::stoi(element));
        REQUIRE(result >= 0);
    }
}