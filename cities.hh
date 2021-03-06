/*
 * API file for Travelling-Salesperson Cities class and utilities
 */

#pragma once

#include <vector>
#include <ostream>
#include <istream>


// Representation of an ordering of cities
class Cities
{
 public:

  // A pair of integral coordinates for each city
  using coord_t = std::pair<int, int>; // int x, int y

  // A list of cities in no particular order.
  using atlas_t = std::vector<coord_t>;

  // An ordering of cities. Each value represents a unique index
  // into the current city ordering in some container.
  using permutation_t = std::vector<unsigned int>;

  Cities(atlas_t points_init = {}) : points_(points_init) {};

  // Given a permutation, return a new Cities object where the order of the
  // cities reflects the original order of this class after reordering with
  // the given ordering. So for example, the ordering { 1, 0 } simply swaps
  // the first two elements (coordinates) in the new Cities object.
  Cities reorder(const permutation_t& ordering) const;

  // For a given permutation of the cities in this object,
  // compute how long (distance) it would take to traverse all the cities in the
  // order of the permutation, and then returning to the first city.
  // The distance between any two cities is computed as the Euclidean 
  // distance on a plane between their coordinates.
  double total_path_distance(const permutation_t& ordering) const;

  // Reads out the list of cities into an output stream.
  // >> and << should roughly be their own inverses.
  friend std::ostream& operator<<(std::ostream& out, const Cities& cities);

  // Reads  in an  input stream into the list of cities.
  friend std::istream& operator>>(std::istream& in,  Cities& cities);

  // Gives the number of cities contained within the Cities object.
  unsigned size() const;
 private:
  atlas_t points_;
};

bool check_permutation(Cities::permutation_t perm);

Cities::permutation_t random_permutation(unsigned int len);
