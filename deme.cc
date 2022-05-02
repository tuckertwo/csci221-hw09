/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */

#include "chromosome.hh"
#include "deme.hh"
#include <algorithm>
#include <cassert>

// Generate a Deme of the specified size with all-random chromosomes.
// Also receives a mutation rate in the range [0-1].
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
    // It is my impression that initializing a vector with placeholders and then
    // overwriting those placeholders is more efficient than growing the vector
    // for each new element.
  : pop_(pop_size, nullptr),
    mut_rate_(mut_rate),
    generator_(rand())
{
  for(unsigned i = 0; i<pop_size; i++)
  {
    pop_.push_back(new Chromosome(cities_ptr));
  }
}

// Clean up as necessary
Deme::~Deme()
{
  // Add your implementation here
}

// Evolve a single generation of new chromosomes, as follows:
// We select pop_size/2 pairs of chromosomes (using the select() method below).
// Each chromosome in the pair can be randomly selected for mutation, with
// probability mut_rate, in which case it calls the chromosome mutate() method.
// Then, the pair is recombined once (using the recombine() method) to generate
// a new pair of chromosomes, which are stored in the Deme.
// After we've generated pop_size new chromosomes, we delete all the old ones.
void Deme::compute_next_generation()
{
  // Add your implementation here
}

// Return a copy of the chromosome with the highest fitness.
const Chromosome* Deme::get_best() const
{
  // Handle a population of zero properly
  if(pop_.size() == 0)
  {
    return nullptr;
  }
  else
  {
    // Use the lovely STL to get us the element with the highest fitness, using
    // a special ad-hoc comparison function to handle nullptrs and calling the
    // get_fitness method.
    return std::max_element(pop_.cbegin(), pop_.cend(),
        [](Chromosome* a, Chromosome* b)
          {return (a&&b)&&(a->get_fitness() < b->get_fitness());});
          // (a&&b)&&x ensures that a and b are not nullptrs before evaluating
          // x, which relies on a and b actually pointing to something.
  }
}

// Randomly select a chromosome in the population based on fitness and
// return a pointer to that chromosome.
Chromosome* Deme::select_parent()
{
  // Add your implementation here
}
