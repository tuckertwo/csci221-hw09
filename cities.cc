#include "cities.hh"
#include <algorithm>
#include <vector>
#include <random>
#include <cmath>
#include <cassert>

using namespace std;

Cities Cities::reorder(const permutation_t& ordering) const
{
  assert(check_permutation(ordering));
  Cities::atlas_t new_atlas(ordering.size()); // Make a new atlas
  for(unsigned i=0; i<ordering.size(); i++) // Fill it
  {
    new_atlas.at(ordering.at(i)) = points_.at(i);
  }
  Cities new_cities(new_atlas);
  return new_cities;

}

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

Cities::operator<<(ostream& out) const
{
  for(pair<int> coord : points_)
  {
    // x y\n
    out << get<0>(coord) << "\t" << get<1>(coord) << endl;
  }
}

Cities::operator>>(istream& in)
{
  while(!in.eof())
  {
    // C++'s << operator actually makes this remarkably easy.
    // It skips over whitespace (spaces, tabs, and newlines alike), then grabs
    // and parses the next cluster of integers.
    // It throws an exception if it receives unexpected input.
    // Because of how this program is set up, coordinates and pairs of points
    // need only be separated by spaces, which could cause unexpected results
    // with pathologically malformed files.
    int x, y;
    in>>x;
    in>>y;
    points_.push_back(make_pair<Cities::coord_t>(x, y));
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
