#include "cities.hh"
#include <algorithm>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

double Cities::total_path_distance(const Cities::permutation_t& ordering) const
{
  double accum = 0;
  for(unsigned i=0; i<points_.size(); i++)
  {
    // Our first point is at index i.
    Cities::coord_t c0 = points_.at(ordering.at(i));

    // Our second point is after index i, wrapping around (using modulo) if i is
    // the last element.
    Cities::coord_t c1 = points_.at(ordering.at((i+1)%points_.size()));

    accum += sqrt(pow(get<0>(c0)-get<0>(c1), 2)
        + pow(get<1>(c0)-get<1>(c1), 2));
  }
  return accum;
}

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
