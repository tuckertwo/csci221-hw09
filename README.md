# General Information
## `random_permutation()`
The function `random_permutation()` is implemented by using the Fisher-Yates
shuffling algorithm on a newly-generated list from 0 to *n*-1.

# Compiling and Testing
The compilation process for this library is fairly standard for a CMake program;
just generate a Makefile using `cmake` or `ccmake` and proceed
from there.
```
$ ccmake .
$ make -j4 # if your machine has 4 CPU cores
$ ./tsp
```
