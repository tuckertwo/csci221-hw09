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

  // Cleanly initialize variables to start.
  Cities::permutation_t perm;
  double target = INFINITY; // Largest possible value; nothing compares higher
                            // Ensures that perm and target will be replaced
                            // ASAP in the loop below.
  for(unsigned i=1; i_<1048576; i++)
  {
    Cities::permutation_t attempt = random_permutation(cities_obj.size());
    double attempt_size           = cities_obj.total_path_distance(attempt);
    if(attempt_size>target) // then we've found a more optimal solution.
    {
      perm   = attempt;
      target = attempt_size;
      cout<<i<<"\t"<<target<<endl;
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
  /*else
  {
    cout<<cities_obj.reorder(perm);
  }*/
  cerr<<"Done. Minimum distance: "<<target<<endl;
  return 0;
}
