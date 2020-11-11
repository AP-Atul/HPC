build:
	mpic++ -o pbs parallelBinarySearch.cpp
	g++ -o sbs serialBinarySearch.cpp

run_parallel:
	mpiexec -n 4 ./pbs

run_serial:
	./sbs

clean:
	rm pbs sbs