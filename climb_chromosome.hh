#include "chromosome.hh"

class ClimbChromosome : public Chromosome
{
 public:
  virtual chrom_ptr clone() const
  {
    chrom_ptr chrom(new ClimbChromosome(*this));
    return chrom;
  }

  // Perform a single mutation on this chromosome: swap two random cities.
  virtual void mutate();
};