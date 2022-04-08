#include "cities.hh"
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

bool check_permutation(Cities::permutation_t perm)
{
  vector<bool> elements(perm.size(), false);
  for(unsigned int n : perm)
  {
    if(n >= perm.size())
    {
      return false;
    }

    if(elements.at(n))
    {
      return false;
    }

    elements.at(n) = true;
  }

  return all_of(elements.cbegin(), elements.cend(), [](bool x) {return x;});
}

Cities::permutation_t random_permutation(unsigned int len)
{
  Cities::permutation_t perm(len, 0);
  iota(perm.begin(), perm.end(), 0);

  random_device rand_dev;
  mt19937 rand_gen(rand_dev());
  shuffle(perm.begin(), perm.end(), rand_gen);
  return perm;
}
