#include "climb_chromosome.hh"
#include <cassert>

ClimbChromosome::~ClimbChromosome() {}

void ClimbChromosome::mutate()
{
  assert(order_.size()>0); // Prevents UB in uniform_int_distribution

  // Allows us to generate unbiased random numbers in a particular range
  std::uniform_int_distribution<unsigned> dist(0, order_.size()-1);

  // Generates our index.
  unsigned idx0   = dist(generator_);

  unsigned idx1   = 0;
  if(idx0 == 0)
  {
    idx1 = order_.size()-1;
  }
  else
  {
    idx1 = idx0-1;
  }

  // Clever trick: (N-1) mod (N-1) == 0
  unsigned idx2   = idx0 % (order_.size()-1);

  // Performs the first swap.
  Cities::permutation_t new_order_prev = order_;
  new_order_prev.at(idx0) = order_.at(idx1);
  new_order_prev.at(idx1) = order_.at(idx0);
  assert(check_permutation(new_order_prev));

  // Perform the second swap.
  Cities::permutation_t new_order_next = order_;
  new_order_next.at(idx0) = order_.at(idx2);
  new_order_next.at(idx2) = order_.at(idx0);
  assert(check_permutation(new_order_prev));

  double fittest_val = 0;
  Cities::permutation_t fittest;
  for(Cities::permutation_t order : {order_, new_order_next, new_order_prev})
  {
    if(get_fitness_perm(order) > fittest_val)
    {
      fittest_val = get_fitness_perm(order);
      fittest     = order;
    }
  }
  order_ = fittest;
}
