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

TEST_CASE("random_permutation")
{
  Cities::permutation_t perm0 = {};
  Cities::permutation_t perm1 = {0};
  REQUIRE(random_permutation(0) == perm0);
  REQUIRE(random_permutation(1) == perm1);
  REQUIRE(check_permutation(random_permutation(128)));
}

TEST_CASE("Cities and other methods")
{
  Cities cities0;
  // Pythagorean triples, to make distances nice non-floats.
  Cities cities1({(0,0),  (3,4), (8,16), (16,31), (23,55), (14,15), (6,9),
      (3,5), (3,4)});
  // Evil irrational numbers
  Cities cities2({(1,2),  (3,4),  (5,6), (7,8)});
  REQUIRE(cities1.total_path_distance({0,1,2,3,4,5,6,7,8}) == 122);
  REQUIRE(cities1.reorder({8,7,6,5,4,3,2,1,0}).total_path_distance({0,1,2,3,4,
        5,6,7,8}) == 122);
}
