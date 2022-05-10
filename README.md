# General Information
This code was written by Julian Jacklin and Tucker R. Twomey.
Documentation for the `Cities`, `Chromosome`, and `Deme` classes are contained
within their respective header files.
Attempts have been made to use STL functions in preference to C-style constructs
whenever possible.
As part of this effort, the professor-provided `Chromosome` and `Deme` classes
have been rewritten to use `shared_ptr`s instead of C-style pointers.

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
To run, compile the program (see above) and then run `tsp`, passing the input
file as the first argument, the population size as the second argument, and the
mutation rate (0-1) as the third argument.
This will perform a genetic algorithm search,
printing successively better solutions to STDOUT and writing the best solution
to `shortest.tsv`.

# Performance
Experimentation has found that a high population size and mutation rate tends
to converge quickly, while a lower population size and high mutation rate yields
a better solution.

The best solution found by the genetic algorithm, with a length of 17270.3,
was found after 60720 iterations with a population size of 40, and a mutation
rate of 0.9.

![A graph comparing performance between genetic and random approaches to the
travelling salesman problem.](comparison.gif)
