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
    basic_ifstream infile(argv[1]);
    if(infile.fail() || infile.bad())
    {
      cerr<<"Cannot open "<<argv[1]<<endl;
      return 2;
    }
    infile>>cities_obj;
  }
  else
  {
    cin>>cities_obj;
  }

  Cities::permutation_t perm = random_permutation(cities_obj.size());
  unsigned target            = cities_obj.total_path_distance(perm);
  for(unsigned i_=1; i_<1048576; i_++)
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
    basic_ofstream outfile("shortest.tsv");
    if(outfile.fail() || outfile.bad())
    {
      cerr<<"Cannot open shortest.tsv"<<endl;
      return 2;
    }
    outfile<<cities_obj;
  }
  else
  {
    cout<<cities_obj.reorder(perm);
  }
  cerr<<"Done. Minimum distance: "<<target<<endl;
  return 0;
}
