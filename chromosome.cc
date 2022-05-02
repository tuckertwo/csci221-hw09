/*
 * Implementation for Chromosome class
 */

#include <algorithm>
#include <cassert>
#include <random>

#include "chromosome.hh"

//////////////////////////////////////////////////////////////////////////////
// Generate a completely random permutation from a list of cities
Chromosome::Chromosome(const Cities* cities_ptr)
  : cities_ptr_(cities_ptr),
    order_(random_permutation(cities_ptr->size())),
    generator_(rand())
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
Chromosome::~Chromosome()
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Perform a single mutation on this chromosome
void
Chromosome::mutate()
{
  assert(order_.size()>0); // Prevents UB in uniform_int_distribution

  // Allows us to generate unbiased random numbers in a particular range
  std::uniform_int_distribution<unsigned> dist(0, order_.size()-1);

  // Generates our indices.
  unsigned idx0   = dist(generator_);
  unsigned idx1   = dist(generator_);

  // Performs the swap.
  unsigned temp   = order_.at(idx0);
  order_.at(idx0) = order_.at(idx1);
  order_.at(idx1) = temp;
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Return a pair of offsprings by recombining with another chromosome
// Note: this method allocates memory for the new offsprings
std::pair<Chromosome*, Chromosome*>
Chromosome::recombine(const Chromosome* other)
{
  assert(is_valid());
  assert(other->is_valid());

  // Generate our initial index into the array.
  std::uniform_int_distribution<unsigned> dist0(0, order_.size()-2);
  unsigned idx0 = dist0(generator_);
  // Generate our second index by picking a number after the first index
  std::uniform_int_distribution<unsigned> dist1(idx0, order_.size()-1);
  unsigned idx1 = dist0(generator_);
  // Crossover
  Chromosome* child0 = create_crossover_child(this, other, idx0, idx1);
  Chromosome* child1 = create_crossover_child(other, this, idx1, idx0);
  return std::make_pair(child0, child1);
  // You just lost The Game.
}

//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.
Chromosome*
Chromosome::create_crossover_child(const Chromosome* p1, const Chromosome* p2,
                                   unsigned b, unsigned e) const
{
  Chromosome* child = p1->clone();

  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < p1->order_.size() && j < p2->order_.size(); ++i) {
    if (i >= b and i < e) {
      child->order_[i] = p1->order_[i];
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e)) {
        ++j;
        assert(j < p2->order_.size());
      }
      child->order_[i] = p2->order_[j];
      j++;
    }
  }

  assert(child->is_valid());
  return child;
}

// Return a positive fitness value, with higher numbers representing
// fitter solutions (shorter total-city traversal path).
double
Chromosome::get_fitness() const
{
  double dist = cities_ptr_->total_path_distance(order_);

  // For any x>1, 1/x<x. Thus, we can make our fitness the reciprocal of the
  // total path distance to convert from a lower-is-better measurement to a
  // higher-is-better measurement.
  // First, though, we've got to make sure our constraint holds.
  assert(dist>0); // Our constraint is x>0 because we use x+1 later.
  return 1/(dist+1);
}

// A chromsome is valid if it has no repeated values in its permutation,
// as well as no indices above the range (length) of the chromosome.
bool
Chromosome::is_valid() const
{
  return check_permutation(order_);
}

// Find whether a certain value appears in a given range of the chromosome.
// Returns true if value is within the specified the range specified
// [begin, end) and false otherwise.
bool
Chromosome::is_in_range(unsigned value, unsigned begin, unsigned end) const
{
  for(i = begin; i != end; i++)
  {
    if(*i == value)
    {
      return true;
    }
  }
  return false;
}
