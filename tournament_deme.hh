#include "deme.hh"
#include "climb_chromosome.hh"

class TournamentDeme : public Deme
{
 protected:
  // Randomly select a chromosome in the population using tournament selection
  // return a pointer to that chromosome.
  virtual ClimbChromosome::chrom_ptr select_parent();
};
