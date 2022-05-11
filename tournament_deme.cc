#include "tournament_deme.hh"
#include <cmath>
#include <algorithm>
#include <cassert>

TournamentDeme::~TournamentDeme() {}

// Randomly select a chromosome in the population using tournament selection and
// return a pointer to that chromosome.
Chromosome::chrom_ptr TournamentDeme::select_parent()
{
  unsigned init_size = pow(2, floor(log2(pop_.size())-1));
  assert(init_size>1);

  std::vector<unsigned> perm(pop_.size());
  std::iota(perm.begin(), perm.end(), 0);
  std::shuffle(perm.begin(), perm.end(), generator_);

  std::vector<ClimbChromosome::chrom_ptr> bracket;
  for(unsigned i=0; i<init_size; i++)
  {
    bracket.at(i) = pop_.at(perm.at(i));
  }

  while(bracket.size()>1)
  {
    std::vector<ClimbChromosome::chrom_ptr> new_bkt;
    for(unsigned i=0; i<bracket.size(); i+=2)
    {
      ClimbChromosome::chrom_ptr i_el = bracket.at(i);
      ClimbChromosome::chrom_ptr j_el = bracket.at(i+1);

      assert(i_el);
      assert(j_el);

      if(i_el->get_fitness() > j_el->get_fitness())
      {
        new_bkt.push_back(i_el);
      }
      else
      {
        new_bkt.push_back(j_el);
      }
    }

    assert(new_bkt.size() == bracket.size()/2);
    bracket = new_bkt;
  }
  return bracket.at(0);
}
