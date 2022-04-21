#include "cities.hh"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  Cities cities_obj;
  if(argc>=2)
  {
    cerr<<"Incorrect number of arguments"<<endl;
    return 1;
  }
  else if(argc==2)
  {
    //
  }
  else
  {
    cin>>cities_obj;
  }

  Cities::permutation_t perm = random_permutation(cities_obj.size());
  unsigned target = cities_obj.total_path_distance(perm);
  for(unsigned i_; i_<(2^cities_obj.size()); i_++) // Change me.
  {
    Cities::permutation_t attempt = random_permutation(cities_obj.size());
    unsigned attempt_size         = cities_obj.total_path_distance(attempt);
    if(attempt_size>target)
    {
      perm   = attempt;
      target = attempt_size;
    }
  }

  if(argc==2)
  {
    //
  }
  else
  {
    cout<<cities_obj.reorder(perm);
  }
  cerr<<"Done. Minimum distance: "<<target<<endl;
  return 0;
}
