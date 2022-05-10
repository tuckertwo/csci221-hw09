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
    Chromosome::chrom_ptr member(new Chromosome(cities_ptr));
    pop_.at(i) = member;
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
  std::vector<Chromosome::chrom_ptr> newpop;
  for(unsigned i=0; i<pop_.size()/2; i++)
  {
    // This does not provide special handling for the case where both parents
    // are the same.
    Chromosome::chrom_ptr parent0 = select_parent();
    Chromosome::chrom_ptr parent1 = select_parent();
    // Decimal points are necessary to make the constructor use float types.
    std::uniform_real_distribution randdist(0.0, 1.0);
    for(Chromosome::chrom_ptr parent : {parent0, parent1})
    {
      if(randdist(generator_) < mut_rate_)
      {
        parent->mutate();
      }
    }
    std::pair<Chromosome::chrom_ptr, Chromosome::chrom_ptr> children
      = parent0->recombine(parent1);
    newpop.push_back(std::get<0>(children));
    newpop.push_back(std::get<1>(children));
  }
  assert(abs(pop_.size() - newpop.size())<=1);
  pop_ = newpop;
}

// Return a copy of the chromosome with the highest fitness.
const Chromosome::chrom_ptr Deme::get_best() const
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
    // Note that max_element returns an iterator, not an element.
    auto max_el_iter = std::max_element(pop_.cbegin(), pop_.cend(),
        [](Chromosome::chrom_ptr a, Chromosome::chrom_ptr b)
          {return (a&&b)&&(a->get_fitness() < b->get_fitness());});
          // (a&&b)&&x ensures that a and b are not nullptrs before evaluating
          // x, which relies on a and b actually pointing to something.
    return *max_el_iter;
  }
}

// Randomly select a chromosome in the population based on fitness and
// return a pointer to that chromosome.
Chromosome::chrom_ptr Deme::select_parent()
{
  // Calculate fitnesses using my beloved map()-like function.
  // This makes the function run in O(n) time, and is probably the most
  // computationally expensive part of it for large values of n.
  // It would thus make sense to replace repeated calls to select_parent() with
  // a mechanism that would generate the fitness list once and repeatedly select
  // unique chromosomes using it.
  std::vector<double> fitnesses;
  std::transform(pop_.cbegin(), pop_.cend(), std::back_inserter(fitnesses),
      [](Chromosome::chrom_ptr x)
      {
        if(x)
        {
          double fitness = x->get_fitness();
          return fitness;
        }
        else
        {
          return 0.0;
        }
      });
  assert(fitnesses.size() == pop_.size());

  // Select the index of a random chromosome using discrete_distribution and the
  // weights calculated previously, then return the chromosome with that index.
  std::discrete_distribution distr(fitnesses.cbegin(), fitnesses.cend());
  return pop_.at(distr(generator_));
}
