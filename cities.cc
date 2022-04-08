#include "cities.hh"
#include <algorithm>
#include <vector>

using namespace std;

bool check_permutation(Cities::permutation_t perm)
{
  vector<bool> elements(perm.size(), false);
  for(unsigned int n : perm)
  {
    if(n >= perm.size())
    {
      return false;
    }

    if(elements.at(n))
    {
      return false;
    }

    elements.at(n) = true;
  }

  return all_of(elements.cbegin(), elements.cend(), [](bool x) {return x;});
}
