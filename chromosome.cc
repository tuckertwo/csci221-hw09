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
void Chromosome::mutate()
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
std::pair<Chromosome::chrom_ptr, Chromosome::chrom_ptr>
Chromosome::recombine(const Chromosome::chrom_ptr other)
{
  assert(is_valid());
  assert(other->is_valid());

  // Generate our initial index into the array.
  std::uniform_int_distribution<unsigned> dist0(0, order_.size()-2);
  unsigned idx0 = dist0(generator_);
  // Generate our second index by picking a number after the first index
  assert(idx0+1<=order_.size()-1);
  std::uniform_int_distribution<unsigned> dist1(idx0+1, order_.size()-1);
  unsigned idx1 = dist1(generator_);
  // Crossover
  Chromosome::chrom_ptr me = clone();
  Chromosome::chrom_ptr child0 = create_crossover_child(me, other, idx0, idx1);
  Chromosome::chrom_ptr child1 = create_crossover_child(other, me, idx0, idx1);
  return std::make_pair(child0, child1);
  // You just lost The Game.
}

//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.
Chromosome::chrom_ptr
Chromosome::create_crossover_child(const Chromosome::chrom_ptr p1,
                                   const Chromosome::chrom_ptr p2,
                                   unsigned b, unsigned e) const
{
  Chromosome::chrom_ptr child = p1->clone();

  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < p1->order_.size() && j < p2->order_.size(); ++i) {
    if (i >= b and i < e) {
      child->order_.at(i) = p1->order_.at(i);
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e)) {
        ++j;
        assert(j < p2->order_.size());
      }
      child->order_.at(i) = p2->order_.at(j);
      j++;
    }
  }

  assert(child->is_valid());
  return child;
}

// Return a positive fitness value, with higher numbers representing
// fitter solutions (shorter total-city traversal path).
double Chromosome::get_fitness() const
{
  return get_fitness_perm(order_);
}

// Gets the fitness of a particular ordering.
double Chromosome::get_fitness_perm(Cities::permutation_t order) const
{
  assert(check_permutation(order));
  double dist = cities_ptr_->total_path_distance(order);

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
  // Already wrote this function for HW09.
  return check_permutation(order_);
}

// Find whether a certain value appears in a given range of the chromosome.
// Returns true if value is within the specified the range specified
// [begin, end) and false otherwise.
bool Chromosome::is_in_range(unsigned value, unsigned begin, unsigned end) const
{
  assert(begin<=end);
  for(unsigned i = begin; i != end; i++)
  {
    // Doesn't bounds-check i because .at() does that for us.
    if(order_.at(i) == value)
    {
      return true;
    }
  }
  return false;
}
