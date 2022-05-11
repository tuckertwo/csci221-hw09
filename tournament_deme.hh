#include "deme.hh"
#include "climb_chromosome.hh"
#pragma once

class TournamentDeme : public Deme
{
 public:
  TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate);

  ~TournamentDeme();

 protected:
  // Randomly select a chromosome in the population using tournament selection
  // return a pointer to that chromosome.
  virtual ClimbChromosome::chrom_ptr select_parent();
};
