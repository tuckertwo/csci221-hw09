#define CATCH_CONFIG_MAIN
#include "catch.hh"
#include "cities.hh"
#include <sstream>

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
  REQUIRE(check_permutation(random_permutation(128)));
  REQUIRE(check_permutation(random_permutation(128)));
  REQUIRE(check_permutation(random_permutation(128)));
}

TEST_CASE("Cities and other methods")
{
  Cities cities0;
  // Pythagorean triples, to make distances nice non-floats.
  Cities cities1({std::make_pair(0,0),  std::make_pair(3,4),
      std::make_pair(8,16),  std::make_pair(16,31), std::make_pair(23,55),
      std::make_pair(14,15), std::make_pair(6,9),   std::make_pair(3,5),
      std::make_pair(3,4)});
  // Evil irrational numbers
  Cities cities2({std::make_pair(1,2),  std::make_pair(3,4),
      std::make_pair(5,6), std::make_pair(7,8)});

  // Test TPD
  REQUIRE(cities1.total_path_distance({0,1,2,3,4,5,6,7,8}) == 122);
  // Make sure reordering and inversion works as expected
  REQUIRE(cities1.reorder({8,7,6,5,4,3,2,1,0}).total_path_distance({8,7,6,5,4,3,
        2,1,0}) == 122);
  // Make sure reordering actually does something
  REQUIRE(cities1.reorder({5,6,4,3,7,2,1,0,8}).total_path_distance({8,7,6,5,4,3,
        2,1,0}) != 122);

  double tpd_ir = cities2.total_path_distance({0,1,2,3});
  // Crude attempt at ensuring that an irrational number is equal to the /right/
  // irrational number.
  REQUIRE(tpd_ir>16);
  REQUIRE(tpd_ir<17);
}

TEST_CASE("I/O")
{
  // Somewhat pathological input case
  const std::string pyth_inp
    = "0 0\n3 4\n8 16\n16 31 \n\r\n23 55\n14\t15\n6 9\n3 5\n3 4\n";
  // Correct output case
  const std::string pyth_out
    = "0\t0\n3\t4\n8\t16\n16\t31\n23\t55\n14\t15\n6\t9\n3\t5\n3\t4\n";

  // These std::istringstreams let us simulate input from files.
  std::istringstream test_inp_blank("");
  std::istringstream test_inp_spc(" ");
  std::istringstream test_inp_pyth(pyth_inp);

  // Initialize blank Cities objects.
  Cities blank;
  Cities spc;
  Cities pyth;
  // Expected parse of PYTH_INP
  Cities realpyth({std::make_pair(0,0),  std::make_pair(3,4),
      std::make_pair(8,16),  std::make_pair(16,31), std::make_pair(23,55),
      std::make_pair(14,15), std::make_pair(6,9),   std::make_pair(3,5),
      std::make_pair(3,4)});

  // Read inputs
  test_inp_blank>>blank;
  test_inp_spc>>spc;
  test_inp_pyth>>pyth;

  // Check that input reading works
  REQUIRE(blank.total_path_distance({})==0);
  REQUIRE(spc.total_path_distance({})==0);
  REQUIRE(pyth.total_path_distance({0,1,2,3,4,5,6,7,8})
      == realpyth.total_path_distance({0,1,2,3,4,5,6,7,8}));

  // Analogous to std::istringstreams, these std::ostringstreams let us simulate
  // output to a file.
  std::ostringstream test_out_blank;
  std::ostringstream test_out_pyth0;
  std::ostringstream test_out_pyth1;

  // Output Cities objects to our ostringstreams.
  test_out_blank<<blank;
  test_out_pyth0<<pyth;
  test_out_pyth1<<realpyth;

  REQUIRE(test_out_blank.str() == "");
  REQUIRE(test_out_pyth0.str() == pyth_out);
  REQUIRE(test_out_pyth1.str() == pyth_out);
}
