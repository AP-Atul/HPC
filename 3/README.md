## Contents
1. Sorting Algos with serial and parallel implementation.
2. When numbers are greater than 10000, there is time difference in the parallel and the serial implementations

### Execution
1. Clone the repo or copy the codes
2. For parallel algos with openmp use the flag while compiling
```
$ gcc -fopenmp fileName.cpp -o fileName
```
3. Or you can use the shell file directly, make the shell script executable
```
$ sudo chmod +xr runXX.sh
```
4. You will be able to see the time difference, if sorting goes wrong it will split out numbers.

There is not that much of a time difference but it works better than serial one in some aspects.

Also OpenMP is completely new concept for me, so it's a win win.😀