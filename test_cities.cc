#define CATCH_CONFIG_MAIN
#include "catch.hh"
#include "cities.hh"

// These test cases were based on the specification given in `tree.hh`.
TEST_CASE("check_permutation")
{
  REQUIRE(!check_permutation({1,2,3,4}));
  REQUIRE(check_permutation({0,1,2,3,4}));
  REQUIRE(check_permutation({}));
  REQUIRE(check_permutation({0}));
  REQUIRE(!check_permutation({0,1,1,2,3,4}));
  REQUIRE(!check_permutation({0,1,3,4}));
}
