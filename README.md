# General Information
This code was written by Julian Jacklin and Tucker R. Twomey.
Documentation for the `tsp` program is below;
documentation for the `Cities` class is contained within `cities.hh`.
Both use STL methods and types whenever possible.

# Compiling and Testing
The compilation process for this library is fairly standard for a CMake program;
just generate a Makefile using `cmake` or `ccmake` and proceed
from there.
```
$ ccmake .
$ make -j4 # if your machine has 4 CPU cores
$ ./test_cities
```

# Running
To run, compile the program (see above) and then run `tsv`, passing the input
file as the first argument.
`tsv` will then do a brute-force search for the shortest path,
outputting its progress to STDOUT and outputting a solution to `shortest.tsv`.
One can also call `tsv` without arguments;
in this case, `tsv` will take input from STDIN and will not output the solution.
