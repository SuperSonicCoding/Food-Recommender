#define CATCH_CONFIG_MAIN
#include "header/catch.hpp"
#include "../src/restaurant.hpp"

Restaurant r = {"Example", Type::Mexican, 1.2, "01/02/2003", "Food", "City", "ST"};

TEST_CASE("Getting day works", "[integer]") {
    REQUIRE(r.getDay() == 1);
}

TEST_CASE("Getting month works", "[integer]") {
    REQUIRE(r.getMonth() == 2);
}

TEST_CASE("Getting year works", "[integer]") {
    REQUIRE(r.getYear() == 2003);
}